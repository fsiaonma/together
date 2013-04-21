#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <map>
#include "../../src/util/eagleMysql/eagleMysql.h"
using namespace std;

int main() {
    const char *domain = "localhost";
    const char *userName = "root";
    const char *password = "123456";
    const char *database = "testmysql";
    int port = 3306;

    // init
    eagleMysql e(domain, userName, password, database, port);

    // insert
    map<string, string> insert_params;
    insert_params["username"] = "insert_test";
    insert_params["password"] = "123456";
    e.insert("user", insert_params);

	// remove
    e.remove("user", "where username = 'sam'");

    // updata
    map<string, string> update_insert_params;
    update_insert_params["username"] = "update_insert_test";
    update_insert_params["password"] = "654321";
    e.insert("user", update_insert_params);

    map<string, string> update_params;
    update_params["password"] = "testupdate";
    e.update("user", update_params, "where username = 'update_insert_test'");

	//excute
    e.connet();

    MYSQL mysql;
    string sql = "select * from user;";
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
        cout << field->name << "\t\t";
    }
    cout << endl;
    MYSQL_ROW row = NULL;
    row = mysql_fetch_row(result);
    while(NULL != row) {
        for(int i = 0; i < fieldcount; i++) {
            cout << row[i] << "\t\t";
        }
        cout << endl;
        row = mysql_fetch_row(result);
    }

    e.close();

    bool is_exist;
    e.is_exist("user", "where username = 'fsiaonma'", is_exist);
    cout << "is_exist: " << is_exist << endl;

	return 0;
}