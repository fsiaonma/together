#ifndef _SEND_H_
#define _SEND_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/sendfile.h>

#include "../../common/global/global.h"
#include "../../util/log/log.h"

void send_response_header(process *process);

void send_response(process *process);

#endif