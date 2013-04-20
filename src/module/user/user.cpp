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

        int ret;
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
        
        // save the user info
        PARAM regist_item;
        PARAMLIST regist_datas;
        regist_item.key = "username";
        regist_item.value = username;
        regist_datas.push_back(regist_item);
        regist_item.key = "password";
        regist_item.value = password;
        regist_datas.push_back(regist_item);
        ret = e.insert("user", regist_datas);

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

/**
 * user resiest
 *  
 * @method resiest
 * @param {string} username username which is used for regiested.
 * @param {string} password password which is used for regiested.
 * @return {const char*} return respone data. 
 */
const char *login(string username, string password) {
	LOG_INFO << "login params: username is " << username << " password is " << password << endl;
	Config *c = Config::get_instance();
    map<string, string> config = c->get_config();
    eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

    bool exist;
    if (e.is_exist("user", "where username = '" + username + "' and password = '" + password + "'", exist)) {
    	LOG_INFO << "login success" << endl;
    } else {
    	LOG_INFO << "login fail" << endl;
    }

    string result;
    return result.c_str();
}

int user_handler(process *process, map<string, string> param) {
	char response_data[1024];
    if (param.count("action") == 0) {
        LOG_ERROR << "action type is not exist" << endl;
        return -1;
    }
    int action_type = atoi(param["action"].c_str());
    LOG_INFO << "action_type: " << action_type << endl;
    switch (action_type) {
    	case USER_REGIEST: {
            if (param.count("username") == 0 || param.count("password") == 0) {
                LOG_ERROR << "username or password is not be found" << endl;
                return -1;
            }
    	    regiest(param["username"], param["password"], response_data);
    	    break ;
    	}
    	case USER_LOGIN: {
            if (param.count("username") == 0 || param.count("password") == 0) {
                LOG_ERROR << "username or password is not exist" << endl;
                return -1;
            }
    		// response_data = login(param["username"], param["password"]);
    		break ;
    	}
        default: {
            LOG_ERROR << "action type err" << endl;
            return -1;
        }
    }
    LOG_INFO << "length:" << strlen(response_data) << endl;

	process->buf[0] = 0; 
	write_to_header(header_200_start); // start to write header
    write_to_header("\r\n");
    write_to_header(response_data); // send data
	write_to_header(header_end); // write header end
	return 0;
}