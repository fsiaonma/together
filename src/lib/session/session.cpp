#include "./session.h"

// session
session::session(string username, string dev_id) {
	const time_t t = time(NULL);
	string current_time;
	string rand_num;
	current_time = Tool::L2S(t);
	rand_num = Tool::L2S(rand());
	this->sid = Tool::md5(username + "_" + dev_id + "_" + current_time + '_' + rand_num);;
}

session::~session() {
	this->sid = "";
}

string session::get_sid() {
	return this->sid; 
}

void session::set(string key, string value) {
	this->arguments.insert(pair<string, string>(key, value));
}

string session::get(string key) {
	return this->arguments[key];
}

// session_list 
session_list::session_list() {
	cout << 'init' << endl;
}

session_list::~session_list() {
	this->list.clear();
}

void session_list::set_session(session s) {
	this->list.push_back(s);
}

session session_list::get_session(string sid) {
	session *p = NULL;
	SESSION_LIST::iterator ptr;
	ptr = this->list.begin();
    for (int i = 0; i < this->list.size(); ++i) {
    	if ((*ptr).get_sid() == sid) {
    		p = &(*ptr);
    	}
    	++ptr;
    }
    cout << (*ptr).get_sid() << endl;
    return *p;
}