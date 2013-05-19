#include "user.h"

/**
 * user login
 *  
 * @method login
 * @param {string} username username which is used for login.
 * @param {string} password password which is used for login.
 * @param {char*} respone data. 
 * @return {int} login status.
 */
int login(string username, string password, string dev_id, char *buf, int &send_len) {
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result;
    int ret;

    do {
        LOG_INFO << "login params: username is " << username << " password is " << password << "dev_id is " << dev_id << endl;
        
        // username or password not be found
        if (Tool::trim(username).empty() || Tool::trim(password).empty() || Tool::trim(dev_id).empty()) {
            result = PARAM_ERROR;
            _set_http_head(result, false, "username or password or dev_id is null", http_res);
            break;
        }

        // database params
        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));
        bool exist;

        // check whether username and password match is database or not 
        ret = e.is_exist("t_user", "where username = '" + username + "' and password = '" + password + "'", exist);
        // exception
        if (ret != DB_OK) {
            result = DB_ERROR;
            _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
            break;
        }
        // user not exist
        if (!exist) {
            result = USER_NOT_EXIST;
            _set_http_head(result, false, "user not exist", http_res);
            break;
        }

        // set session
        string sid;
        int uid;

        _get_uid(username, uid);

        ret = Session::set(Tool::toString(uid), dev_id, sid);
        LOG_INFO << "sid is: " << sid << endl;
        if (ret == LOGIN_REPLACE) {
            result = LOGIN_REPLACE;
            _set_http_head(result, true, "login success and replace session", http_res);
        } else {
            result = LOGIN_SUCCESS;
            _set_http_head(result, true, "login success", http_res);
        }

        UserData::User_Info *user_info = new UserData::User_Info();
        ret = _get_user_info(uid, user_info);
        // exception
        if (ret != DB_OK) {
            result = DB_ERROR;
            _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
            break;
        }
        UserResponse::LoginResponse *login_res = new UserResponse::LoginResponse();
        login_res->set_allocated_user_info(user_info);
        login_res->set_sid(sid);
        http_res->set_allocated_login_response(login_res);
    } while(0);

    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    memcpy(buf, respon_data.c_str(), respon_data.length());
    send_len = respon_data.length();
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}

/**
 * user logout
 *  
 * @method logout
 * @param {string} sid sid which is used for logout.
 * @param {char*} buf respone data.
 * @return {int} louout status. 
 */
int logout(string sid, char *buf, int &send_len) {
    string respon_data;
    int result;
    string msg;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();

    LOG_INFO << " sid is " << sid << endl;

    do {    
        //sid is not be found
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

        // remove session
        cout << Session::get(sid)->uid << endl;
        Session::remove(Session::get(sid)->uid);
        result = LOGOUT_SUCCESS;
        _set_http_head(result, true, "remove session success", http_res);
    } while(0);

    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    memcpy(buf, respon_data.c_str(), respon_data.length());
    send_len = respon_data.length();
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}