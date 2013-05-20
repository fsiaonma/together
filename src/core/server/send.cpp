#include "./send.h"
#include "./close.h"

/**
 * [send_response_header 发送响应首部]
 * @param process [description]
 */
void send_response_header(process *process) {
	LOG_INFO << "send|code:" << process->response_code << endl;
	if (process->response_code != 200) {
    	// 非 200 不进入 send_response
		if (process->send_length > 0)
			send(process->sock, process->buf, process->send_length, 0);  
		else 
			send(process->sock, process->buf, strlen(process->buf), 0);  
		cleanup(process);
		//update_timer(process->sock, current_msec);
	} else {
		LOG_DEBUG << "process->send_length|" << process->send_length << endl;
		LOG_DEBUG << "process->fd|" << process->fd << endl;
		if (process->type == LISTEN_HTTP_REQ_TYPE || process->type == LISTEN_UPLOAD_REQ_TYPE) {
			if (process->send_length > 0)
				send(process->sock, process->buf, process->send_length, 0);  
			else 
				send(process->sock, process->buf, strlen(process->buf), 0);  
			send_response(process);
			cleanup(process);
		}

	}
}

/**
 * [send_response 发送文件]
 * @param process [description]
 */
void send_response(process *process) {
	LOG_INFO << "send file" << endl;
	if (process->fd == NO_FILE)
		return ;
	process->read_pos = 0;
	while (1) {
		off_t offset = process->read_pos;
		sendfile(process-> sock, process -> fd, &offset, process->total_length);
		process->read_pos = offset;
		// LOG_INFO << "process->read_pos|" << process->read_pos << endl;
		if (process->read_pos == process->total_length) {
      		// 读写完毕
			return;
		}
	}

}