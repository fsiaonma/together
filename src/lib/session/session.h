#ifndef S_PARAM_ERROR_IN
#define S_PARAM_ERROR_IN 1001
#endif

#ifndef S_OK_IN
#define S_OK_IN 6000
#endif

#ifndef S_REPLACE_IN
#define S_REPLACE_IN 12002
#endif

#ifndef _SESSION_H_
#define _SESSION_H_

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
    string uid;
    string dev_id;
    string active_time;
    string rand_num;
};

class Session {
    private:
        static map<string, SESSION> sessions;
        static char filename[100];
        static void init_sessions();
    public:
        static int init();
        static int set(string uid, string dev_id, string &sid);
        static SESSION *get(string sid);
        static int remove(string uid);
};

#endif