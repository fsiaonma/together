#include "../../common/global/global.h"
#include "../../util/log/log.h"

static process processes[MAX_PORCESS];
static int efd;
static epoll_event event;
static int current_total_processes;
static int listen_port[LISTEN_PORT_SIZE] = {LISTEN_HTTP_REQ_PORT, LISTEN_UPLOAD_REQ_PORT, LISTEN_TCP_REQ_PORT};
static int listen_socks[LISTEN_PORT_SIZE];

int setNonblocking(int fd);

process* find_process_by_sock(int sock);

process* accept_sock(int listen_sock);


void cleanup(process *process);

void handle_error(process *process, const char* error_string);

void reset_process(process *process);


void handle_read_request(process *process, char *req);

void read_request(process* process);

void read_http_request(process* process);

void read_tcp_request(process* process);

void read_upload_request(process* process);


void send_response_header(process *process);

void send_response(process *process);


void process_events_and_timer(epoll_event *events);

void process_events(epoll_event *events, int timer);

void expire_timeout_sock();
