#include "./send.h"
#include "./close.h"

/**
*发送响应首部
**/
void send_response_header(process *process) {
	LOG << "send" << endl;
	if (process->response_code != 200) {
    	// 非 200 不进入 send_response
		send(process->sock, process->buf, strlen(process->buf), 0);  
		cleanup(process);
		//update_timer(process->sock, current_msec);
	} else {
		// 写入完毕
		send(process->sock, process->buf, strlen(process->buf), 0);
		send_response(process);
		// TODO::
		if (process->type == LISTEN_HTTP_REQ_TYPE)
			update_timer(process->sock, current_msec);
		else if (process->type == LISTEN_UPLOAD_REQ_TYPE)
			cleanup(process);
	}
}

/**
*发送文件
**/
void send_response(process *process) {
	if (process->fd == NO_FILE)
		return ;
	while (1) {
		off_t offset = process->read_pos;
		sendfile(process-> sock, process -> fd, &offset, process->total_length);
		process->read_pos = offset;
		if (process->read_pos == process->total_length) {
      		// 读写完毕
			return;
		}
	}

}