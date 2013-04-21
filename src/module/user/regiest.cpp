#include "user.h"

/**
 * user resiest
 *  
 * @method resiest
 * @param {string} username username which is used for regiested.
 * @param {string} password password which is used for regiested.
 * @return {const char*} return respone data. 
 */
int regiest(string username, string password, char *buf) {
    string respon_data;
    data::HTTPResponse *http_res = new data::HTTPResponse();
    string msg;
    int result;
    int ret;

    do {
        LOG_INFO << "regiest params: username is " << username << " password is " << password << endl;

        // username or password not be found
        if (Tool::trim(username).empty() || Tool::trim(password).empty()) {
            result = PARAM_ERROR;
            http_res->set_code(PARAM_ERROR);
            http_res->set_success(0);
            msg = "username or password is null";
            LOG_ERROR << msg << endl;
            break;
        }

        // get database config
        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), 
            config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

        bool exist;

        ret = e.is_exist("user", "where username = '" + username + "'", exist);
        // exception
        if (ret != DB_OK) {
            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            http_res->set_success(0);
            msg = "DB ERROR|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            break;
        }
        // username already exist
        if (exist) {
            result = USERNAME_IS_EXIST;
            http_res->set_code(USERNAME_IS_EXIST);
            http_res->set_success(0);
            msg = "username is already exist";
            LOG_ERROR << msg << endl;
            break;
        }

        // save the user info to database
        map<string, string> reg_params;
        reg_params["username"] = username;
        reg_params["password"] = password;
        ret = e.insert("user", reg_params);
        // exception
        if (ret != DB_OK) {
            result = REGIEST_FAIL;
            http_res->set_code(REGIEST_FAIL);
            http_res->set_success(0);
            msg = "REGIEST_FAIL|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            break;
        }

        // set HTTPResponse
        result = REGIEST_SUCCESS;
        http_res->set_code(REGIEST_SUCCESS);
        http_res->set_success(1);
        msg = "regiest success";

        // set RegiestResponse
        user::RegiestResponse *regiest_res = new user::RegiestResponse();
        regiest_res->set_username(username);
        regiest_res->set_password(password);
        http_res->set_allocated_regiest_response(regiest_res);
        LOG_INFO << msg << endl;
    } while(0);

    http_res->set_msg(msg);
    http_res->SerializeToString(&respon_data);
    const char *p = respon_data.c_str();
    strncpy(buf, p, strlen(p) + 1);
    google::protobuf::ShutdownProtobufLibrary();
    return result;
}