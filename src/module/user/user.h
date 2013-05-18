#ifndef _USER_H_
#define _USER_H_

#include <mysql/mysql.h>
#include <map>
#include <stdlib.h>

#include "../../common/config/config.h"
#include "../../util/eagleMysql/eagleMysql.h"
#include "../../common/global/global.h"
#include "../../util/log/log.h"
#include "../../data/compiledData/Response.pb.h"
#include "../../util/tool/tool.h"
#include "../../lib/session/session.h"
#include "./user_base.h"

int regiest(string username, string password, char *buf, int &send_len);
int login(string username, string password, string dev_id, char *buf, int &send_len);
int logout(string sid, char *buf, int &send_len);
int username_is_exist(string username, char *buf, int &send_len);

int view_user_info(int visit_uid, string sid, char *buf, int &send_len);
int set_user_info(map<string, string> params, string sid, char *buf, int &send_len);

int prise(int uid, string sid, char *buf, int &send_len);
int follow(int uid, string sid, char *buf, int &send_len);
int unfollow(int uid, string sid, char *buf, int &send_len);

int get_following_list(int uid, int page_no, int page_size, string sid, char *buf, int &send_len);
int get_followers_list(int uid, int page_no, int page_size, string sid, char *buf, int &send_len);

int get_msg_list(int recipient_id, char *buf, int &send_len);

int user_handler(process *process, map<string, string> param);
#endif