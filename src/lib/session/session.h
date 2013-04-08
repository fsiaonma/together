#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <list>

#include "../../util/tool/tool.h"

using namespace std;

class session {
	private:
		string sid;
		map<string, string> arguments;
	public:
		session(string username, string dev_id);
		~session();

		string get_sid();
		void set(string key, string value);
		string get(string key);
};

typedef list<session> SESSION_LIST;

class session_list {
	private:
		SESSION_LIST list;
	public:
		session_list();
		~session_list();
		void set_session(session s);
		session get_session(string sid);
		void test();
};