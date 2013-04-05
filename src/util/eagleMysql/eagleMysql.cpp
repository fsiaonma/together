#include <mysql/mysql.h>
#include "eagleMysql.h"
#include <iostream>
#include <string>
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
 */
void eagleMysql::insert(string table, PARAMLIST list) {
    this->connet();
	
    string keys = "(", values = "(";
    PARAMLIST::iterator ptr;

    ptr = list.begin();
    for (int i = 0; i < list.size() - 1; ++i) {
        keys += ptr->key + ", ";
        values += "'" + ptr->value + "'" + ", ";
        ++ptr;
    }

    keys += ptr->key + ")";
    values += "'" + ptr->value + "')";

    string sql = "insert into " + table + " " + keys + " values " + values + ";";
    cout << "insert operation: " + sql << endl;
    mysql_query(&(this->mysql), sql.c_str());
    this->close();
}

/**
 * delete operation
 * 
 * @method remove
 * @param {string} table table which is going to remove data from.
 * @param {string} condition sql condition.
 */
void eagleMysql::remove(string table, string condition) {
    this->connet();
    string sql = "delete from " + table + " " + condition;
    cout << "remove operation: " + sql << endl;
    mysql_query(&(this->mysql), sql.c_str());
    this->close();
}

/**
 * update operation
 * 
 * @method update
 * @param {string} table table which is going to update data in.
 * @param {PARAMLIST} list list update values.
 * @param {string} condition sql condition.
 */
void eagleMysql::update(string table, PARAMLIST list, string condition) {
    this->connet();
	
    string keys = "(", values = "(";
    PARAMLIST::iterator ptr;

    string sql = "update " + table + " set ";
    ptr = list.begin();
    for (int i = 0; i < list.size() - 1; ++i) {
        sql += ptr->key + "=" + "'" + ptr->value + "', ";
        ++ptr;
    }
    sql += ptr->key + "=" + "'" + ptr->value + "' ";
    sql += condition;

    cout << "update operation: " + sql << endl;

    mysql_query(&(this->mysql), sql.c_str());
    this->close();
}

/**
 * connet to mysql.
 * 
 * @method connet.
 */
void eagleMysql::connet() {
    mysql_init(&(this->mysql));
    mysql_real_connect(&(this->mysql), this->domain, this->userName, this->password, this->dataBase, this->port, NULL, 0);
}

/**
 * excute sql
 * 
 * @method excute
 * @param {string} sql sql is used to be excuted.
 */
MYSQL eagleMysql::excute(string sql) {
    mysql_query(&(this->mysql), sql.c_str());
    return this->mysql;
}

/**
 * close mysql connet.
 * 
 * @method close.
 */
void eagleMysql::close() {
    mysql_close(&(this->mysql));
}

/**
 * judge whether the value is key list or not.  
 * 
 * @method is_exist.
 */
bool eagleMysql::is_exist(string key, string value) {
    bool is_exist = 0;
    MYSQL_RES *result = NULL;
    MYSQL_ROW row = NULL;
    int fieldcount;

    this->connet();
    this->mysql = this->excute("select " + key + " from user");

    result = mysql_store_result(&(this->mysql));
    fieldcount = mysql_num_fields(result);
    row = mysql_fetch_row(result);
    while(NULL != row) {
        for(int i = 0; i < fieldcount; i++) {
            if (row[i] == value) {
                is_exist = 1;
            }
        }
        row = mysql_fetch_row(result);
    }

    this->close();
    return is_exist;
}