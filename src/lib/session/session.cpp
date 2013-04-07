#include "session.h"

session::session(string username, string dev_id) {
	char *buf;
	char md5[9999];

	const time_t t = time(NULL);
	string current_time;
	string rand_num;
	current_time = Tool::L2S(t);
	rand_num = Tool::L2S(rand());
	
	buf = Tool::S2C(username + "_" + dev_id + "_" + current_time + '_' + rand_num);
	int i = Tool::md5_str(buf, md5);
	string result_str(md5);
	
	this->sid = result_str;
}

session::~session() {
	this->sid = "";
}