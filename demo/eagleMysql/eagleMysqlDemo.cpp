#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <map>
#include <typeinfo>
#include <time.h>
#include "../../src/util/eagleMysql/eagleMysql.h"
#include "../../src/util/tool/tool.h"
using namespace std;

int main() {
    const char *domain = "localhost";
    const char *userName = "root";
    const char *password = "123456";
    const char *database = "together";
    int port = 3306;

    // init
    eagleMysql e(domain, userName, password, database, port);

    int insert_id = -1;

    // insert
    map<string, string> insert_params;
    string update_password = "123456789";
    insert_params["username"] = Tool::mysql_filter("insert_test_sam");
    insert_params["password"] = Tool::mysql_filter("update_password");
    insert_params["birthday"] = Tool::mysql_filter(123123);
    e.insert("t_user", insert_params, insert_id);

	// remove
    e.remove("t_user", "where username = 'insert_test'");

    // updata
    map<string, string> update_insert_params;
    update_insert_params["username"] = Tool::mysql_filter("update_insert_test");
    update_insert_params["password"] = Tool::mysql_filter("654321");
    e.insert("t_user", update_insert_params, insert_id);

    map<string, string> update_params;
    update_params["password"] = Tool::mysql_filter("testupdate");
    e.update("t_user", update_params, "where username = 'update_insert_test'");

	//excute
    e.connet();

    MYSQL mysql;
    string sql = "select * from t_user;";
    e.excute(sql);
    mysql = e.get_mysql();

    MYSQL_RES *result = NULL;
    MYSQL_FIELD *field = NULL;
    result = mysql_store_result(&mysql);
    cout << "result: " << result << endl;
    int rowcount = mysql_num_rows(result);
    cout << "rowcount " << rowcount << endl;
    int fieldcount = mysql_num_fields(result);
    cout << "fieldcount " << fieldcount << endl;
    for(int i = 0; i < fieldcount; i++) {
        field = mysql_fetch_field_direct(result, i);
        cout << field->name << "\t";
    }
    cout << endl;
    MYSQL_ROW row = NULL;
    row = mysql_fetch_row(result);
    while(NULL != row) {
        for(int i = 0; i < fieldcount; i++) {
            if (row[i] != NULL) {
                cout << row[i] << '\t';
            }
        }
        cout << endl;
        row = mysql_fetch_row(result);
    }
    e.close();

	return 0;
}