#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <mysql/mysql.h>
#include <map>
#include <stdlib.h>

#include "../../common/config/config.h"
#include "../../util/eagleMysql/eagleMysql.h"
#include "../../common/global/global.h"
#include "../../util/log/log.h"
#include "../../data/compiledData/Response.pb.h"
#include "../../util/tool/tool.h"
#include "./message_base.h"
#include "../user/user_base.h"

int get_follow_up_msg(int current_id, int recipient_id, int rid, int type, char *buf, int &send_len);
int get_previous_msg(int current_id, int msgs_num, int sender_id, int recipient_id, char *buf, int &send_len);

int chat_handler(process *process, map<string, string> param, list<int> &send_sock_list);
int message_handler(process *process, map<string, string> param);

#endif