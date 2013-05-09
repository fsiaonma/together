#include "room.h"

int room_handler(process *process, map<string, string> param) {
	char response_data[3500];
    memset(response_data, 0, 3500);
    if (param.count("action") == 0) {
        LOG_ERROR << "action type is not exist" << endl;
        return -1;
    }
    int action_type = Tool::S2I(param["action"]);
    LOG_INFO << "action_type: " << action_type << endl;
    int send_len = -1;
    switch (action_type) {
    	case ROOM_CREATE: {
            create_room(param, response_data, send_len);
    	    break ;
    	}
    	case ROOM_SHOWLIST: {
            show_room_list(param, response_data, send_len);
    		break ;
    	}
        case ROOM_JOIN: {
            join_room(param, response_data, send_len);
            break ;
        }
        case ROOM_QUIT: {
            quit_room(param, response_data, send_len);
            break ;
        }
        case ROOM_PEOPLE_LIST: {
            show_room_peo_list(param, response_data, send_len);
            break ;
        }
        case SHOW_ROOM_INFO: {
            show_room_info(param, response_data, send_len);
            break ;
        }
        case SHOW_USER_ROOM: {
            show_user_room(param, response_data, send_len);
            break ;
        }
        default: {
            LOG_ERROR << "action type err" << endl;
            return -1;
        }
    }

	process->buf[0] = 0; 
	write_to_header(header_200_start); // start to write header
    write_to_header("\r\n");
    // write_to_header(response_data); // send data
    memcpy(process->buf + strlen(process->buf), response_data, 3500);
    if (send_len > 0)
    {
        process->send_length = send_len + strlen(header_200_start) + strlen("\r\n");
    }
	return 0;
}