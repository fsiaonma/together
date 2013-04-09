#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <list>

#include "../../util/tool/tool.h"

using namespace std;

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
	public:
		session();
		~session();
		SESSION set(string uid, string username, string dev_id);
		SESSION *get(string sid);
};