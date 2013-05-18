#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/resource.h>
#include <stdlib.h>

#include "./recv.h"
#include "./close.h"
#include "./send.h"
#include "./s.h"

int CreateWorker(int nWorker)
{
    if (0 < nWorker)
    {
        int bIsChild = 0;
        pid_t nPid;

        while (!bIsChild)
        {
            if (0 < nWorker)
            {
                nPid = fork();
                if (nPid > 0)
                {
                    bIsChild = 0;
                    --nWorker;
                }
                else if (0 == nPid)
                {
                    bIsChild = 1;
                    LOG_TRACE << "create worker " << getpid() << " success!" << endl;
                }
                else
                {
                    LOG_ERROR << "fork error: " << strerror(errno) << endl;
                    return -1;
                }
            }
            else
            {
                int nStatus;
                if (-1 == wait(&nStatus))
                {
                    ++nWorker;
                }
            }
        }
    }

    return 0;
}

/**
 * [setNonblocking 设置socket非阻塞]
 * @param  fd [socket描述符]
 * @return    [description]accept_sockaccept_sock
 */
int setNonblocking(int fd) {
	int flags;
	if (-1 ==(flags = fcntl(fd, F_GETFL, 0)))
		flags = 0;
	return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

/**
 * [find_process_by_sock_slow 从process数组中遍历查找对应socket，慢]
 * @param  sock [description]
 * @return      [对应的process]
 */
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
 * [find_empty_process_for_sock 从process数组中找空的位置]
 * @param  sock [description]
 * @return      [对应的process]
 */
process* find_empty_process_for_sock(int sock) {
	if (sock < MAX_PORCESS && sock >= 0 && processes[sock].sock == NO_SOCK) {
		return &processes[sock];
	} else {
		return find_process_by_sock_slow(NO_SOCK);
	}
}

/**
 * [find_process_by_sock 从process数组中遍历查找对应socket所在]
 * @param  sock [description]
 * @return      [对应的process]
 */
process* find_process_by_sock(int sock) {
	if (sock < MAX_PORCESS && sock >= 0 && processes[sock].sock == sock) {
		return &processes[sock];
	} else {
		return find_process_by_sock_slow(sock);
	}
}


/**
 * [iniConfig description]
 * @return [description]
 */
int iniConfig()
{
	Config *c = Config::get_instance();
	map<string, string> config = c->get_config();
	if (config.empty())
		return -1;
	listen_port[LISTEN_HTTP_REQ_TYPE] = Tool::S2I(config["HTTP_PORT"], 9080);
	listen_port[LISTEN_UPLOAD_REQ_TYPE] = Tool::S2I(config["UPLOAD_PORT"], 9081);
	listen_port[LISTEN_TCP_REQ_TYPE] = Tool::S2I(config["TCP_PORT"], 9082);
	keepalive_timeout = Tool::S2I(config["KEEPALIVE_TIMEOUT"], 5000);
	return 1;
}

/**
 * [init_processes 初始化process数组]
 */
void init_processes() {
	int i = 0;
	for (;i < MAX_PORCESS; i ++) {
		processes[i].sock = NO_SOCK;
	}
}

/**
 * [create_and_bind 创建和绑定端口]
 * @param  port [description]
 * @return      [description]
 */
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
		LOG_ERROR << "getaddrinfo: " << gai_strerror(s) << endl;
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
			LOG_INFO << port << "|" << listen_sock << "|" << "bind successfully!" << endl;
			break;
		}

		close(listen_sock);
	}

	if (rp == NULL) {
		LOG_ERROR << "Could not bind" << endl;
		return -1;
	}

	freeaddrinfo(result);

	return listen_sock;
}

/**
 * [in_listen_sock 判断当前要连接的socket是否在监察的端口]
 * @param  sock [description]
 * @return      [结果]
 */
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
 * [process_events_and_timer 事件与定时器的主循环]
 * @param events [epoll事件]
 */
void process_events_and_timer(epoll_event *events)
{
	for(;;)
	{
		long delta;
		long timer = find_timer(current_msec, keepalive_timeout);
		//LOG_INFO << "timer:" << timer << endl;
		delta = current_msec;
		process_events(events, timer);
		delta = current_msec - delta;
		if (delta) {
			expire_timeout_sock();
		}
	}
}

/**
 * [expire_timeout_sock 移除超时的socket]
 */
void expire_timeout_sock()
{
	int count = 0;
	set<CSockTime, sortByTime>::iterator iter;
	for (iter = timeSet.begin(); iter != timeSet.end(); iter++)
    {
    	long interval = current_msec - iter->getActiveTime();
    	LOG_INFO << "sock:" << iter->getSock() << ", interval:" << interval << endl;
    	if (interval < keepalive_timeout)
    	{
    		break;
    	}
    	count++;
    }

    for (int i = 0; i < count; i++)
    {
    	int sock = timeSet.begin()->getSock();
    	process* process = find_process_by_sock(sock);
    	timeSet.erase(timeSet.begin()++);
    	cleanup(process);
    }
}

/**
 * [process_events 事件处理主循环]
 * @param events [epoll事件]
 * @param timer  [epowoo wait的超时时间]
 */
void process_events(epoll_event *events, int timer)
{
	int n, i;
	n = epoll_wait(efd, events, MAXEVENTS, timer);
	if (n == -1) 
	{
		LOG_ERROR << "epoll_wait error" << endl;
		return ;
	}
	// update time
	time_update();

	for (i = 0; i < n; i++) 
	{
		if (( events[i].events & EPOLLERR) ||
			(events[i].events & EPOLLHUP)) 
		{
			LOG_ERROR << "epoll error|" << events[i].data.fd << endl;
			close(events[i].data.fd);
			continue;
		}
		handle_request(events[i].data.fd, events[i].events);
	}
	// LOG_INFO << "pid:" << getpid() << endl;
}


/**
 * [handle_request 判断事件的状态，作对应的处理]
 * @param sock   [socket]
 * @param events [事件的状态]
 */
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
 * [accept_sock 接受socket连接]
 * @param  listen_sock [监听的socket]
 * @return             [接受socket连接后的process]
 */
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
		LOG_WARN << "accept error" << endl;
		return NULL;
	}

	getnameinfo((sockaddr *)&remote_addr, in_len,
		hbuf, sizeof hbuf,
		sbuf, sizeof sbuf,
		NI_NUMERICHOST | NI_NUMERICSERV);

	s = setNonblocking(infd);
	if (s == -1)
	{
		abort();
	}

	event.data.fd = infd;
	event.events = EPOLLIN;
	s = epoll_ctl(efd, EPOLL_CTL_ADD, infd, &event);
	if (s == -1) {
		LOG_ERROR << "epoll_ctl error" << endl;
		abort();
	}
	LOG_INFO << listen_sock << "|Connect from " << inet_ntoa(remote_addr.sin_addr) << ":" << ntohs(remote_addr.sin_port) << ", socket:" << infd << endl;
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
    process->request = "";
    memset(process->md5, 0, sizeof(char) * MD5_LEN + 1);
    memset(process->buf, 0, process->kBufferSize); 
    memset(process->suffix, 0, 11); 
    process->send_length = -1;
	if (process->type == LISTEN_UPLOAD_REQ_TYPE)
	{
		process->status = STATUS_UPLOAD_READY;
	} else {
		process->status = STATUS_READ;
	}
	return NULL;
}


/**
 * [read_request 读取socket请求]
 * @param process [process对象]
 */
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

int main()
{
	int s;
	s = iniConfig();
	if (s == -1) {
		LOG_ERROR << "init config error!" << endl;
		abort();
	}
	epoll_event *events;
	init_processes();
	int listen_sock;

	for (int i = 0; i < LISTEN_PORT_SIZE; i++)
	{
		listen_sock = create_and_bind(listen_port[i]);

		s = setNonblocking(listen_sock);
		if (s == -1) {
			LOG_ERROR << "setNonblocking error!" << endl;
			abort();
		}

		s = listen(listen_sock, SOMAXCONN);
		if (s == -1) {
			LOG_ERROR << "listen error!" << endl;
			abort();
		}
		listen_socks[i] = listen_sock;
	}

	// CreateWorker(10);

	efd = epoll_create1(0);
	LOG_TRACE << "efd:" << efd << endl;
	if (efd == -1) {
		LOG_ERROR << "epoll create error!" << endl;
		abort();
	}

	for (int i = 0; i < LISTEN_PORT_SIZE; i++)
	{
		listen_sock = listen_socks[i];
		event.data.fd = listen_sock;
		event.events = EPOLLIN;
		s = epoll_ctl(efd, EPOLL_CTL_ADD, listen_sock, &event);
		if (s == -1) {
			LOG_ERROR << "epoll_ctl error" << endl;
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
