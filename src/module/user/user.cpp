#include "user.h"

int user_handler(process *process, map<string, string> param) {
	int s;
	map<string, string>::iterator it;
    for (it = param.begin(); it != param.end(); it++)
    {
        LOG << "key:" << it->first << "|val:" << it->second << endl;
    }

	// 开始 header
	process->buf[0] = 0;
	write_to_header(header_200_start);
	#if 0 //send file
	char *file = "/home/kc/code/t.bmp";
	struct stat filestat;
	s = get_index_file(file, &filestat);
	int fd = open(file, O_RDONLY);
	process->fd = fd;
	process->total_length = filestat.st_size;
	char tempstring[30];
	{
		if (process->response_code == 200) {
        // 写入 content 长度
			snprintf(tempstring, sizeof(tempstring), "Content-Length: %ld\r\n", filestat.st_size);
			write_to_header(tempstring);
		}
	}
	#else 
	//send data
    write_to_header("\r\n");
    write_to_header("USER_MODULE");
    #endif

    // 结束 header
	write_to_header(header_end);
}
