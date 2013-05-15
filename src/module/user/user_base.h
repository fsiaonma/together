#ifndef _USER_BASE_H_
#define _USER_BASE_H_

#include <mysql/mysql.h>
#include <map>
#include <stdlib.h>

#include "../../common/config/config.h"
#include "../../util/eagleMysql/eagleMysql.h"
#include "../../common/global/global.h"
#include "../../util/log/log.h"
#include "../../data/compiledData/Response.pb.h"
#include "../../util/tool/tool.h"

int _get_user_info(int uid, UserData::User_Info *user_info);
int _set_http_head(int code, bool success, string msg, Response::HTTPResponse *http_res);
int _get_uid(string username, int &uid);
int _is_follow(int following_id, int follower_id, bool &exist);

#endif