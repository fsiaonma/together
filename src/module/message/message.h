#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "./message_base.h"

int chat_handler(process *process, map<string, string> param, list<int> &send_sock_list);

#endif