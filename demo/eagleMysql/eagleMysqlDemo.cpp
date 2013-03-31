#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include "../../src/util/eagleMysql/eagleMysql.h"
using namespace std;

int main() {
	// init
    eagleMysql e("localhost", "root", "123456", "testmysql", 3306);

	// insert
    PARAM dataA;
    dataA.key = "username";
    dataA.value = "sam";
    PARAM dataB;
    dataB.key = "password";
    dataB.value = "123456";

    PARAMLIST insertList;
    insertList.push_back(dataA);
    insertList.push_back(dataB);

    e.insert("user", insertList);

	// remove
    e.remove("user", "where username = 'sam'");

	// update
    PARAM dataC;
    dataC.key = "username";
    dataC.value = "testUpdate";
    PARAMLIST testUpdateInsertList;
    testUpdateInsertList.push_front(dataC);
    e.insert("user", testUpdateInsertList);

    PARAM dataD;
    dataD.key = "username";
    dataD.value = "fsiaonma";
    PARAM dataE;
    dataE.key = "password";
    dataE.value = "123456789";
    PARAMLIST updateList;
    updateList.push_back(dataD);
    updateList.push_back(dataE);
    e.update("user", updateList, "where username = 'testUpdate'");

	//excute
    e.connet();

    MYSQL mysql;
    string sql = "select * from user;";
    mysql = e.excute(sql);

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
	return 0;
}