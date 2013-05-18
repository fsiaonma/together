#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <iostream>
#include <cstdio>
#include <string.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/epoll.h>
#include <google/protobuf/text_format.h>
#include "../const.h"

using namespace std;

extern long current_msec;

extern int efd;
extern epoll_event event;
extern int current_total_processes;

struct process {
	static const int kBufferSize = 4096;
	int sock;
	int status;
	int response_code;
	int fd;
	int read_pos;
	int write_pos;
	int total_length;
	char buf[kBufferSize];
	char md5[MD5_LEN + 1];
	char suffix[11];
	int type;
	int send_length;
	string request;
};

int get_index_file(char *filename_buf, struct stat *pstat);

int get_module_type(const char *req);

void time_update();

template<typename T>
void print_proto(const T *t)
{
	#if DEBUG
	    cout << "-------------- " << "print proto data" << " --------------" << endl; 
		string outString;
	    google::protobuf::TextFormat::PrintToString(*t ,&outString);
	    cout << outString << endl; 
	    cout << "-------------- " << "end" << " --------------" << endl; 
	#endif
}

#endif





