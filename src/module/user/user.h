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

int regiest(string username, string password, char *buf);
int login(string username, string password, string dev_id, char *buf);
int logout(string username, string sid, char *buf);
int user_handler(process *process, map<string, string> param);

#endif