#include "session.h"

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