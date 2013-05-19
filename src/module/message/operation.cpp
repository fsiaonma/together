#include "message.h"

int save_msg(int sock, map<string, string> param, list<int> &send_sock_list, char *buf)
{
    char c_rst[10];
    int result = SAVE_MSG_SUCCESS;
    send_sock_list.push_back(sock);
    do
    {
        // sid?

        int sender_id = Tool::S2I(param["senderId"]);
        int recipient_id = Tool::S2I(param["recipientId"]);
        int room_id = Tool::S2I(param["roomId"]);
        int msg_type = Tool::S2I(param["msgType"]);
        string content = param["content"];

        if (sender_id < 0 || !(msg_type == 1 || msg_type == 2) || Tool::trim(content).empty())
        {
            result = PARAM_ERROR;
            LOG_ERROR << "param error" << endl;
            break;
        }

        // database params
        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

        // connect fail
        if (!e.connet()) {
            result = DB_ERROR;
            LOG_ERROR << "connect fail" << endl; 
            e.close();
            break;
        }

        MYSQL mysql;
        int db_ret;
        mysql = e.get_mysql();

        string call_pr = "call pr_insert_msg (" + Tool::toString(sender_id) + ", " 
            + Tool::toString(recipient_id) + ", " + Tool::toString(room_id) + ", " 
            + Tool::toString(msg_type) + ", " + Tool::mysql_filter(content) +", @ret, @send_user_list)";
        LOG_DEBUG << call_pr << endl;
        db_ret = mysql_query(&mysql, call_pr.c_str());
        db_ret = mysql_query(&mysql, "SELECT @ret, @send_user_list");

        // exception
        if (db_ret)
        {
            result = DB_ERROR;
            e.close();
            LOG_ERROR << "DB ERROR|" << db_ret << endl; 
            break;
        }
        MYSQL_RES *db_rst = NULL;
        db_rst = mysql_store_result(&mysql);
        MYSQL_ROW row = NULL;
        row = mysql_fetch_row(db_rst);

        db_ret = Tool::S2I(row[0]);
        string send_list = row[1];

        LOG_DEBUG << "db_ret:" << db_ret << "|send_list:" << send_list << endl;

        if (db_ret == DB_PR_ERR)
        {
            result = DB_ERROR;
            LOG_ERROR << "call pr_insert_msg err|" << endl;
            e.close();
            break;
        }
        if (db_ret == DB_PR_INSERT_MSG_SENDER_NOTEXIST)
        {
            result = SAVE_MSG_SENDER_NOTEXIST;
            LOG_ERROR << "sender not exist" << endl;
            e.close();
            break;
        }
        if (db_ret == DB_PR_INSERT_MSG_ROOM_NOTEXIST)
        {
            result = SAVE_MSG_ROOM_NOTEXIST;
            LOG_ERROR << "room not exist" << endl;
            e.close();
            break;
        }
        if (db_ret == DB_PR_INSERT_MSG_RECIPIENT_NOTEXIST)
        {
            result = SAVE_MSG_RECIPIENT_NOTEXIST;
            LOG_ERROR << "recipient not exist" << endl;
            e.close();
            break;
        }
        if (db_ret == DB_PR_INSERT_MSG_MSGTYPE_ERROR)
        {
            result = SAVE_MSG_MSGTYPE_ERROR;
            LOG_ERROR << "msg type error" << endl;
            e.close();
            break;
        }
        result = SAVE_MSG_SUCCESS;
        std::vector<string> v = Tool::split(send_list, "|");
        for (int i = 0; i < (int)v.size(); i++)
        {
            int so = find_sock(Tool::S2I(v[i]));
            LOG_DEBUG << v[i] << "|" << so << endl;
            if (!(so < 0 || so == sock))
                send_sock_list.push_back(so);
        }


    } while(0);
    sprintf(c_rst, "%d", result);
    strncpy(buf, c_rst, strlen(c_rst) + 1);
    return result;
}

/**
 * change message status from not read to have read
 *  
 * @method change_msg_status
 * @param {int} msg_id id of message
 * @return {int} change_msg_status status.
 */
int change_msg_status(int msg_id, char *buf, int &send_len) {
     string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result;
    int ret;

    LOG_INFO << "msg_id is " << msg_id << endl;

    do {    
        // msg_id is not be found
        if (msg_id <= 0) {
            result = PARAM_ERROR;
            _set_http_head(result, false, "msg_id error", http_res);
            break;
        }

        // change message status
        map<string, string> update_params;

        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), 
            config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));
        
        if (!e.connet()) {
            result = SQL_CONNECT_FAIL;
            _set_http_head(result, false, "sql connet fail", http_res);
        }

        ret = e.excute("select status from t_msg where id=" + Tool::mysql_filter(msg_id) + ";");
        if (ret != DB_OK) {
            result = DB_ERROR;
            _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
            break;
        }

        MYSQL mysql;
        mysql = e.get_mysql();

        MYSQL_RES *res = NULL;
        MYSQL_ROW row = NULL;

        res = mysql_store_result(&mysql);
        row = mysql_fetch_row(res);

        update_params["status"] = Tool::mysql_filter(MSG_HAVE_READ);

        e.close();

        ret = e.update("t_msg", update_params, "where id=" + Tool::mysql_filter(msg_id) + ";");
        // exception
        if (ret != DB_OK) {
            result = CHANGE_MSG_STATUS_FAIL;
            _set_http_head(result, false, "change message status fail", http_res);
            break;
        }

        result = CHANGE_MSG_STATUS_SUCCESS;
        _set_http_head(result, true, "change message status success", http_res);
    } while(0);

    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    memcpy(buf, respon_data.c_str(), respon_data.length());
    send_len = respon_data.length();
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}