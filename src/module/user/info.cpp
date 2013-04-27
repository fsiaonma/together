#include "user.h"

/**
 * view user info
 *  
 * @method view_user_info
 * @param {string} username username which is used for getting user info.
 * @param {string} sid sid which is used for getting user info.
 * @param {char*} respone data. 
 * @return {int} view_user_info status.
 */
int view_user_info(int uid, string username, string sid, char *buf) {
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result;
    int ret;

    LOG_INFO << "username is " << username << " sid is " << sid << endl;

    do {    
        // username or password is not be found
        if (Tool::trim(username).empty()) {
            result = PARAM_ERROR;
            http_res->set_code(PARAM_ERROR);
            http_res->set_success(false);
            msg = "username is null";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        UserData::User_Info *user_info = new UserData::User_Info();
        UserResponse::DetailResponse *detail_res = new UserResponse::DetailResponse();

        _get_user_info(username, user_info);

        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), 
            config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));
        
        // increase visit num
        if (!Tool::trim(sid).empty() && username != Session::get(sid) -> username) {
            // increase visit number
            map<string, string> visit_params;
            int visit_num = 0;
            if (user_info->visit_num()) {
                visit_num = user_info->visit_num() + 1;
            }
            visit_params["visit_num"] = Tool::mysql_filter(visit_num);
            ret = e.update("t_user", visit_params, "where username = '" + username + "';");
            // exception
            if (ret != DB_OK) {
                result = DB_ERROR;
                http_res->set_code(DB_ERROR);
                http_res->set_success(false);
                msg = "DB ERROR|" + Tool::toString(ret);
                LOG_ERROR << msg << endl;
                http_res->set_msg(msg);
                break;
            }
        }

        // check whether follow or not
        if (uid > 0) {
            bool exist;
            ret = e.is_exist("t_follow", 
                "where follow_id = " + Tool::mysql_filter(uid) + " and followed_id = " + Tool::mysql_filter(user_info->uid()) + ";", 
                exist);
            // exception
            if (ret != DB_OK) {
                result = DB_ERROR;
                http_res->set_code(DB_ERROR);
                http_res->set_success(false);
                msg = "DB ERROR|" + Tool::toString(ret);
                LOG_ERROR << msg << endl;
                http_res->set_msg(msg);
                break;
            }
            detail_res->set_is_follow(exist);
        }

        result = VIEW_USER_INFO_SUCCESS;
        msg = "view user info success";
        LOG_INFO << msg << endl;

        _set_http_head(result, true, msg, http_res);
        detail_res->set_allocated_user_info(user_info);
        http_res->set_allocated_detail_response(detail_res);
    } while(0);

    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    const char *p = respon_data.c_str();
    strncpy(buf, p, strlen(p) + 1);
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}

/**
 * set user info
 *  
 * @method set_user_info
 * @param {map<string, string>} param datas for setting user info.
 * @param {string} sid sid which is used for setting user info.
 * @param {char*} respone data. 
 * @return {int} set_user_info status.
 */
int set_user_info(map<string, string> params, string sid, char *buf) {
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result;
    int ret;

    LOG_INFO << " sid is " << sid << endl;

    do {    
        // username or password is not be found
        if (Tool::trim(sid).empty()) {
            result = PARAM_ERROR;
            http_res->set_code(PARAM_ERROR);
            http_res->set_success(false);
            msg = "sid is null";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        // session is not exist
        if (Session::get(sid) == NULL) {
            result = SESSION_NOT_EXIST;
            http_res->set_code(SESSION_NOT_EXIST);
            http_res->set_success(false);
            msg = "session not exist";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }
        
        map<string, string> update_params;

        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), 
            config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

        map<string, string>::iterator ptr;
        for(ptr = params.begin(); ptr != params.end(); ++ptr) {
            if (ptr->first != "action" && ptr->first != "sid") {
                update_params[ptr->first] = Tool::mysql_filter(ptr->second);
            }
        }

        ret = e.update("t_user", update_params, "where username = '" + Session::get(sid)->username + "'");
        // exception
        if (ret != DB_OK) {
            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            http_res->set_success(false);
            msg = "DB ERROR|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        result = SET_USER_INFO_SUCCESS;
        http_res->set_code(SET_USER_INFO_SUCCESS);
        http_res->set_success(true);
        msg = "set user info success";
        LOG_ERROR << msg << endl;
        http_res->set_msg(msg);
    } while(0);

    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    const char *p = respon_data.c_str();
    strncpy(buf, p, strlen(p) + 1);
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}