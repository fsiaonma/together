#ifndef _RECV_H_
#define _RECV_H_

#include <sys/socket.h>
#include <map>
#include <errno.h>

#include "../../common/global/global.h"
#include "../../util/tool/tool.h"
#include "../../module/user/user.h"
#include "../../util/timer/timer.h"
#include "../../util/log/log.h"
#include "../../lib/session/session.h"

void handle_read_request(process *process, char *module, map<string, string> param);

map<string, string> parse_param(char *param_data);

void read_http_request(process* process);

int recv_file(process* process, const char* filename);

void read_upload_request(process* process);

void read_tcp_request(process* process);

#endif