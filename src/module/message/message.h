#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <mysql/mysql.h>
#include <map>
#include <vector>
#include <stdlib.h>

#include "../../common/config/config.h"
#include "../../util/eagleMysql/eagleMysql.h"
#include "../../common/global/global.h"
#include "../../util/log/log.h"
#include "../../data/compiledData/Response.pb.h"
#include "../../util/tool/tool.h"
#include "./message_base.h"
#include "./message_sock.h"
#include "../user/user_base.h"

int get_msgs(map<string, string> param, char *buf, int &send_len);

int save_msg(int sock, map<string, string> param, list<int> &send_sock_list, char *buf);
int start_room(int sock, map<string, string> param, list<int> &send_sock_list, char *buf);
int change_msg_status(int msg_id, int room_id, int recipient_id, char *buf, int &send_len);
int join_room(int sock, map<string, string> param, list<int> &send_sock_list, char *buf);
int quit_room(int sock, map<string, string> param, list<int> &send_sock_list, char *buf);


int chat_handler(process *process, map<string, string> param, list<int> &send_sock_list);
int message_handler(process *process, map<string, string> param);

#endif