#include "./recv.h"


void handle_read_request(process *process, char *module, map<string, string> param) {
	LOG << "handle_read_request" << endl;
	int module_type = get_module_type(module);
	int s;
	
	switch (module_type) {
		case USER_MODULE:
		{	
			s = user_handler(process, param);
			if (s == -1)
				break;
			else {
				process->status = STATUS_SEND_RESPONSE_HEADER;
			    // 修改此 sock 的监听状态，改为监视写状态
				event.data.fd = process->sock;
				event.events = EPOLLOUT;
				s = epoll_ctl(efd, EPOLL_CTL_MOD, process->sock, &event);
				if (s == -1) {
					ERR << "epoll_ctl error" << endl;
					abort();
				}
				LOG << "------send header------" << endl;
				LOG << process->buf << endl;
			}
			break;
		}
		case ROOM_MODULE:
		{
			//room_handler(process, req);
			break;
		}
		default:
		break;
	}
}