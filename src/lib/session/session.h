#ifndef S_PARAM_ERROR_IN
#define S_PARAM_ERROR_IN 1001
#endif

#ifndef S_OK_IN
#define S_OK_IN 6000
#endif

#ifndef S_REPLACE_IN
#define S_REPLACE_IN 12002
#endif

#ifndef _SESSION_H_
#define _SESSION_H_

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <list>
#include <fstream>

#include "../../util/tool/tool.h"

using namespace std;

/**
 * struct SESSION
 *  
 * @param {String} sid session id;
 * @param {String} username username; 
 * @param {String} dev_id device id; 
 * @param {String} active_time active time; 
 * @param {String} rand_num random number; 
 */
struct SESSION {
	string sid;
	string username;
	string dev_id;
	string active_time;
	string rand_num;
};

typedef list<SESSION> SESSION_LIST;

class Session {
	private:
		static Session *instance;
		SESSION_LIST list;
		char filename[100];
	public:
		Session();
		~Session();
		static Session *get_instance();
		bool exist(string username);
		int set(string username, string dev_id, string &sid);
		SESSION *get(string sid);
		int remove(string username);
};

#endif