#ifndef _RECV_H_
#define _RECV_H_

#include <sys/socket.h>
#include <sys/stat.h>
#include <map>
#include <list>
#include <errno.h>

#include "../../common/global/global.h"
#include "../../util/tool/tool.h"
#include "../../util/timer/timer.h"
#include "../../util/log/log.h"
#include "../../lib/session/session.h"

#include "../../module/user/user.h"
#include "../../module/room/room.h"
#include "../../module/message/message.h"

void handle_read_request(process *process, const char *module, map<string, string> param);

map<string, string> parse_param(char *param_data);

void read_http_request(process* process);

void download_file(process* process, int fileId);

int recv_file(process* process, const char* filename);

void read_upload_request(process* process);

void read_tcp_request(process* process);

#endif