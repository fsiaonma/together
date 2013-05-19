#include "user.h"

/**
 * view user info
 *  
 * @method view_user_info
 * @param {string} visit_uid visit_uid which is used for getting user info.
 * @param {string} sid sid which is used for getting user info.
 * @param {char*} respone data. 
 * @return {int} view_user_info status.
 */
int view_user_info(int visit_uid, string sid, char *buf, int &send_len) {
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result;
    int ret;

    LOG_INFO << "visit_uid is " << visit_uid << " sid is " << sid << endl;

    do {    
        // visit_uid is not be found
        if (visit_uid <= 0) {
            result = PARAM_ERROR;
            _set_http_head(result, false, "visit_uid is null", http_res);
            break;
        }

        // session is not exist
        if (Session::get(sid) == NULL) {
            result = SESSION_NOT_EXIST;
            _set_http_head(result, false, "session not exist", http_res);
            break;
        }

        UserData::User_Info *user_info = new UserData::User_Info();
        UserResponse::DetailResponse *detail_res = new UserResponse::DetailResponse();

        ret = _get_user_info(visit_uid, user_info);
        if (ret != DB_OK) {
            result = DB_ERROR;
            _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
            break;
        }

        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), 
            config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

        // increase visit num
        if (!Tool::trim(sid).empty() && visit_uid != Tool::S2I(Session::get(sid) -> uid)) {
            // increase visit number
            map<string, string> visit_params;
            int visit_num = 0;
            if (user_info->visit_num()) {
                visit_num = user_info->visit_num() + 1;
            }
            visit_params["visit_num"] = Tool::mysql_filter(visit_num);
            ret = e.update("t_user", visit_params, "where id = " + Tool::mysql_filter(visit_uid) + ";");
            // exception
            if (ret != DB_OK) {
                result = DB_ERROR;
                _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
                break;
            }
        }

        // check whether follow or not
        bool exist;
        int self_uid = Tool::S2I(Session::get(sid)->uid);
        _is_follow(self_uid, visit_uid, exist);
        if (exist) {
            detail_res->set_is_follow(true);
        } 

        result = VIEW_USER_INFO_SUCCESS;
        _set_http_head(result, true, "view user info success", http_res);

        detail_res->set_allocated_user_info(user_info);
        http_res->set_allocated_detail_response(detail_res);
    } while(0);

    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    memcpy(buf, respon_data.c_str(), respon_data.length());
    send_len = respon_data.length();
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
int set_user_info(map<string, string> params, string sid, char *buf, int &send_len) {
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result;
    int ret;

    LOG_INFO << " sid is " << sid << endl;

    do {    
        // sid is not be found
        if (Tool::trim(sid).empty()) {
            result = PARAM_ERROR;
            _set_http_head(result, false, "sid is null", http_res);
            break;
        }

        // session is not exist
        if (Session::get(sid) == NULL) {
            result = SESSION_NOT_EXIST;
            _set_http_head(result, false, "session not exist", http_res);
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

        ret = e.update("t_user", update_params, "where id = " + Tool::mysql_filter(Session::get(sid)->uid) + "");
        // exception
        if (ret != DB_OK) {
            result = DB_ERROR;
            _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
            break;
        }

        result = SET_USER_INFO_SUCCESS;
        _set_http_head(result, true, "set user info success", http_res);
    } while(0);

    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    memcpy(buf, respon_data.c_str(), respon_data.length());
    send_len = respon_data.length();
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}