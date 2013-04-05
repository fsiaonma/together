#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <sys/sendfile.h>

#include "./s.h"
#include "../../module/user/user.h"
#include "../../util/timer/timer.h"

/**
*
**/

/**
*处理请求内容
**/
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

/**
*设置socket非阻塞
**/
int setNonblocking(int fd) {
	int flags;
	if (-1 ==(flags = fcntl(fd, F_GETFL, 0)))
		flags = 0;
	return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

/**
*从process数组中遍历查找对应socket，慢
**/
process* find_process_by_sock_slow(int sock) {
	int i;
	for (i = 0; i < MAX_PORCESS; i++) {
		if (processes[i].sock == sock) {
			return &processes[i];
		}
	}
	return 0;
}

/**
*从process数组中找空的位置
**/
process* find_empty_process_for_sock(int sock) {
	if (sock < MAX_PORCESS && sock >= 0 && processes[sock].sock == NO_SOCK) {
		return &processes[sock];
	} else {
		return find_process_by_sock_slow(NO_SOCK);
	}
}

/**
*从process数组中遍历查找对应socket所在
**/
process* find_process_by_sock(int sock) {
	if (sock < MAX_PORCESS && sock >= 0 && processes[sock].sock == sock) {
		return &processes[sock];
	} else {
		return find_process_by_sock_slow(sock);
	}
}

map<string, string> parse_param(char *param_data)
{
	char *p;
	char *buf1 = param_data;
	  
	char *outer_ptr = NULL;
	char *inner_ptr = NULL;

	int k;
	string key;
	map<string, string> m;
	while((p=strtok_r(buf1, "&", &outer_ptr))!=NULL)
	{
		buf1=p;
		k = 0;
		while((p=strtok_r(buf1, "=", &inner_ptr))!=NULL)
		{
			k++;
			if (k == 1) {
				key.assign(p);
			} else if (k == 2) {
				m.insert(pair<string, string>(key, p));
				break;
			}
			buf1=NULL;
		}  
		buf1=NULL;
	}
    map<string, string>::iterator it;
    for (it = m.begin(); it != m.end(); it++)
    {
        LOG << "key:" << it->first << "|val:" << it->second << endl;
    }
	return m;
}

/**
*重置一个process中的当前读写位置
**/
void reset_process(process* process) {
	process->read_pos = 0;
	process->write_pos = 0;
}

/**
*接受socket连接
**/
process* accept_sock(int listen_sock) {
	int s;
	sockaddr_in remote_addr;
	socklen_t in_len;
	int infd;
	char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

	// TODO:: 当请求已满时的处理

	in_len = sizeof(struct sockaddr_in);
	infd = accept(listen_sock, (sockaddr *)&remote_addr, &in_len);
	if (infd == -1) {
		ERR << "accept error" << endl;
		return NULL;
	}

	getnameinfo((sockaddr *)&remote_addr, in_len,
		hbuf, sizeof hbuf,
		sbuf, sizeof sbuf,
		NI_NUMERICHOST | NI_NUMERICSERV);

	s = setNonblocking(infd);
	if (s == -1)
		abort();

	event.data.fd = infd;
	event.events = EPOLLIN;
	s = epoll_ctl(efd, EPOLL_CTL_ADD, infd, &event);
	if (s == -1) {
		//ERR << "epoll_ctl error" << endl;
		abort();
	}
	LOG << "Connect from " << inet_ntoa(remote_addr.sin_addr) << ":" << ntohs(remote_addr.sin_port) << ", socket:" << infd << endl;
	process* process = find_empty_process_for_sock(infd);
	current_total_processes++;
	reset_process(process);
	
	for (int i = 0; i < LISTEN_PORT_SIZE; i++)
	{
		if (listen_socks[i] == listen_sock) {
			process->type = i;
			break;
		}
	}
	process->sock = infd;
    process->fd = NO_FILE;
    process->total_length = 0;
    memset(process->md5, 0, sizeof(char) * MD5_LEN + 1); 
	if (process->type == LISTEN_UPLOAD_REQ_TYPE)
	{
		process->status = STATUS_UPLOAD_READY;
	} else {
		process->status = STATUS_READ;
	}
	return NULL;
}

/**
*接收HTTP请求(LISTEN_HTTP_REQ_PORT端口)
**/
void read_http_request(process* process)
{
	int sock = process->sock;
	char* buf = process->buf;
	char read_complete = 0;

	ssize_t count;

	while (1) {
		count = recv(sock, buf + process->read_pos, process->kBufferSize - process->read_pos, MSG_DONTWAIT);
		if (count == -1) {
			break;
		} else if (count == 0) {
	    	// 被客户端关闭连接
	    	LOG << "client " << process->sock << " close connection" << endl;
			del_timer(process->sock);
			cleanup(process);
			return;
		} else if (count > 0) {
			process->read_pos += count;
		}
	}

	int header_length = process->read_pos;
	LOG << "-----recv-----" << endl;
	LOG << "from sock:" << process->sock << " type:" << process->type << endl;
	buf[header_length]=0;
	LOG << buf << endl;
  	// 请求超长，不处理了
	if (header_length > process->kBufferSize - 1) {
		process->response_code = 400;
		process->status = STATUS_SEND_RESPONSE_HEADER;
    	strncpy(process->buf, header_400, sizeof(header_400));
		send_response_header(process);
		handle_error(processes, "bad request");
		return;
	}
	buf[header_length]=0;
	#if 0
	read_complete =(strstr(buf, "\n\n") != 0) ||(strstr(buf, "\r\n\r\n") != 0);
	#else
	read_complete = 1;
	#endif
	if (read_complete) {
    	// 重置读取位置
		reset_process(process);
		// 传输格式的位置 POST的时候format_pos=4,GET的时候format_post=3
		int format_pos = -1;
		if (strncmp(buf, "POST", 4) == 0) {
    		format_pos = 4;
		} else if (strncmp(buf, "GET", 3) == 0) {
    		format_pos = 3;
		}
		LOG << "format_pos|" << format_pos << endl;
		if (format_pos < 0)
		{
			process->response_code = 400;
			process->status = STATUS_SEND_RESPONSE_HEADER;
	    	strncpy(process->buf, header_400, sizeof(header_400));
			send_response_header(process);
			handle_error(processes, "bad request");
			return;
		}

		// 解析第一行
		const char *n_loc = strchr(buf, '\n');
		const char *space_loc = strchr(buf + format_pos + 1, ' ');
		if (n_loc <= space_loc) {
			ERR << "read first line error" << endl;
			process->response_code = 400;
			process->status = STATUS_SEND_RESPONSE_HEADER;
	    	strncpy(process->buf, header_400, sizeof(header_400));
			send_response_header(process);
			handle_error(processes, "bad request");
			return;
		}

		// 解析出模块名
		char module[50];
		int module_len = space_loc - buf - (format_pos + 2);
		strncpy(module, buf + (format_pos + 2), module_len);
		module[module_len] = 0;
		LOG << "module name|" << module << endl;


		// 如果首部有Content-Length就解析出来
		int content_length = -1;
		char temp[10];
		char *c = strstr(buf, HEADER_CONTENT_LENGTH);
		if (c != 0)
		{
		    char *rn = strchr(c, '\r');
		    if (rn == 0)
		    {
		        rn = strchr(c, '\n');
		        if (rn == 0)
		        {
		        	ERR << "not found line break" << endl;
					process->response_code = 400;
					process->status = STATUS_SEND_RESPONSE_HEADER;
			    	strncpy(process->buf, header_400, sizeof(header_400));
					send_response_header(process);
					handle_error(processes, "bad request");
					return;
		        }
		    }
		    int l = rn - c - sizeof(HEADER_CONTENT_LENGTH) + 1;
		    strncpy(temp, c + sizeof(HEADER_CONTENT_LENGTH) - 1, l);
		    temp[l] = 0;
		}
		LOG << "Content-Length|" << temp << endl;
		content_length = atoi(temp);

		// 解析最后一行
		int request_len = strlen(buf);

		int last_line_begin = 0;
		int count = 0;
		int i = request_len - 1;
		int last_line_end = i;
		for (; i >= 0; i--)
		{
		    if (*(buf + i) == '\n')
		    {
		    	if (last_line_begin == 0)
		        {
		            last_line_begin = i + 1;
		            break;
		        }
		    }
		}

		char param_data[200];
		int param_len = last_line_end - last_line_begin + 1;
		strncpy(param_data, buf + last_line_begin, param_len);
		param_data[param_len] = 0;
		LOG << "param data|" << param_data << endl;

		// 最后一行长度为0则视为数据出错
		if (param_len == 0)
		{
			ERR << "receive data is null" << endl;
			process->response_code = 400;
			process->status = STATUS_SEND_RESPONSE_HEADER;
		    strncpy(process->buf, header_400, sizeof(header_400));
			send_response_header(process);
			handle_error(processes, "bad request");
			return;
		}

		// 如果首部有Content-Length,就比较与当前接收到的数据长度是否一致
		if (content_length > 0)
		{
			if (content_length != strlen(param_data))
			{
				ERR << "receive data size not same" << endl;
				process->response_code = 400;
				process->status = STATUS_SEND_RESPONSE_HEADER;
		    	strncpy(process->buf, header_400, sizeof(header_400));
				send_response_header(process);
				handle_error(processes, "bad request");
				return;
			} else {
				LOG << "receive data size same" << endl;
			}
		}

		// 解析参数
		map<string, string> param = parse_param(param_data);
		if (param.empty())
		{
			ERR << "param is null" << endl;
			process->response_code = 400;
			process->status = STATUS_SEND_RESPONSE_HEADER;
		    strncpy(process->buf, header_400, sizeof(header_400));
			send_response_header(process);
			handle_error(processes, "bad request");
			return;
		}


		process->response_code = 200;
		handle_read_request(process, module, param);
	}
}

/**
*接收文件数据,保存到硬盘
**/
int recv_file(process* process, const char* filename) 
{ 
    int rval; 
    int read_total = 0;
    char *buf = process->buf; 
    int sock = process->sock;
    FILE *file = fopen(filename, "a+b"); 
    if (!file)
    {
        ERR << "Can't open file for writing" << endl;
        return -1;
    }

    do
    {
        rval = recv(sock, buf, sizeof(buf), 0);
        if (rval < 0)
        {
            if (errno != EAGAIN) {
	            ERR << "Can't read from socket" << "|" << rval << "|" << errno << endl;
	            fclose(file);
	            return -1;
            } else {
            	read_total += rval;
            	fclose(file);
	            return read_total;
            }
        }
        if (rval == 0)
            break;
        int off = 0;
        do
        {
            int written = fwrite(&buf[off], 1, rval - off, file);
            if (written < 1)
            {
                ERR << "Can't write to file" << endl;
                fclose(file);
                return read_total;
            }
            off += written;
        }while (off < rval);
        read_total += rval;
    } while(1);

    fclose(file); 
    return read_total;
} 


/**
*接收HTTP请求,解析后开始接收文件数据,保存(LISTEN_UPLOAD_REQ_PORT端口)
**/
void read_upload_request(process* process)
{
	int s;
	LOG << "RECV|" << process->status << endl;
	switch(process->status)
	{
		case STATUS_UPLOAD_READY:
		{
			LOG << "STATUS_UPLOAD_READY" << endl;
			int sock = process->sock;
			char* buf = process->buf;
			ssize_t count;
			while (1) {
				count = recv(sock, buf + process->read_pos, process->kBufferSize - process->read_pos, MSG_DONTWAIT);
				if (count == -1) {
					break;
				} else if (count == 0) {
			    	// 被客户端关闭连接
			    	LOG << "client " << process->sock << " close connection" << endl;
					cleanup(process);
					return;
				} else if (count > 0) {
					process->read_pos += count;
				}
			}
			int header_length = process->read_pos;
			LOG << "-----recv-----" << endl;
			LOG << "from sock:" << process->sock << " type:" << process->type << endl;
			buf[header_length]=0;
			LOG << buf << endl;
			
			// TODO:: 解析HTTP请求并设置好对应的文件总长度和md5
			process->total_length = 4500053;
			char md5[] = "cefcb8e6d025249ad9156f30c0c7fe8c";
			strncpy(process->md5, md5, 33);
			process->status = STATUS_UPLOAD_ONGOING;
			break;
		}
		case STATUS_UPLOAD_ONGOING:
		{
			LOG << "STATUS_UPLOAD_ONGOING" << endl;
			const char *file_name = "./test.bmp";
			s = recv_file(process, file_name);
			LOG << "recv file " << s << endl;
			if (s < 0)
			{
				// TODO::
				process->response_code = 400;
				process->status = STATUS_SEND_RESPONSE_HEADER;
		    	strncpy(process->buf, header_400, sizeof(header_400));
				send_response_header(process);
				handle_error(processes, "bad request");
				break;
			}
			if (s == process->total_length)
			{
				LOG << "recv file finish" << endl;
				process->status = STATUS_UPLOAD_FINISHED;
				LOG << process->status << endl;
			} else {
				break;
			}
		}
		case STATUS_UPLOAD_FINISHED:
		{
			LOG << "STATUS_UPLOAD_FINISHED" << endl;
		    // TODO::保存文件成功,之后判断接收到的文件MD5与预期的是否一样,一样的话就写入数据库.返回响应信息
    		LOG << "save file succ!" << endl;
    		char md5[MD5_LEN + 1];
    		if (calc_file_MD5("./test.bmp", md5))
    		{
    			LOG << "Calc Success! MD5 sum :" << md5 << endl;
    			if (strcmp(md5, process->md5) == 0)
    			{
	    			LOG << "Success! MD5 sum is consistent" << endl;
	    			process->response_code = 200;
				    memset(process->buf, 0, sizeof(char) * process->kBufferSize); 
				    process->buf[0] = 0;
					write_to_header(header_200_start);
					write_to_header("\r\n");
					write_to_header("SUCC");
					write_to_header(header_end);
					process->status = STATUS_SEND_RESPONSE_HEADER;

					// 修改此 sock 的监听状态，改为监视写状态
					event.data.fd = process->sock;
					event.events = EPOLLOUT;
					s = epoll_ctl(efd, EPOLL_CTL_MOD, process->sock, &event);
					if (s == -1) {
						ERR << "epoll_ctl error" << endl;
						abort();
					}
    			} else {
				// MD5不一致
	    			LOG << "Fail! MD5 sum is inconsistent" << endl;
					process->response_code = 400;
					process->status = STATUS_SEND_RESPONSE_HEADER;
			    	strncpy(process->buf, header_400, sizeof(header_400));
					send_response_header(process);
					handle_error(processes, "bad request");
    			}
    		} else {
    			// TODO::计算MD5失败
    			ERR << "Calc MD5 ERROR" << endl;
				process->response_code = 400;
				process->status = STATUS_SEND_RESPONSE_HEADER;
			    strncpy(process->buf, header_400, sizeof(header_400));
				send_response_header(process);
				handle_error(processes, "bad request");
    		}
    		process->status = STATUS_UPLOAD_READY;
			break;
		}
		default:
		break;
	}
}

/**
*接收长连接请求(LISTEN_TCP_REQ_PORT端口)
**/
void read_tcp_request(process* process)
{
	int sock = process->sock;
	char* buf = process->buf;
	char read_complete = 0;

	ssize_t count;

	while (1) {
		count = recv(sock, buf + process->read_pos, process->kBufferSize - process->read_pos, MSG_DONTWAIT);
		if (count == -1) {
			break;
		} else if (count == 0) {
	    	// 被客户端关闭连接
			del_timer(process->sock);
			cleanup(process);
			return;
		} else if (count > 0) {
			process->read_pos += count;
		}
	}
	int header_length = process->read_pos;
	LOG << "-----recv-----" << endl;
	LOG << "from sock:" << process->sock << " type:" << process->type << endl;
	buf[header_length]=0;
	LOG << buf << endl;
  	// 请求超长，不处理了
	if (header_length > process->kBufferSize - 1) {
		process->response_code = 400;
		process->status = STATUS_SEND_RESPONSE_HEADER;
    	strncpy(process->buf, header_400, sizeof(header_400));
		send_response_header(process);
		handle_error(processes, "bad request");
		return;
	}
	#if 0
	read_complete =(strstr(buf, "\n\n") != 0) ||(strstr(buf, "\r\n\r\n") != 0);
	#else
	read_complete = 1;
	#endif
	if (read_complete) {
    	// 重置读取位置
		reset_process(process);
		process->response_code = 200;
		// handle_read_request(process, buf);
	}
}


/**
*读取socket请求
**/
void read_request(process* process) {
	int sock_type = process->type;

	switch(sock_type) {
		case LISTEN_HTTP_REQ_TYPE:
		{
			read_http_request(process);
			break;
		}
		case LISTEN_UPLOAD_REQ_TYPE:
		{
			read_upload_request(process);
			break;
		}
		case LISTEN_TCP_REQ_TYPE:
		{
			read_tcp_request(process);
			break;
		}
		default:
		break;
	}
}

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

/**
*清空一个process
**/
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
	// del_timer(process->sock);
}

/**
*socket出错时的处理
**/
void handle_error(process* process, const char* error_string) {
	del_timer(process->sock);
	cleanup(process);
	ERR << error_string << endl;
}

bool in_listen_sock(int sock)
{
	for (int i = 0; i < LISTEN_PORT_SIZE; i++)
	{
		if (sock == listen_socks[i])
			return true;
	}
	return false;
}

/**
*判断事件的状态，作对应的处理
**/
void handle_request(int sock, int events) {
	process* process = find_process_by_sock(sock);
	if (in_listen_sock(sock) > 0) {
		accept_sock(sock);
	} 
	else if (events & EPOLLIN){
		read_request(process);
	}
	else if (events & EPOLLOUT){
		send_response_header(process);
		process->status = STATUS_READ;
		event.data.fd = process->sock;
		event.events = EPOLLIN;
		epoll_ctl(efd, EPOLL_CTL_MOD, process->sock, &event);
	}
}

/**
*创建和绑定端口
**/
static int create_and_bind(int port) {
	addrinfo hints;
	addrinfo *result, *rp;
	int s, listen_sock;
	char _port[5];
	sprintf(_port, "%d", port);

	memset(&hints, 0, sizeof(addrinfo));
  	hints.ai_family = AF_UNSPEC;
  	hints.ai_socktype = SOCK_STREAM;
  	hints.ai_flags = AI_PASSIVE;

	s = getaddrinfo(NULL, _port, &hints, &result);
	if (s != 0) {
		ERR << "getaddrinfo: " << gai_strerror(s) << endl;
		return -1;
	}

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		listen_sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		int opt = 1;
		setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
		if (listen_sock == -1)
			continue;

		s = bind(listen_sock, rp->ai_addr, rp->ai_addrlen);
		if (s == 0) {
			LOG << port << "|" << listen_sock << "|" << "bind successfully!" << endl;
			break;
		}

		close(listen_sock);
	}

	if (rp == NULL) {
		ERR << "Could not bind" << endl;
		return -1;
	}

	freeaddrinfo(result);

	return listen_sock;
}

/**
*初始化process数组
**/
void init_processes() {
	int i = 0;
	for (;i < MAX_PORCESS; i ++) {
		processes[i].sock = NO_SOCK;
	}
}

/**
*移除超时的socket
**/
void expire_timeout_sock()
{
	int count = 0;
	set<CSockTime, sortByTime>::iterator iter;
	for (iter = timeSet.begin(); iter != timeSet.end(); iter++)
    {
    	long interval = current_msec - iter->getActiveTime();
    	LOG << "sock:" << iter->getSock() << ", interval:" << interval << endl;
    	if (interval < keepalive_timeout)
    	{
    		break;
    	}
    	count++;
    }
    // LOG << "overtime count:" << count << endl;
    // del sock
    for (int i = 0; i < count; i++)
    {
    	int sock = timeSet.begin()->getSock();
    	process* process = find_process_by_sock(sock);
    	timeSet.erase(timeSet.begin()++);
    	cleanup(process);
    }
}

/**
*事件与定时器的主循环
**/
void process_events_and_timer(epoll_event *events)
{
	for(;;)
	{
		long delta;
		long timer = find_timer(current_msec, keepalive_timeout);
		//LOG << "timer:" << timer << endl;
		delta = current_msec;
		process_events(events, timer);
		delta = current_msec - delta;
		if (delta) {
			expire_timeout_sock();
		}
	}
}

/**
*事件处理主循环
**/
void process_events(epoll_event *events, int timer)
{
	int n, i;
	n = epoll_wait(efd, events, MAXEVENTS, timer);
	if (n == -1) 
	{
		ERR << "epoll_wait error" << endl;
		return ;
	}
	// update time
	time_update();

	for (i = 0; i < n; i++) 
	{
		if (( events[i].events & EPOLLERR) ||
			(events[i].events & EPOLLHUP)) 
		{
			ERR << "epoll error|" << events[i].data.fd << endl;
			close(events[i].data.fd);
			continue;
		}
		handle_request(events[i].data.fd, events[i].events);
	}
}

void iniConfig()
{
	Config *c = Config::get_instance();
	map<string, string> config = c->get_config();
	listen_port[LISTEN_HTTP_REQ_TYPE] = Tool::S2I(config["HTTP_PORT"], 9080);
	listen_port[LISTEN_UPLOAD_REQ_TYPE] = Tool::S2I(config["UPLOAD_PORT"], 9081);
	listen_port[LISTEN_TCP_REQ_TYPE] = Tool::S2I(config["TCP_PORT"], 9082);
	keepalive_timeout = Tool::S2I(config["KEEPALIVE_TIMEOUT"], 5000);
}

int main()
{
	int s;
	iniConfig();
	epoll_event *events;
	init_processes();
	int listen_sock;

	for (int i = 0; i < LISTEN_PORT_SIZE; i++)
	{
		listen_sock = create_and_bind(listen_port[i]);

		s = setNonblocking(listen_sock);
		if (s == -1) {
			ERR << "setNonblocking error!" << endl;
			abort();
		}

		s = listen(listen_sock, SOMAXCONN);
		if (s == -1) {
			ERR << "listen error!" << endl;
			abort();
		}
		listen_socks[i] = listen_sock;
	}

	efd = epoll_create1(0);
	LOG << "efd:" << efd << endl;
	if (efd == -1) {
		ERR << "epoll create error!" << endl;
		abort();
	}

	for (int i = 0; i < LISTEN_PORT_SIZE; i++)
	{
		listen_sock = listen_socks[i];
		event.data.fd = listen_sock;
		event.events = EPOLLIN;
		s = epoll_ctl(efd, EPOLL_CTL_ADD, listen_sock, &event);
		if (s == -1) {
			ERR << "epoll_ctl error" << endl;
			abort();
		}
	}


	events = new epoll_event[MAXEVENTS];

	process_events_and_timer(events);

	free(events);

	for (int i = 0; i < LISTEN_PORT_SIZE; i++)
	{
		close(listen_socks[i]);
	}
	Config::del_instance();
	return 0;
}
