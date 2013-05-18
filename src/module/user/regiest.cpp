#include "user.h"

/**
 * user resiest
 *  
 * @method resiest
 * @param {string} username username which is used for regiested.
 * @param {string} password password which is used for regiested.
 * @param {char *} buf respone data.
 * @return {int} regiest status. 
 */
int regiest(string username, string password, char *buf, int &send_len) {
    string respon_data;
    Response::HTTPResponse *http_res = new Response ::HTTPResponse();
    string msg;
    int result;
    int ret;

    do {
        LOG_INFO << "regiest params: username is " << username << " password is " << password << endl;

        // username or password not be found
        if (Tool::trim(username).empty() || Tool::trim(password).empty()) {
            result = PARAM_ERROR;
            _set_http_head(result, false, "username or password is null", http_res);
            break;
        }

        // get database config
        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), 
            config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

        bool exist;

        ret = e.is_exist("t_user", "where username = '" + username + "'", exist);
        // exception
        if (ret != DB_OK) {
            result = DB_ERROR;
            _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
            break;
        }
        // username already exist
        if (exist) {
            result = USERNAME_IS_EXIST;
            _set_http_head(result, false, "username is already exist", http_res);
            break;
        }

        // save the user info to database
        map<string, string> reg_params;
        reg_params["username"] = Tool::mysql_filter(username);
        reg_params["password"] = Tool::mysql_filter(password);
        int insert_id = -1;
        ret = e.insert("t_user", reg_params, insert_id);
        // exception
        if (ret != DB_OK) {
            result = REGIEST_FAIL;
            _set_http_head(result, false, "REGIEST_FAIL|" + Tool::toString(ret), http_res);
            break;
        }

        // set HTTPResponse
        result = REGIEST_SUCCESS;
        _set_http_head(result, true, "regiest success", http_res);
    } while(0);

    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    memcpy(buf, respon_data.c_str(), respon_data.length());
    send_len = respon_data.length();
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}

/**
 * check whether the username is exist or not
 *  
 * @method username_is_exist
 * @param {string} username username which is used for checking whether the username is exist or not.
 * @param {char *} buf respone data.
 * @return {int} username_is_exist status. 
 */
int username_is_exist(string username, char *buf, int &send_len) {
    string respon_data;
    Response::HTTPResponse *http_res = new Response ::HTTPResponse();
    string msg;
    int result;
    int ret;

    do {
        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), 
            config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

        bool exist;

        ret = e.is_exist("t_user", "where username = '" + username + "'", exist);
        // exception
        if (ret != DB_OK) {
            result = DB_ERROR;
            _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
            break;
        }
        // username already exist
        if (exist) {
            result = USERNAME_IS_EXIST;
            _set_http_head(result, false, "username is already exist", http_res);
            break;
        }

        result = USERNAME_AVAILABLE;
        _set_http_head(result, true, "username is available", http_res);
        UserResponse::UsernameExistResponse *username_exist_response = new UserResponse::UsernameExistResponse();
        username_exist_response->set_is_exist(exist);
        http_res->set_allocated_exist_username_response(username_exist_response);
    } while(0);

    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    memcpy(buf, respon_data.c_str(), respon_data.length());
    send_len = respon_data.length();
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}