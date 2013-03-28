#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include "../../src/util/eagleMysql/eagleMysql.h"
using namespace std;

int main() {
	PARAM a;
	a.key = "username";
	a.value = "soso";

	PARAMLIST list;
	list.push_front(a);

	eagleMysql e("localhost", "root", "123456", "testmysql", 3306);
	e.insert("user", list, "where 1=1");
	return 0;
}