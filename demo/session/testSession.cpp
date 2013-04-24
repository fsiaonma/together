#ifndef S_PARAM_ERROR_IN
#define S_PARAM_ERROR_IN 1001
#endif

#ifndef S_OK_IN
#define S_OK_IN 6000
#endif

#ifndef S_REPLACE_IN
#define S_REPLACE_IN 12002
#endif

#include <iostream>
#include <list>
#include <string>
#include <stdlib.h>

using namespace std;

struct SESSION {
    string username;
};

typedef list<SESSION> SESSION_LIST;

class Session {
    private:
        static Session *instance;
        static SESSION_LIST list;
    public:
        static init();
        static set(string username, string dev_id, string &sid);
        static remove(string username);
};

/**
 *  init instance
 */
SESSION_LIST Session::list;

int Session::init() {
    cout << "init" << endl;
    return 0;
}

int a = Session::init();

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
    SESSION_LIST::iterator ptr;

    do {
        // check whether username is in catch or not
        for (ptr = list.begin(); ptr != list.end();) {
            if (ptr->username == username) {
                remove(username);
                result = S_REPLACE_IN;
                break;
            } else {
                ++ptr;
            }
        }

        // store to cache
        s.username = username;
        list.push_back(s);
        
        // set sid
        sid = "aaa";

        if (result == 0) {
            result = S_OK_IN;
        }
    } while(0);

    return result;
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
    for (ptr = list.begin(); ptr != list.end();) {
        if ((*ptr).username == username) {
            list.erase(ptr++);
        } else {
            ++ptr;
        }
    }
    return 1;
}

int main() {
    string str;
    Session::set("sam", "99002020202020", str);
    cout << str << endl;
    string a;
    Session::set("sam", "99002020202020dawdawd", a);
    cout << a << endl;
    return 0;
}