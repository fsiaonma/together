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
	char response_data[3500];
    if (param.count("action") == 0) {
        LOG_ERROR << "action type is not exist" << endl;
        return -1;
    }
    int action_type = atoi(param["action"].c_str());
    LOG_INFO << "action_type: " << action_type << endl;
    int send_len = -1;
    switch (action_type) {
    	case USER_REGIEST: {
            if (param.count("username") == 0 || param.count("password") == 0) {
                LOG_ERROR << "username or password is not be found" << endl;
                return -1;
            }
    	    regiest(param["username"], param["password"], response_data, send_len);
    	    break ;
    	}
    	case USER_LOGIN: {
            if (param.count("username") == 0 || param.count("password") == 0 || param.count("dev_id") == 0) {
                LOG_ERROR << "username or password or dev_id is not exist" << endl;
                return -1;
            }
            login(param["username"], param["password"], param["dev_id"], response_data, send_len);
    		break ;
    	}
        case USER_LOGOUT: {
            if (param.count("sid") == 0) {
                LOG_ERROR << "sid is not exist" << endl;
                return -1;
            }
            logout(param["sid"], response_data, send_len);
            break ;
        }
        case USER_VIEW_INFO: {
            if (param.count("visit_uid") == 0) {
                LOG_ERROR << "visit_uid is not exist" << endl;
                return -1;
            }
            view_user_info(Tool::S2I(param["visit_uid"]), param["sid"], response_data, send_len);
            break ;
        }
        case USER_SET_INFO: {
            if (param.count("sid") == 0) {
                LOG_ERROR << "sid is not exist" << endl;
                return -1;
            }
            set_user_info(param, param["sid"], response_data, send_len);
            break ;
        }
        case USER_PRISE: {
            if (param.count("uid") == 0 || param.count("sid") == 0) {
                LOG_ERROR << "uid or sid is not exist" << endl;
                return -1;
            }
            prise(Tool::S2I(param["uid"]), param["sid"], response_data, send_len);
            break ;
        }
        case USER_FOLLOW: {
            if (param.count("uid") == 0 || param.count("sid") == 0) {
                LOG_ERROR << "uid or sid is not exist" << endl;
                return -1;
            }
            follow(Tool::S2I(param["uid"]), param["sid"], response_data, send_len);
            break ;
        }
        case USER_IS_EXIST: {
            if (param.count("username") == 0) {
                LOG_ERROR << "username is not exist" << endl;
                return -1;
            }
            username_is_exist(param["username"], response_data, send_len);
            break ;
        }
        case GET_FOLLOWING_LIST: {
            if (param.count("uid") == 0 || param.count("page_no") == 0 || param.count("page_size") == 0 || param.count("sid") == 0) {
                LOG_ERROR << "uid or page_no or page_size or sid is not exist" << endl;
                return -1;
            }
            get_following_list(Tool::S2I(param["uid"]), Tool::S2I(param["page_no"]), Tool::S2I(param["page_size"]), param["sid"], response_data, send_len);
            break ;
        }
        case GET_FOLLOWERS_LIST: {
            if (param.count("uid") == 0 || param.count("page_no") == 0 || param.count("page_size") == 0 || param.count("sid") == 0) {
                LOG_ERROR << "uid or page_no or page_size or sid is not exist" << endl;
                return -1;
            }
            get_followers_list(Tool::S2I(param["uid"]), Tool::S2I(param["page_no"]), Tool::S2I(param["page_size"]), param["sid"], response_data, send_len);
            break ;
        }
        case USER_UNFOLLOW: {
            if (param.count("uid") == 0 || param.count("sid") == 0) {
                LOG_ERROR << "uid or sid is not exist" << endl;
                return -1;
            }
            unfollow(Tool::S2I(param["uid"]), param["sid"], response_data, send_len);
            break ;
        }
        case GET_MSG_LIST: {
            if (param.count("recipient_id") == 0) {
                LOG_ERROR << "recipient_id is not exist" << endl;
                return -1;
            }
            get_msg_list(Tool::S2I(param["recipient_id"]), response_data, send_len);
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
    memcpy(process->buf + strlen(process->buf), response_data, 3500);
    if (send_len > 0) {
        process->send_length = send_len + strlen(header_200_start) + strlen("\r\n");
    }
	return 0;
}