#include "./session.h"

/**
 * session Construtor
 */
session::session() {
	ifstream i_file;
	string out_text;
	string key, value;
	SESSION s;

    this->list.clear();

    char prj_path[1024];
    Tool::get_project_path(prj_path, 1024);
	char session_cache_path[strlen(prj_path) + 20];
    sprintf(session_cache_path, "%ssrc/lib/session/session_cache", prj_path);
   	strncpy(this->filename, session_cache_path, strlen(session_cache_path) + 1);

    i_file.open(this->filename, ios::in);
    while(!i_file.eof()) {
        getline(i_file, out_text);
        if (out_text != "") {
        	while ((int)out_text.find('/') != -1) {
        		key = out_text.substr(0, out_text.find(':'));
        		out_text = out_text.erase(0, out_text.find(':') + 1);
        		value = out_text.substr(0, out_text.find('/'));
        		if (key == "sid") {
        			s.sid = value;
        		} else if (key == "uid") {
        			s.uid = value;
        		} else if (key == "username") {
        			s.username = value;
        		} else if (key == "dev_id") {
        			s.dev_id = value;
        		} else if (key == "active_time") {
        			s.active_time = value;
        		} else if (key == "rand_num") {
        			s.rand_num = value;
        		}
				out_text = out_text.erase(0, out_text.find('/') + 1);
			}
			this->list.push_back(s);
        }
    }
    i_file.close();
}

/**
 * set session
 *  
 * @method set
 * @param {string} uid user id
 * @param {string} username username
 * @param {string} dev_id device id 
 * @return {string} sid
 */
string session::set(string uid, string username, string dev_id) {
	string result = "";
	SESSION s;
	ofstream o_file;
	SESSION_LIST::iterator ptr;

	for (ptr = this->list.begin(); ptr != this->list.end();) {
		if ((*ptr).username == username) {
			this->remove(username);
			break;
		} else {
			++ptr;
		}
	}

	s.uid = uid;
	s.username = username;
	s.dev_id = dev_id;
	s.active_time = Tool::L2S(time(NULL));
	s.rand_num = Tool::L2S(rand());
	s.sid = Tool::md5(uid + "_" + username + "_" + dev_id + "_" + s.active_time + '_' + s.rand_num);;
	this->list.push_back(s);

	o_file.open(this->filename, ios::app);
	o_file << "username:" << s.username << "/"
		   << "uid:" << s.uid << "/"  
		   << "dev_id:" << s.dev_id << "/" 
		   << "active_time:" << s.active_time << "/" 
		   << "rand_num:" << s.rand_num << "/"
		   << "sid:" << s.sid << "/\n";
	o_file.close();

	result = s.sid;

	return result;
}

/**
 * get session by sid
 *  
 * @method get
 * @param {string} sid session id
 * @return {SESSION} SESSION whitch is found according to sid 
 */
SESSION *session::get(string sid) {
	SESSION *s = NULL;
	SESSION_LIST::iterator ptr;
    ptr = this->list.begin();
    for (int i = 0, len = this->list.size(); i < len; ++i) {
        if (ptr->sid == sid) {
        	s = &(*ptr);
        	break;
        }
        ++ptr;
    }
	return s;
}

/**
 * remove session by username
 *  
 * @method remove
 * @param {string} username username
 * @return {int} the status of remove operation
 */
int session::remove(string username) {
	SESSION_LIST::iterator ptr;
	ofstream o_file;

	o_file.open(this->filename);
    ptr = this->list.begin();
	for (ptr = this->list.begin(); ptr != this->list.end();) {
		if ((*ptr).username == username) {
			this->list.erase(ptr++);
		} else {
			o_file << "username:" << (*ptr).username << "/"  
				   << "uid:" << (*ptr).uid << "/" 
				   << "dev_id:" << (*ptr).dev_id << "/" 
				   << "active_time:" << (*ptr).active_time << "/" 
				   << "rand_num:" << (*ptr).rand_num << "/"	
				   << "sid:" << (*ptr).sid << "/\n";
			++ptr;
		}
	}
	o_file.close();

    return 1;
}

/**
 * session Destructor
 */
session::~session() {
	this->list.clear();
	memset(this->filename, 0, sizeof(this->filename));
}