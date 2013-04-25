#include "room.h"

int room_handler(process *process, map<string, string> param) {
	char response_data[1024];
    if (param.count("action") == 0) {
        LOG_ERROR << "action type is not exist" << endl;
        return -1;
    }
    int action_type = Tool::S2I(param["action"]);
    LOG_INFO << "action_type: " << action_type << endl;
    switch (action_type) {
    	case ROOM_CREATE: {
    	    break ;
    	}
    	case ROOM_SHOWLIST: {
    		break ;
    	}
        case ROOM_SEARCH: {
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