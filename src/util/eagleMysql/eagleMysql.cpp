#include <mysql/mysql.h>
#include "eagleMysql.h"
#include <iostream>
using namespace std;

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
 * used for insert operation
 *  
 * @method excute
 * @param {string} table table which is going to insert value to.
 * @param {PARAM array} params[10] insert values.
 * @param {string} condition sql condition.
 */
void eagleMysql::insert(string table, PARAMLIST list, string condition) {
	// cout << table << endl;
	PARAMLIST::iterator i;
	for (i = list.begin(); i != list.end(); ++i) {
		cout << i->key << '\t' << i->value << endl;
	}
	cout << table << endl;
	cout << condition << endl;
	// for (int i = 0; i < ( sizeof(params) / sizeof(PARAM)); ++i) {
	// 	cout << params[i].key << '\t' << params[i].value << endl;
	// }
	// cout << condition << endl;
	// mysql_init(&(this->mysql));
	// mysql_real_connect(&(this->mysql), this->domain, this->userName, this->password, this->dataBase, this->port, NULL, 0);
	// mysql_query(&(this->mysql), sql.c_str());
	// mysql_close(&(this->mysql));
}