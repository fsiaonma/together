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