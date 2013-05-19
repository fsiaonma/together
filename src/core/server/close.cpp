#include "./close.h"

/**
 * [cleanup 清空一个process]
 * @param process [process对象]
 */
void cleanup(process *process) {
	LOG_INFO << "cleanup" << endl;
	int s;
	if (process->sock != NO_SOCK) {
		LOG_INFO << "close sock:" << process->sock << endl;
		s = close(process->sock);
		current_total_processes--;
		if (s == NO_SOCK) {
			LOG_ERROR << "close sock" << endl;
		}
	}
	if (process->fd != -1) {
		s = close(process->fd);
		if (s == NO_FILE) {
			LOG_ERROR << "fd: " << process->fd << " close file error" << endl;
		}
	}
	process->sock = NO_SOCK;
	process->fd = NO_FILE;
	process->type = NO_TYPE;
	process->status = NO_STATUS;
	process->request = "";
	process->send_length = -1;
	memset(process->md5, 0, sizeof(char) * MD5_LEN + 1); 
    memset(process->suffix, 0, 11); 
	reset_process(process);
}

/**
 * [handle_error socket出错时的处理]
 * @param process      [process对象]
 * @param error_string [错误字符串]
 */
void handle_error(process* process, const char* error_string) {
	del_timer(process->sock);
	cleanup(process);
	LOG_ERROR << error_string << endl;
}

/**
 * [reset_process 重置一个process中的当前读写位置]
 * @param process [process对象]
 */
void reset_process(process* process) {
	process->read_pos = 0;
	process->write_pos = 0;
}
