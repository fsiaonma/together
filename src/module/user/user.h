#include <mysql/mysql.h>
#include <map>
#include <stdlib.h>

#include "../../common/config/config.h"
#include "../../util/eagleMysql/eagleMysql.h"
#include "../../common/global/global.h"
#include "../../util/log/log.h"
#include "../../data/data.pb.h"

int user_handler(process *process, map<string, string> param);