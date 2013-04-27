#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <map>
#include <typeinfo>
#include <time.h>
#include "../../src/util/eagleMysql/eagleMysql.h"
#include "../../src/util/tool/tool.h"
#include "../../src/common/config/config.h"
using namespace std;

int main() {
    Config *c = Config::get_instance();
    map<string, string> config = c->get_config();
    eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), 
            config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

    int insert_id = -1;

    // insert
    map<string, string> insert_params;
    string param = "参数";
    insert_params["username"] = Tool::mysql_filter(param);
    e.insert("t_user", insert_params, insert_id);

    // count
    int count;
    e.count("t_user", "where username = '参数';", count);
    cout << "count: " << count << endl;

	// remove
    e.remove("t_user", "where username = '参数'");

    // updata
    map<string, string> update_insert_params;
    string update_insert_test = "update_insert_test";
    string password = "123456";
    update_insert_params["username"] = Tool::mysql_filter(update_insert_test);
    update_insert_params["password"] = Tool::mysql_filter(password);
    e.insert("t_user", update_insert_params, insert_id);

    map<string, string> update_params;
    string testupdate = "testupdate";
    update_params["password"] = Tool::mysql_filter(testupdate);
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
