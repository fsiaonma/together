#ifndef S_PARAM_ERROR_IN
#define S_PARAM_ERROR_IN 1001
#endif

#ifndef S_OK_IN
#define S_OK_IN 6000
#endif

#ifndef S_REPLACE_IN
#define S_REPLACE_IN 12002
#endif

#ifndef _SESSION_T_H_
#define _SESSION_T_H_

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
 * @param {String} username username; 
 * @param {String} dev_id device id; 
 * @param {String} active_time active time; 
 * @param {String} rand_num random number; 
 */
struct SESSION {
    string sid;
    string username;
    string dev_id;
    string active_time;
    string rand_num;
};

typedef list<SESSION> SESSION_LIST;

class Session {
    private:
        static SESSION_LIST list;
        static char filename[100];
    public:
        static init();
        static int set(string username, string dev_id, string &sid);
        static SESSION *get(string sid);
        static int remove(string username);
};

SESSION_LIST Session::list;
char Session::filename[100];

/**
 * session Construtor
 */
int Session::init() {
    ifstream i_file;
    string out_text;
    string key, value;
    SESSION s;

    list.clear();

    char prj_path[1024];
    Tool::get_project_path(prj_path, 1024);
    char session_cache_path[strlen(prj_path) + 20];
    sprintf(session_cache_path, "%ssrc/lib/session/session_cache", prj_path);
    strncpy(filename, session_cache_path, strlen(session_cache_path) + 1);

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
            list.push_back(s);
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
    int result = 0;
    SESSION s;
    ofstream o_file;
    SESSION_LIST::iterator ptr;

    do {
        // check whether username is in catch or not
        for (ptr = list.begin(); ptr != list.end();) {
            if ((*ptr).username == username) {
                remove(username);
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
        list.push_back(s);

        // write to file
        o_file.open(filename, ios::app);
        o_file << "username:" << s.username << "/"
               << "dev_id:" << s.dev_id << "/" 
               << "active_time:" << s.active_time << "/" 
               << "rand_num:" << s.rand_num << "/"
               << "sid:" << s.sid << "/\n";
        o_file.close();
        
        // set sid
        sid = s.sid;

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
    SESSION *s = NULL;
    SESSION_LIST::iterator ptr;
    ptr = list.begin();
    for (int i = 0, len = list.size(); i < len; ++i) {
        if ((*ptr).sid == sid) {
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

    o_file.open(filename);
    for (ptr = list.begin(); ptr != list.end();) {
        if ((*ptr).username == username) {
            list.erase(ptr++);
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

int res = Session::init();

#endif