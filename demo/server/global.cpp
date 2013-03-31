#include "global.h"
long current_msec;

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

int get_module_type(char *req) {
	// TODO::
	if (USER_MODULE == 100) {
		return USER_MODULE;
	} else if (ROOM_MODULE == 200) {
		return ROOM_MODULE;
	}
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

int calc_file_MD5(char *file_name, char *md5_sum)
{
    #define MD5SUM_CMD_FMT "md5sum %." STR(PATH_LEN) "s 2>/dev/null"
    char cmd[PATH_LEN + sizeof (MD5SUM_CMD_FMT)];
    sprintf(cmd, MD5SUM_CMD_FMT, file_name);
    #undef MD5SUM_CMD_FMT

    FILE *p = popen(cmd, "r");
    if (p == NULL) return 0;

    int i, ch;
    for (i = 0; i < MD5_LEN && isxdigit(ch = fgetc(p)); i++) {
        *md5_sum++ = ch;
    }

    *md5_sum = '\0';
    pclose(p);
    return i == MD5_LEN;
}