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
            LOG_DEBUG << "_bind_user_chat result|" << result << "|" << send_sock_list.size() << endl;
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
    char response_data[100];
    memset(response_data, 0, 100);
    if (param.count("action") == 0) {
        LOG_ERROR << "action type is not exist" << endl;
        return -1;
    }
    int action_type = Tool::S2I(param["action"]);
    LOG_INFO << "action_type: " << action_type << endl;
    int result;
    int send_len = -1;
    switch (action_type) {
        // case GET_FOLLOW_UP_MSG: {
        //     if (param.count("current_id") == 0 || param.count("sender_id") == 0 || param.count("recipient_id") == 0) {
        //         LOG_ERROR << "current_id or sender_id or recipient_id is not exist" << endl;
        //         return -1;
        //     }
        //     get_follow_up_msg(Tool::S2I(param["current_id"]), Tool::S2I(param["sender_id"]), Tool::S2I(param["recipient_id"]), response_data, send_len);
        //     break;
        // }
        // case GET_PREVIOUS_MSG: {
        //     if (param.count("current_id") == 0 || param.count("msgs_num") || param.count("sender_id") == 0 || param.count("recipient_id") == 0) {
        //         LOG_ERROR << "current_id or msgs_num or sender_id or recipient_id is not exist" << endl;
        //         return -1;
        //     }
        //     get_previous_msg(Tool::S2I(param["current_id"]), Tool::S2I(param["msgs_num"]), Tool::S2I(param["sender_id"]), Tool::S2I(param["recipient_id"]), response_data, send_len);
        //     break ;
        // }
        default: {
            LOG_ERROR << "action type err" << endl;
            return -1;
        }
    }
    process->buf[0] = 0; 
    write_to_header(response_data);

    return 0;
}