#include "./session.h"

map<string, SESSION> Session::sessions;
char Session::filename[100];

/**
 * session Construtor
 */
int Session::init() {
    char prj_path[1024];
    Tool::get_project_path(prj_path, 1024);
    char session_cache_path[strlen(prj_path) + 20];
    sprintf(session_cache_path, "%ssrc/lib/session/session_cache", prj_path);
    strncpy(filename, session_cache_path, strlen(session_cache_path) + 1);
    return 0;
}

/**
 * set session
 *  
 * @method set
 * @param {string} uid uid
 * @param {string} dev_id device id 
 * @return {string} sid
 */
int Session::set(string uid, string dev_id, string &sid) {
	init_sessions();

    int result = 0;
    SESSION s;
    ofstream o_file;
    map<string, SESSION>::iterator ptr;
    string str_temp;

    do {
        // check whether username is in catch or not
	    for(ptr = sessions.begin(); ptr != sessions.end(); ++ptr) {
	    	if (ptr->first == uid) {
	    		remove(uid);
	    		result = S_REPLACE_IN;
	    		break;
	    	}
	    }

	    str_temp =Tool::md5(uid + "_" + dev_id + "_" + s.active_time + '_' + s.rand_num);

        // write to file
        o_file.open(filename, ios::app);
        o_file << "uid:" << uid << "/"
               << "dev_id:" << dev_id << "/" 
               << "active_time:" << Tool::L2S(time(NULL)) << "/" 
               << "rand_num:" << Tool::L2S(rand()) << "/"
               << "sid:" << str_temp << "/\n";
        o_file.close();
        
        // set sid
        sid = str_temp;

        if (result == 0) {
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
	init_sessions();

    SESSION *s = NULL;
    map<string, SESSION>::iterator ptr;
    for (ptr = sessions.begin(); ptr != sessions.end();) {
    	if ((ptr->second).sid == sid) {
            s = &(ptr->second);
            break;
        }
        ++ptr;
    }
    return s;
}

/**
 * remove session by uid
 *  
 * @method remove
 * @param {string} uid uid
 * @return {int} the status of remove operation
 */
int Session::remove(string uid) {
	init_sessions();

    map<string, SESSION>::iterator ptr;
    ofstream o_file;

    o_file.open(filename);
    for (ptr = sessions.begin(); ptr != sessions.end(); ++ptr) {
        if (ptr->first != uid) {
            o_file << "uid:" << (ptr->second).uid << "/"
                   << "dev_id:" << (ptr->second).dev_id << "/" 
                   << "active_time:" << (ptr->second).active_time << "/" 
                   << "rand_num:" << (ptr->second).rand_num << "/" 
                   << "sid:" << (ptr->second).sid << "/\n";
            
        }
    }
    o_file.close();

    return 1;
}

int res = Session::init();

void Session::init_sessions() {
	sessions.clear();
    ifstream i_file;
    string out_text;
    string key, value;
    SESSION s;
	i_file.open(filename, ios::in);
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
                } else if (key == "dev_id") {
                    s.dev_id = value;
                } else if (key == "active_time") {
                    s.active_time = value;
                } else if (key == "rand_num") {
                    s.rand_num = value;
                }
                out_text = out_text.erase(0, out_text.find('/') + 1);
            }
           	sessions[s.uid] = s;
        }
    }
    i_file.close();
}
