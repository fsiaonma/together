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