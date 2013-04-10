#include "./close.h"

/**
 * [cleanup 清空一个process]
 * @param process [process对象]
 */
void cleanup(process *process) {
	LOG << "cleanup" << endl;
	int s;
	if (process->sock != NO_SOCK) {
		LOG << "close sock:" << process->sock << endl;
		s = close(process->sock);
		current_total_processes--;
		if (s == NO_SOCK) {
			ERR << "close sock" << endl;
		}
	}
	if (process->fd != -1) {
		s = close(process->fd);
		if (s == NO_FILE) {
			ERR << "fd: " << process->fd << " close file error" << endl;
		}
	}
	process->sock = NO_SOCK;
	process->fd = NO_FILE;
	process->type = NO_TYPE;
	process->status = NO_STATUS;
	memset(process->md5, 0, sizeof(char) * MD5_LEN + 1); 
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
	ERR << error_string << endl;
}

/**
 * [reset_process 重置一个process中的当前读写位置]
 * @param process [process对象]
 */
void reset_process(process* process) {
	process->read_pos = 0;
	process->write_pos = 0;
}
