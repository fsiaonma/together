#include "global.h"

long current_msec;
int efd;
epoll_event event;
int current_total_processes;

// 根据目录名自动添加 index.htm
int get_index_file(char *filename_buf, struct stat *pstat) {
	struct stat stat_buf;
	int s;
	s = lstat(filename_buf, &stat_buf);
	if (s == -1) {
    // 文件或目录不存在
		return -1;
	}
	if (S_ISDIR(stat_buf.st_mode)) {
    // 是目录，追加 index.htm(l)
		strncpy(filename_buf + strlen(filename_buf), "/index.htm", sizeof("/index.htm"));
    // 再次判断是否是文件
		s = lstat(filename_buf, &stat_buf);
		if (s == -1 || S_ISDIR(stat_buf.st_mode)) {
      // 文件不存在，或者为目录
			int len = strlen(filename_buf);
			filename_buf[len] = 'l';
			filename_buf[len + 1] = 0;
			s = lstat(filename_buf, &stat_buf);
			if (s == -1 || S_ISDIR(stat_buf.st_mode)) {
        // 文件不存在，或者为目录
				return -1;
			}
		}
	}
	*pstat = stat_buf;
	return 0;
}

int get_module_type(const char *req) {
	int ret = UNKNOWN_MODULE;
	if (strcmp(req, "USER") == 0) {
		ret = USER_MODULE;
	} else if (strcmp(req, "ROOM") == 0) {
		ret = ROOM_MODULE;
	} else if (strcmp(req, "MESSAGE") == 0) {
		ret = MESSAGE_MODULE;
	}
	return ret;
}

void time_update()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	time_t sec;
	unsigned int msec;
	sec = tv.tv_sec;
    msec = tv.tv_usec / 1000;
    current_msec = sec * 1000 + msec;
}