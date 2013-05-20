#include "room.h"

int join_room(map<string, string> param, char *buf, int &send_len)
{
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result = JOIN_ROOM_SUCCESS;
    int ret;

    // database params
    Config *c = Config::get_instance();
    map<string, string> config = c->get_config();
    eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

    MYSQL_RES *db_rst = NULL;

    do
    {
        // param sid not exist
        if (param.count("sid") == 0)
        {
            result = PARAM_ERROR;
            http_res->set_code(PARAM_ERROR);
            msg = "param sid not exist";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        // session is not exist
        if (Session::get(Tool::trim(param["sid"])) == NULL) {
            result = SESSION_NOT_EXIST;
            http_res->set_code(SESSION_NOT_EXIST);
            msg = "session not exist";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }
        
        int room_id = Tool::S2I(param["roomId"]);
        int user_id = Tool::S2I(param["userId"]);

        if (room_id < 0 || user_id < 0)
        {
            result = PARAM_ERROR;
            http_res->set_code(PARAM_ERROR);
            msg = "param error";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        // connect fail
        if (!e.connet()) {
            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            msg = "DB ERROR|join room|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            e.close();
            break;
        }

        MYSQL mysql;
        int db_ret;
        mysql = e.get_mysql();

        string call_pr = "call pr_join_room (" + Tool::toString(room_id) + ", " + Tool::toString(user_id) +
            " , @ret, @now_room_peo_list)";
        LOG_DEBUG << call_pr << endl;
        db_ret = mysql_query(&mysql, call_pr.c_str());
        db_ret = mysql_query(&mysql, "SELECT @ret");

        // exception
        if (db_ret)
        {
            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            msg = "DB ERROR|join room call pr|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            e.close();
            break;
        }

        db_rst = mysql_store_result(&mysql);
        MYSQL_ROW row = NULL;
        row = mysql_fetch_row(db_rst);

        db_ret = Tool::S2I(row[0]);
        if (db_ret == DB_PR_ERR)
        {
            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            msg = "call pr_join_room err|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            e.close();
            break;
        }
        if (db_ret == DB_PR_PARAM_ERR)
        {
            result = JOIN_ROOM_USER_OR_ROOM_NOEXIST;
            http_res->set_code(JOIN_ROOM_USER_OR_ROOM_NOEXIST);
            msg = "user or room not exist";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            e.close();
            break;
        }
        if (db_ret == DB_PR_JOIN_ROOM_HAVEBEENJOINED)
        {
            result = JOIN_ROOM_HAVEBEENJOINED;
            http_res->set_code(JOIN_ROOM_HAVEBEENJOINED);
            msg = "have been joined room";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            e.close();
            break;
        }
        if (db_ret == DB_PR_JOIN_ROOM_OVERLIMITNUM)
        {
            result = JOIN_ROOM_OVERLIMITNUM;
            http_res->set_code(JOIN_ROOM_OVERLIMITNUM);
            msg = "already over limit num";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            e.close();
            break;
        }


        // success
        result = JOIN_ROOM_SUCCESS;
        http_res->set_code(JOIN_ROOM_SUCCESS);
        http_res->set_success(true);
        msg = "join room success";
        LOG_INFO << msg << endl;
        http_res->set_msg(msg);
        e.close();

    } while(0);
    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    memcpy(buf, respon_data.c_str(), respon_data.length());
    send_len = respon_data.length();
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}