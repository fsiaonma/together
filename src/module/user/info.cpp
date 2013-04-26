#include "user.h"

/**
 * get user info
 *  
 * @method get_user_info
 * @param {string} username username which is used for getting user info.
 * @param {string} sid sid which is used for getting user info.
 * @param {char*} respone data. 
 * @return {int} get_user_info status.
 */
int get_user_info(string username, string sid, char *buf) {
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
            http_res->set_success(0);
            msg = "username or sid is null";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        // session is not exist
        if (Session::get(sid) == NULL) {
            result = SESSION_NOT_EXIST;
            http_res->set_code(SESSION_NOT_EXIST);
            http_res->set_success(0);
            msg = "session not exist";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        //TODO: get username info
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
int set_user_info(map<string, string> param, string sid, char *buf) {
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
            http_res->set_success(0);
            msg = "sid is null";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        // session is not exist
        if (Session::get(sid) == NULL) {
            result = SESSION_NOT_EXIST;
            http_res->set_code(SESSION_NOT_EXIST);
            http_res->set_success(0);
            msg = "session not exist";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }
        
        //TODO: set username info
    } while(0);

    http_res->SerializeToString(&respon_data);
    const char *p = respon_data.c_str();
    strncpy(buf, p, strlen(p) + 1);
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}