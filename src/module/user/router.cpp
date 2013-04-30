#include "user.h"

/**
 * switch the action_type, match the action_type and the function.
 *  
 * @method user_handler
 * @param {process*} process socket.
 * @param {map<string, string>} param request param.
 * @return {int} return operation status.
 */
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
            if (param.count("username") == 0 || param.count("password") == 0 || param.count("dev_id") == 0) {
                LOG_ERROR << "username or password or dev_id is not exist" << endl;
                return -1;
            }
            login(param["username"], param["password"], param["dev_id"], response_data);
    		break ;
    	}
        case USER_LOGOUT: {
            if (param.count("username") == 0 || param.count("sid") == 0) {
                LOG_ERROR << "username or sid is not exist" << endl;
                return -1;
            }
            logout(param["username"], param["sid"], response_data);
            break ;
        }
        case USER_VIEW_INFO: {
            if (param.count("username") == 0) {
                LOG_ERROR << "username is not exist" << endl;
                return -1;
            }
            view_user_info(Tool::S2I(param["uid"]), param["username"], param["sid"], response_data);
            break ;
        }
        case USER_SET_INFO: {
            if (param.count("sid") == 0) {
                LOG_ERROR << "sid is not exist" << endl;
                return -1;
            }
            set_user_info(param, param["sid"], response_data);
            break ;
        }
        case USER_PRISE: {
            if (param.count("username") == 0 || param.count("sid") == 0) {
                LOG_ERROR << "username or sid is not exist" << endl;
                return -1;
            }
            prise(param["username"], param["sid"], response_data);
            break ;
        }
        case USER_FOLLOW: {
            if (param.count("follow_id") == 0 || param.count("followed_id") == 0 || param.count("sid") == 0) {
                LOG_ERROR << "follow_id or followed_id or sid is not exist" << endl;
                return -1;
            }
            follow(Tool::S2I(param["follow_id"]), Tool::S2I(param["followed_id"]), param["sid"], response_data);
            break ;
        }
        case USER_IS_EXIST: {
            if (param.count("username") == 0) {
                LOG_ERROR << "username is not exist" << endl;
                return -1;
            }
            username_is_exist(param["username"], response_data);
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
	// write_to_header(header_end); // write header end
	return 0;
}