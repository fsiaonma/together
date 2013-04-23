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
int login(string username, string password, string dev_id, char *buf) {
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
            http_res->set_code(PARAM_ERROR);
            http_res->set_success(0);
            msg = "username or password or dev_id is null";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
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
            http_res->set_code(DB_ERROR);
            http_res->set_success(0);
            msg = "DB ERROR|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }
        // user not exist
        if (!exist) {
            result = USER_NOT_EXIST;
            http_res->set_code(USER_NOT_EXIST);
            http_res->set_success(0);
            msg = "user not exist";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        // set session
        string sid;
        ret = Session::get_instance()->set(username, dev_id, sid);
        LOG_INFO << "sid is: " << sid << endl;
        
        if (ret == LOGIN_REPLACE) {
            result = LOGIN_REPLACE;
            http_res->set_code(LOGIN_REPLACE);
            msg = "login success and replace session";
        } else {
            result = REGIEST_SUCCESS;
            http_res->set_code(LOGIN_SUCCESS);
            msg = "login success";
        }

        // set HTTPResponse
        http_res->set_success(1);
        LOG_INFO << msg << endl;
        http_res->set_msg(msg);
        UserResponse::LoginResponse *login_res = new UserResponse::LoginResponse();
        login_res->set_username(username);
        login_res->set_sid(sid);
        http_res->set_allocated_login_response(login_res);
    } while(0);
	
    http_res->SerializeToString(&respon_data);
    const char *p = respon_data.c_str();
    strncpy(buf, p, strlen(p) + 1);
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}

/**
 * user logout
 *  
 * @method logout
 * @param {string} username username which is used for logout.
 * @param {string} sid sid which is used for logout.
 * @param {char*} buf respone data.
 * @return {int} louout status. 
 */
int logout(string username, string sid, char *buf) {
    string respon_data;
    int result;
    string msg;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();

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
        if (!Session::get_instance()->exist(username)) {
            result = SESSION_NOT_EXIST;
            http_res->set_code(SESSION_NOT_EXIST);
            http_res->set_success(0);
            msg = "session not exist";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        // remove session
        Session::get_instance()->remove(username);
        result = SESSION_OK;
        http_res->set_code(SESSION_OK);
        http_res->set_success(1);
        msg = "remove session success";
        LOG_INFO << msg << endl;
        http_res->set_msg(msg);
    } while(0);

    http_res->SerializeToString(&respon_data);
    const char *p = respon_data.c_str();
    strncpy(buf, p, strlen(p) + 1);
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}