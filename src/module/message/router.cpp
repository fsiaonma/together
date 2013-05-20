#include "message.h"
#include "message_base.h"

int chat_handler(process *process, map<string, string> param, list<int> &send_sock_list) {
    char response_data[100];
    memset(response_data, 0, 100);
    if (param.count("action") == 0) {
        LOG_ERROR << "action type is not exist" << endl;
        return -1;
    }
    int action_type = Tool::S2I(param["action"]);
    LOG_INFO << "action_type: " << action_type << endl;
    int result;
    switch (action_type) {
    	case BIND_USER_CHAT: {
            result = _bind_user_chat(process->sock, param, send_sock_list, response_data);
            LOG_DEBUG << "_bind_user_chat result|" << process->sock << "|" << result << "|" << send_sock_list.size() << endl;
    	    break ;
    	}
        case SAVE_MSG: {
            result = save_msg(process->sock, param, send_sock_list, response_data);
            LOG_DEBUG << "SAVE_MSG result|" << process->sock << "|" << result << "|" << send_sock_list.size() << endl;
            break ;
        }
        case START_ROOM: {
            result = start_room(process->sock, param, send_sock_list, response_data);
            LOG_DEBUG << "START_ROOM result|" << process->sock << "|" << result << "|" << send_sock_list.size() << endl;
            break ;
        }
        case LC_JOIN_ROOM: {
            result = join_room(process->sock, param, send_sock_list, response_data);
            LOG_DEBUG << "JOIN_ROOM result|" << process->sock << "|" << result << "|" << send_sock_list.size() << endl;
            break ;
        }
        case LC_QUIT_ROOM: {
            result = quit_room(process->sock, param, send_sock_list, response_data);
            LOG_DEBUG << "QUIT_ROOM result|" << process->sock << "|" << result << "|" << send_sock_list.size() << endl;
            break ;
        }
        default: {
            LOG_ERROR << "action type err" << endl;
            return -1;
        }
    }
    process->buf[0] = 0; 
    write_to_header(response_data);

	return 0;
}

int message_handler(process *process, map<string, string> param) {
    char response_data[3500];
    if (param.count("action") == 0) {
        LOG_ERROR << "action type is not exist" << endl;
        return -1;
    }
    int action_type = atoi(param["action"].c_str());
    LOG_INFO << "action_type: " << action_type << endl;
    int send_len = -1;
    switch (action_type) {
        case GET_MSG: {
            if (param.count("current_id") == 0 || 
                param.count("msgs_num") == 0 ||
                param.count("recipient_id") == 0 || 
                param.count("room_id") == 0 || 
                param.count("type") == 0 ||
                param.count("get_type") == 0) {
                LOG_ERROR << "current_id or msgs_num or recipient_id or room_id or type or get_type is not exist" << endl;
                return -1;
            }
            get_msgs(param, response_data, send_len);
            break;
        }
        case CHANGE_MSG_STATUS: {
            if (param.count("msg_id") == 0 || param.count("room_id") == 0 || param.count("recipient_id") == 0) {
                LOG_ERROR << "msg_id or room_id or recipient_id is not exist" << endl;
                return -1;
            }
            change_msg_status(Tool::S2I(param["msg_id"]), Tool::S2I(param["room_id"]), Tool::S2I(param["recipient_id"]), response_data, send_len);
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