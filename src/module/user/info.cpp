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
int view_user_info(string username, string sid, char *buf) {
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result;
    int ret;

    LOG_INFO << "username is " << username << " sid is " << sid << endl;

    do {    
        // username or password is not be found
        if (Tool::trim(username).empty() || Tool::trim(sid).empty()) {
            result = PARAM_ERROR;
            http_res->set_code(PARAM_ERROR);
            http_res->set_success(false);
            msg = "username or sid is null";
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

    //TODO: view username info and increase visit number
    #if 0
        UserData::User_Info *user_info = new UserData::User_Info();
        _get_user_info(username, user_info);

        if (username != Session::get(sid) -> username) {
            Config *c = Config::get_instance();
            map<string, string> config = c->get_config();
            eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), 
                config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

            // increase visit number
            map<string, string> visit_params;
            visit_params["visit_num"] = Tool::mysql_filter(user_info.get_user_info() + 1);
            int insert_id = -1;
            ret = e.insert("t_user", visit_params, insert_id);
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
        
        result = VIEW_USER_INFO_SUCCESS;
        http_res->set_code(VIEW_USER_INFO_SUCCESS);
        http_res->set_success(true);
        msg = "view user info success";
        LOG_ERROR << msg << endl;
        http_res->set_msg(msg);

        UserResponse::DetailResponse *detail_res = new UserResponse::DetailResponse();
        detail_res->set_allocated_user_info(user_info);
        http_res->set_allocated_detail_response(detail_res);
    #endif
    } while(0);

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
        
    //TODO: set user info
    #if 0
        map<string, string> update_params;

        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), 
            config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

        map<string, string>::iterator ptr;
        for(ptr = params.begin(); ptr != params.end(); ++ptr) {
            if (ptr->first != "action") {
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
    #endif
    } while(0);

    http_res->SerializeToString(&respon_data);
    const char *p = respon_data.c_str();
    strncpy(buf, p, strlen(p) + 1);
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}