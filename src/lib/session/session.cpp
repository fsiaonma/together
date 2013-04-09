#include "./session.h"

session::session() {
	this->list.clear();
	cout << "init" << endl;
}

session::~session() {
	this->list.clear();
}

SESSION session::set(string uid, string username, string dev_id) {
	SESSION s;

	const time_t t = time(NULL);
	string active_time;
	string rand_num;
	string sid;

	active_time = Tool::L2S(t);
	rand_num = Tool::L2S(rand());
	sid = Tool::md5(uid + "_" + username + "_" + dev_id + "_" + active_time + '_' + rand_num);

	s.sid = sid;
	s.uid = uid;
	s.username = username;
	s.dev_id = dev_id;
	s.active_time = active_time;
	s.rand_num = rand_num;

	this->list.push_back(s);

	return s;
}

SESSION *session::get(string sid) {
	SESSION *s = NULL;
	SESSION_LIST::iterator ptr;
    ptr = this->list.begin();
    for (int i = 0; i < this->list.size(); ++i) {
        if (ptr->sid == sid) {
        	s = &(*ptr);
        	break;
        }
        ++ptr;
    }
	return s;
}