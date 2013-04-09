#ifndef _CLOSE_H_
#define _CLOSE_H_

#include "../../common/global/global.h"
#include "../../util/log/log.h"
#include "../../util/timer/timer.h"

void cleanup(process *process);

void handle_error(process* process, const char* error_string);

void reset_process(process* process);

#endif