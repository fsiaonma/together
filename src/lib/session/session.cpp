#include "./session.h"

/**
 * session Construtor
 */
Session::Session() {
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
 * @param {string} username username
 * @param {string} dev_id device id 
 * @return {string} sid
 */
int Session::set(string username, string dev_id, string &sid) {
	int result;
	SESSION s;
	ofstream o_file;
	SESSION_LIST::iterator ptr;

	do {
		// check whether username is in catch or not
		for (ptr = this->list.begin(); ptr != this->list.end();) {
			if ((*ptr).username == username) {
				this->remove(username);
				result = S_REPLACE_IN;
				break;
			} else {
				++ptr;
			}
		}

		// store to cache
		s.username = username;
		s.dev_id = dev_id;
		s.active_time = Tool::L2S(time(NULL));
		s.rand_num = Tool::L2S(rand());
		s.sid = Tool::md5(username + "_" + dev_id + "_" + s.active_time + '_' + s.rand_num);;
		this->list.push_back(s);

		// write to file
		o_file.open(this->filename, ios::app);
		o_file << "username:" << s.username << "/"
			   << "dev_id:" << s.dev_id << "/" 
			   << "active_time:" << s.active_time << "/" 
			   << "rand_num:" << s.rand_num << "/"
			   << "sid:" << s.sid << "/\n";
		o_file.close();
		
		// set sid
		sid = s.sid;

        if (result != S_REPLACE_IN) {
            result = S_OK_IN;
        }
	} while(0);

	return result;
}

/**
 * get session by sid
 *  
 * @method get
 * @param {string} sid session id
 * @return {SESSION} SESSION whitch is found according to sid 
 */
SESSION *Session::get(string sid) {
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
int Session::remove(string username) {
	SESSION_LIST::iterator ptr;
	ofstream o_file;

	o_file.open(this->filename);
	for (ptr = this->list.begin(); ptr != this->list.end();) {
		if ((*ptr).username == username) {
			this->list.erase(ptr++);
		} else {
			o_file << "username:" << (*ptr).username << "/"
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
 * check whether the session is exist or not
 * 
 * @method exist
 * @param {string} username username
 * @return {bool} whether the session is exist or not
 */
bool Session::exist(string username) {
	SESSION_LIST::iterator ptr;
	bool is_exist = false;
	do {
		ptr = this->list.begin();
		for (ptr = this->list.begin(); ptr != this->list.end(); ++ptr) {
			if ((*ptr).username == username) {
				is_exist = true;
				break;
			}
		}
	} while (0);
	return is_exist;
}

/**
 *  init instance
 */
Session* Session::instance = new Session;

/**
 * get Session instance
 *  
 * @method get_instance
 * @return {Session} Session instance 
 */
Session* Session::get_instance() {
	return instance;
}

/**
 * session Destructor
 */
Session::~Session() {
	this->list.clear();
	memset(this->filename, 0, sizeof(this->filename));
}