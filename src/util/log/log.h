#ifndef LOG  
#define LOG cout << getpid() << "|" <<  __FILE__ << "|" << __LINE__ << "|" << get_now_time() << "|"
#endif

#ifndef ERR  
#define ERR cout << getpid() << "|" <<  __FILE__ << "|" << __FUNCTION__ << "|" << __LINE__ << "|" << get_now_time() << "|ERR|" 
#endif

#ifndef _LOG_H_
#define _LOG_H_

#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <cstdio>
#include <sys/time.h>

using namespace std;

char *get_now_time();

#endif