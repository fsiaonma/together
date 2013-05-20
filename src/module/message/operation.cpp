#include "message.h"
#include "../../lib/session/session.h"

int save_msg(int sock, map<string, string> param, list<int> &send_sock_list, char *buf)
{
    char c_rst[10];
    int result;
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
        if (msg_type == 1) {
            result = SAVE_MSG_GROUP_SUCCESS;
        } else {
            result = SAVE_MSG_SINGLE_SUCCESS;
        }
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

int join_room(int sock, map<string, string> param, list<int> &send_sock_list, char *buf)
{
    char c_rst[10];
    int result;
    send_sock_list.push_back(sock);
    do
    {
        // param sid not exist
        if (param.count("sid") == 0)
        {
            result = PARAM_ERROR;
            LOG_ERROR << "param sid not exist" << endl;
            break;
        }

        // session is not exist
        SESSION *s = Session::get(Tool::trim(param["sid"]));
        if (s == NULL) {
            result = SESSION_NOT_EXIST;
            LOG_ERROR << "session not exist" << endl;
            break;
        }
        int user_id = Tool::S2I(s->uid);
        LOG_INFO << "user id :" << user_id << endl;

        int room_id = Tool::S2I(param["roomId"]); 
        if (room_id < 0)
        {
            result = PARAM_ERROR;
            LOG_ERROR << "room_id error" << endl;
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

        string call_pr = "call pr_join_room(" + 
            Tool::toString(room_id) + ", " + Tool::toString(user_id) +
            " , @ret, @now_room_peo_list)";
        LOG_INFO << call_pr << endl;
        db_ret = mysql_query(&mysql, call_pr.c_str());
        db_ret = mysql_query(&mysql, "SELECT @ret, @now_room_peo_list");

        // exception
        if (db_ret)
        {
            result = DB_ERROR;
            LOG_ERROR << "DB ERROR|join room call pr" << endl;
            e.close();
            break;
        }

        MYSQL_RES *db_rst = NULL;
        db_rst = mysql_store_result(&mysql);
        MYSQL_ROW row = NULL;
        row = mysql_fetch_row(db_rst);

        db_ret = Tool::S2I(row[0]);
        if (db_ret != DB_PR_JOIN_ROOM_SUCCESS)
        {
            result = DB_ERROR;
            LOG_ERROR << "call pr_join_room result:" << db_ret << endl;
            e.close();
            break;
        }

        // find all people in room
        LOG_INFO << "room people list:" << row[1] << endl;
        vector<string> v_room_peo = Tool::split(row[1], "|");
        for (int i = 0; i < v_room_peo.size(); i++)
        {
            int uid = Tool::S2I(v_room_peo[i]);
            if (uid < 0 || uid == user_id)
                continue;
            int so = find_sock(uid);
            LOG_INFO << "send sock|" << uid << "|" << so << endl;
            if (!(so < 0 || so == sock))
                send_sock_list.push_back(so);
        }
        result = LC_JOIN_ROOM_SUCCESS;

    } while(0);
    sprintf(c_rst, "%d", result);
    strncpy(buf, c_rst, strlen(c_rst) + 1);
    return result;
}


int quit_room(int sock, map<string, string> param, list<int> &send_sock_list, char *buf)
{
    char c_rst[10];
    int result;
    send_sock_list.push_back(sock);
    do
    {
        // param sid not exist
        if (param.count("sid") == 0)
        {
            result = PARAM_ERROR;
            LOG_ERROR << "param sid not exist" << endl;
            break;
        }

        // session is not exist
        SESSION *s = Session::get(Tool::trim(param["sid"]));
        if (s == NULL) {
            result = SESSION_NOT_EXIST;
            LOG_ERROR << "session not exist" << endl;
            break;
        }
        int user_id = Tool::S2I(s->uid);
        LOG_INFO << "user id :" << user_id << endl;

        int room_id = Tool::S2I(param["roomId"]); 
        if (room_id < 0)
        {
            result = PARAM_ERROR;
            LOG_ERROR << "room_id error" << endl;
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

        string call_pr = "call pr_quit_room(" + 
            Tool::toString(room_id) + ", " + Tool::toString(user_id) +
            " , @ret, @now_room_peo_list)";
        LOG_INFO << call_pr << endl;
        db_ret = mysql_query(&mysql, call_pr.c_str());
        db_ret = mysql_query(&mysql, "SELECT @ret, @now_room_peo_list");

        // exception
        if (db_ret)
        {
            result = DB_ERROR;
            LOG_ERROR << "DB ERROR|quit room call pr" << endl;
            e.close();
            break;
        }

        MYSQL_RES *db_rst = NULL;
        db_rst = mysql_store_result(&mysql);
        MYSQL_ROW row = NULL;
        row = mysql_fetch_row(db_rst);

        db_ret = Tool::S2I(row[0]);
        if (db_ret != DB_PR_QUIT_ROOM_SUCCESS)
        {
            result = DB_ERROR;
            LOG_ERROR << "call pr_quit_room result:" << db_ret << endl;
            e.close();
            break;
        }

        // find all people in room
        LOG_INFO << "room people list:" << row[1] << endl;
        vector<string> v_room_peo = Tool::split(row[1], "|");
        for (int i = 0; i < v_room_peo.size(); i++)
        {
            int uid = Tool::S2I(v_room_peo[i]);
            if (uid < 0 || uid == user_id)
                continue;
            int so = find_sock(uid);
            LOG_INFO << "send sock|" << uid << "|" << so << endl;
            if (!(so < 0 || so == sock))
                send_sock_list.push_back(so);
        }
        result = LC_QUIT_ROOM_SUCCESS;

    } while(0);
    sprintf(c_rst, "%d", result);
    strncpy(buf, c_rst, strlen(c_rst) + 1);
    return result;
}

int start_room(int sock, map<string, string> param, list<int> &send_sock_list, char *buf)
{
    char c_rst[10];
    int result = START_ROOM_SUCCESS;
    send_sock_list.push_back(sock);
    do
    {
        // param sid not exist
        if (param.count("sid") == 0)
        {
            result = PARAM_ERROR;
            LOG_ERROR << "param sid not exist" << endl;
            break;
        }

        // session is not exist
        SESSION *s = Session::get(Tool::trim(param["sid"]));
        if (s == NULL) {
            result = SESSION_NOT_EXIST;
            LOG_ERROR << "session not exist" << endl;
            break;
        }
        int user_id = Tool::S2I(s->uid);
        LOG_INFO << "user id :" << user_id << endl;

        int room_id = Tool::S2I(param["roomId"]);

        if (room_id < 0)
        {
            result = PARAM_ERROR;
            LOG_ERROR << "room id error :" << room_id << endl;
            break;
        }

        // database params
        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

        bool is_exist_room;
        // whether room exist
        e.is_exist("t_room",  "where id = " + Tool::mysql_filter(room_id) + " and room_status = 0", is_exist_room);
        if (!is_exist_room)
        {
            result = START_ROOM_HASSTARTED_OR_NOTEXIST;
            LOG_ERROR << "room has started or not exist" << endl;
            break;
        }

        // connect fail
        if (!e.connet()) {
            result = DB_ERROR;
            LOG_ERROR << "connect fail" << endl; 
            e.close();
            break;
        }

        string sql = "SELECT r.owner_id, rel.user_id FROM t_room r left join t_room_user_relation rel "
        " on r.id = rel.room_id where r.id = " + Tool::mysql_filter(room_id);


        result = e.excute(sql);
        // exception
        if (result != DB_OK) {
            LOG_ERROR << "DB ERROR|get owner and joined people|" + Tool::toString(result) << endl;
            result = DB_ERROR;
            e.close();
            break;
        }

        MYSQL mysql = e.get_mysql();

        MYSQL_RES *rst = NULL;
        MYSQL_FIELD *field = NULL;
        MYSQL_ROW row = NULL;


        rst = mysql_store_result(&mysql);
        int fieldcount = mysql_num_fields(rst);
        row = mysql_fetch_row(rst);

        int owner_id = -1;
        vector<int> join_peo_list;
        while(NULL != row) 
        {
            for(int i = 0; i < fieldcount; i++) 
            {
                field = mysql_fetch_field_direct(rst, i);
                string key = field->name;
                if (row[i] == NULL)
                    continue;
                // LOG_DEBUG << row[i] << endl;
                if (key == "owner_id") {
                    owner_id = Tool::S2I(row[i]);
                } else if (key == "user_id") {
                    int join_peo_id = Tool::S2I(row[i]);
                    if (join_peo_id > 0)
                        join_peo_list.push_back(join_peo_id);
                }
            }
            row = mysql_fetch_row(rst);
        }
        e.close();


        // judge whether owner
        LOG_DEBUG << "owner_id:" << owner_id << endl;
        if (owner_id != user_id) {
            result = START_ROOM_ISNOT_OWNER;
            LOG_ERROR << "user is not owner" << endl;
            break;
        }

        // update room status
        if (!e.connet()) {
            result = DB_ERROR;
            LOG_ERROR << "connect fail" << endl; 
            e.close();
            break;
        }
        string update_room_sql = "update t_room set room_status = 1 "
        " and begin_time = " + Tool::now_time() +
        " where id = " + Tool::mysql_filter(room_id);

        result = e.excute(update_room_sql);
        // exception
        if (result != DB_OK) {
            LOG_ERROR << "DB ERROR|update t_room|" + Tool::toString(result) << endl;
            result = DB_ERROR;
            e.close();
            break;
        }

        // update success, add join_peo to sock list
        for (int i = 0; i < (int) join_peo_list.size(); i++)
        {
            LOG_DEBUG << "join peo id:" << join_peo_list[i] << endl;
            if (join_peo_list[i] > 0 && join_peo_list[i] != user_id) {
                int so = find_sock(join_peo_list[i]);
                if (!(so < 0 || so == sock))
                    send_sock_list.push_back(so);
            }
        }
        result = START_ROOM_SUCCESS;
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
int change_msg_status(int msg_id, int room_id, int recipient_id, char *buf, int &send_len) {
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
        
        update_params["status"] = Tool::mysql_filter(MSG_HAVE_READ);

        ret = e.update("t_msg", update_params, "where id<=" + Tool::mysql_filter(msg_id) 
            + " and room_id=" + Tool::mysql_filter(room_id)
            + " and recipient_id=" + Tool::mysql_filter(recipient_id)
            + ";");
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