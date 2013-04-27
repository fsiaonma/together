#ifndef _E_MYSQL_H_
#define _E_MYSQL_H_

#ifndef SQL_OK
#define SQL_OK 5000
#endif

#ifndef SQL_CONNECT_FAIL
#define SQL_CONNECT_FAIL 5001
#endif

#ifndef SQL_COUNT_ERR
#define SQL_COUNT_ERR 5002
#endif

#ifndef SQL_QUERY_ERR
#define SQL_QUERY_ERR 5003
#endif


#include <mysql/mysql.h>
#include <iostream>
#include <map>
using namespace std;

/**
 * eagleMysql Class
 */
class eagleMysql {
    private:
        const char* domain;
        const char* userName;
        const char* password;
        const char* dataBase;
        int port;
        MYSQL mysql;

    public:
        eagleMysql(const char* domain, const char* userName, const char* password, const char* dataBase, int port);

        int insert(string table, map<string, string>  params, int &insert_id);
        int remove(string table, string condition);
        int update(string table, map<string, string>  params, string condition);
        bool connet();
        int excute(string sql);
        void close();

        MYSQL get_mysql();
        int is_exist(string table, string condition, bool &exist);
        int count(string table, string condition, int &count);
};

#endif