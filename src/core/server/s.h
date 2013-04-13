#include <atomic>
#include "../../common/global/global.h"
#include "../../common/config/config.h"
#include "../../util/tool/tool.h"
#include "../../util/log/log.h"

// atomic_int is_accepting(0);

static process processes[MAX_PORCESS];
static int listen_port[LISTEN_PORT_SIZE];
static int listen_socks[LISTEN_PORT_SIZE];
int keepalive_timeout;

int CreateWorker(int nWorker);

int setNonblocking(int fd);

process* find_process_by_sock_slow(int sock);

process* find_process_by_sock(int sock);

process* find_empty_process_for_sock(int sock);

process* accept_sock(int listen_sock);

int iniConfig();

void init_processes();

static int create_and_bind(int port);

bool in_listen_sock(int sock);



void read_request(process* process);

void process_events_and_timer(epoll_event *events);

void expire_timeout_sock();

void process_events(epoll_event *events, int timer);

void handle_request(int sock, int events);

process* accept_sock(int listen_sock);

void read_request(process* process);
