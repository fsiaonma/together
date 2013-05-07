#include "room.h"

int quit_room(map<string, string> param, char *buf)
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
            http_res->set_success(0);
            msg = "param sid not exist";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        // session is not exist
        if (Session::get(Tool::trim(param["sid"])) == NULL) {
            result = SESSION_NOT_EXIST;
            http_res->set_code(SESSION_NOT_EXIST);
            http_res->set_success(0);
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
            http_res->set_success(0);
            msg = "param error";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        // connect fail
        if (!e.connet()) {
            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            http_res->set_success(0);
            msg = "DB ERROR|quit room|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        MYSQL mysql;
        int db_ret;
        mysql = e.get_mysql();

        string call_pr = "call pr_quit_room (" + Tool::toString(room_id) + ", " + Tool::toString(user_id) +", @ret)";
        LOG_DEBUG << call_pr << endl;
        db_ret = mysql_query(&mysql, call_pr.c_str());
        db_ret = mysql_query(&mysql, "SELECT @ret");

        // exception
        if (db_ret)
        {
            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            http_res->set_success(0);
            msg = "DB ERROR|quit room call pr|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
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
            http_res->set_success(0);
            msg = "call pr_quit_room err|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }
        if (db_ret == DB_PR_PARAM_ERR)
        {
            result = QUIT_ROOM_USER_OR_ROOM_NOEXIST;
            http_res->set_code(QUIT_ROOM_USER_OR_ROOM_NOEXIST);
            http_res->set_success(0);
            msg = "user or room not exist";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }
        if (db_ret == DB_PR_QUIT_ROOM_NOTJOINED)
        {
            result = QUIT_ROOM_NOTJOINED;
            http_res->set_code(QUIT_ROOM_NOTJOINED);
            http_res->set_success(0);
            msg = "not joined room yet";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }


        // success
        result = QUIT_ROOM_SUCCESS;
        http_res->set_code(QUIT_ROOM_SUCCESS);
        http_res->set_success(1);
        msg = "quit room success";
        LOG_INFO << msg << endl;
        http_res->set_msg(msg);

    } while(0);
    print_proto(http_res);
    mysql_free_result(db_rst); 
    e.close();

    http_res->SerializeToString(&respon_data);
    const char *p = respon_data.c_str();
    strncpy(buf, p, strlen(p) + 1);
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}