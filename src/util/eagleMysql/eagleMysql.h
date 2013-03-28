#include <mysql/mysql.h>
#include <iostream>
#include <list>
using namespace std;

/**
 * database params
 */
struct PARAM {
	string key;
	string value;
};

/**
 * defined list
 */
typedef list<PARAM> PARAMLIST;

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
		
		void insert(string table, PARAMLIST list, string sql);
		// void remove(string table, PARAM params[10], string sql);
		// void update(string table, PARAM params[10], string sql);
};