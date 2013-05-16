#ifndef _MESSAGE_BASE_H_
#define _MESSAGE_BASE_H_

#include <mysql/mysql.h>
#include <map>
#include <list>
#include <stdlib.h>

#include "../../common/config/config.h"
#include "../../util/eagleMysql/eagleMysql.h"
#include "../../common/global/global.h"
#include "../../util/log/log.h"
#include "../../util/tool/tool.h"
#include "../../data/compiledData/Response.pb.h"

int _get_message_info(int message_id, MessageData::Message_Info *message_info);
int _bind_user_chat(int sock, map<string, string> param, list<int> &send_sock_list, char *buf);

#endif