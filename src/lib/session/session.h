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
 * @param {String} uid userid id; 
 * @param {String} username username; 
 * @param {String} dev_id device id; 
 * @param {String} active_time active time; 
 * @param {String} rand_num random number; 
 */
struct SESSION {
	string sid;
	string uid;
	string username;
	string dev_id;
	string active_time;
	string rand_num;
};

typedef list<SESSION> SESSION_LIST;

class session {
	private:
		SESSION_LIST list;
		char filename[100];
	public:
		session();
		~session();
		string set(string uid, string username, string dev_id);
		SESSION *get(string sid);
		int remove(string username);
};