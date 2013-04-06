#include "user.h"

/**
 * user resiest
 *  
 * @method resiest
 * @param {string} username username which is used for regiested.
 * @param {string} password password which is used for regiested.
 * @return {const char*} return respone data. 
 */
const char *regiest(string username, string password) {
    string result;
    data::HTTPResponse *http_res = new data::HTTPResponse();

    do
    {
        LOG << "regiest params: username is " << username << " password is " << password << endl;
        if (username.empty() || password.empty()) {
            http_res->set_code(PARAM_ERROR);
            http_res->set_success(0);
            http_res->set_msg("username or password is null");
            ERR << "username or password is null" << endl;
            break;
        }
        
        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), 
            config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

        if (e.is_exist("user", "where username = '" + username + "'")) {
            http_res->set_code(USERNAME_IS_EXIST);
            http_res->set_success(0);
            http_res->set_msg("username is already exist");
            LOG << "username is already exist" << endl;
            break;
        } else {
            PARAM regist_item;
            PARAMLIST regist_datas;
            regist_item.key = "username";
            regist_item.value = username;
            regist_datas.push_back(regist_item);
            regist_item.key = "password";
            regist_item.value = password;
            regist_datas.push_back(regist_item);
            e.insert("user", regist_datas);

            http_res->set_code(REGIEST_SUCCESS);
            http_res->set_success(1);
            http_res->set_msg("regiest success");
        }
        user::RegiestResponse *regiest_res = new user::RegiestResponse();
        regiest_res->set_username(username);
        regiest_res->set_password(password);
        http_res->set_allocated_regiest_response(regiest_res);
    } while(0);


    http_res->SerializeToString(&result);
    google::protobuf::ShutdownProtobufLibrary();
    return result.c_str();
}

const char *login(string username, string password) {
	LOG << "login params: username is " << username << " password is " << password << endl;
	Config *c = Config::get_instance();
    map<string, string> config = c->get_config();
    eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

    if (e.is_exist("user", "where username = '" + username + "' and password = '" + password + "'")) {
    	LOG << "login success" << endl;
    } else {
    	LOG << "login fail" << endl;
    }

    string result;
    return result.c_str();
}

int user_handler(process *process, map<string, string> param) {
	const char *response_data;
    int action_type = atoi(param["action"].c_str());
    LOG << "action_type: " << action_type << endl;
    switch (action_type) {
    	case USER_REGIEST: {
    	    response_data = regiest(param["username"], param["password"]);
    	    break ;
    	}
    	case USER_LOGIN: {
    		response_data = login(param["username"], param["password"]);
    		break ;
    	}
    }
    LOG << "length:" << strlen(response_data) << endl;

	process->buf[0] = 0; 
	write_to_header(header_200_start); // start to write header
    write_to_header("\r\n");
    write_to_header(response_data); // send data
	write_to_header(header_end); // write header end
	return 0;
}


