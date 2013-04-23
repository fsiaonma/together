#include <mysql/mysql.h>
#include "eagleMysql.h"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

/**
 * eagleMysql Constructor
 *  
 * @method eagleMysql
 * @param {const char*} domain domain of the database
 * @param {const char*} userName username which is used for conneting to the database.
 * @param {const char*} password password which is used for conneting to the database.
 * @param {const char*} dataBase dataBase of the project.
 * @param {int} port port of the project.
 * @Constructor
 */
eagleMysql::eagleMysql(const char* domain, const char* userName, const char* password, const char* dataBase, int port) {
    MYSQL mysql;
    mysql_init(&mysql);
    this->domain = domain;
    this->userName = userName;
    this->password = password;
    this->dataBase = dataBase;
    this->port = port;
}

/**
 * insert operation
 * 
 * @method insert
 * @param {string} table table which is going to insert value in.
 * @param {PARAMLIST} list insert values.
 * @param {int} the id of row which inserted.
 */
int eagleMysql::insert(string table, map<string, string> params, int &insert_id) {
    if (!connet())
        return SQL_CONNECT_FAIL;
    int ret = SQL_OK;
    
    string keys = "(", values = "(";
    map<string, string>::iterator ptr;

    ptr = params.begin();
    int size = params.size();
    for(int i = 0; i < size - 1; ++i) {
        keys += ptr->first + ", ";
        values += "'" + ptr->second + "'" + ", ";
        ++ptr;
    }
    keys += ptr->first + ")";
    values += "'" + ptr->second + "')";

    string sql = "insert into " + table + " " + keys + " values " + values + ";";
    cout << "insert operation: " + sql << endl;
    ret = excute(sql);
    insert_id = this->mysql.insert_id;
    this->close();
    return ret;
}

/**
 * delete operation
 * 
 * @method remove
 * @param {string} table table which is going to remove data from.
 * @param {string} condition sql condition.
 */
int eagleMysql::remove(string table, string condition) {
    if (!connet())
        return SQL_CONNECT_FAIL;
    int ret = SQL_OK;

    string sql = "delete from " + table + " " + condition;
    cout << "remove operation: " + sql << endl;
    ret = excute(sql);
    this->close();
    return ret;
}

/**
 * update operation
 * 
 * @method update
 * @param {string} table table which is going to update data in.
 * @param {PARAMLIST} list list update values.
 * @param {string} condition sql condition.
 */
int eagleMysql::update(string table, map<string, string> params, string condition) {
    if (!connet())
        return SQL_CONNECT_FAIL;
    int ret = SQL_OK;
	
    string keys = "(", values = "(";
    map<string, string>::iterator ptr;

    string sql = "update " + table + " set ";
    ptr = params.begin();
    int size = params.size();
    for (int i = 0; i < size - 1; ++i) {
        sql += ptr->first + "=" + "'" + ptr->second + "', ";
        ++ptr;
    }
    sql += ptr->first + "=" + "'" + ptr->second + "' ";
    sql += condition;

    cout << "update operation: " + sql << endl;

    ret = excute(sql);
    this->close();
    return ret;
}

/**
 * connet to mysql.
 * 
 * @method connet.
 * @return {bool} whether it is connect successfully
 */
bool eagleMysql::connet() {
    mysql_init(&(this->mysql));
    if (!mysql_real_connect(&(this->mysql), this->domain, this->userName, this->password, this->dataBase, this->port, NULL, 0)) {
        cout << "Failed to connect to database: Error :" << mysql_error(&mysql) << endl;  
        return false;
    }
    return true;
}

/**
 * excute sql
 * 
 * @method excute
 * @param {string} sql sql is used to be excuted.
 * @return {MYSQL} mysql object.
 */
int eagleMysql::excute(string sql) {
    int ret = SQL_OK;
    if ((mysql_query(&(this->mysql), sql.c_str())) != 0)
        ret = SQL_QUERY_ERR;
    return ret;
}

/**
 * close mysql connet.
 * 
 * @method close.
 */
void eagleMysql::close() {
    mysql_close(&(this->mysql));
}

MYSQL eagleMysql::get_mysql() {
    return this->mysql;
}

/**
 * judge whether the value is exist in key list or not.  
 *  
 * @param {string} table the table of judging whether the value is exist or not. 
 * @param {string} condition the condition of judging whether the value is exist or not.
 * @method is_exist.
 * @return {int} is_exist
 */
int eagleMysql::is_exist(string table, string condition, bool &exist) {
    int ret = SQL_OK;
    exist = false;
    if (!connet())
        return SQL_CONNECT_FAIL;

    excute("select count(1) from " + table + " " + condition + ";");
    MYSQL_RES *result = mysql_store_result(&(this->mysql));
    MYSQL_ROW rowdata = mysql_fetch_row(result);
    if (rowdata) {
        if (atoi(rowdata[0]) > 0)
            exist = true;
    } else {
        ret = SQL_COUNT_ERR;
    }
    cout << "is_exist: " << exist << endl;
    mysql_free_result(result);
    this->close();
    return ret;
}