
#ifndef _LOG_H_
#define _LOG_H_

#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <cstdio>
#include <sys/time.h>
#include <sstream>

using namespace std;

enum enLogLevel
{
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
};

extern const char* LogLevel[];

#define LEVEL 2

class Logger
{
public:
    Logger(enLogLevel level, const char* file, const char* func, int line)
    {
        lvl = level;
        oss << getpid() << "|" << LogLevel[level] << "|" << file << "|" << func << "|" << line << "|" << get_now_time() << "|";
    }
    ~Logger()
    {
        if (lvl >= LEVEL) {
            std::cout << oss.str(); //record log to cout
        }
    }

    std::ostream& stream()
    {
        return oss;
    }

    char *get_now_time()
	{
	    time_t t = time(NULL);
	    tm *lt = localtime(&t);
	    static char s[10];
	    sprintf(s, "%d:%d:%d", lt->tm_hour, lt->tm_min, lt->tm_sec);
	    return s;
	}

private:
    std::ostringstream oss;
    int lvl;
};



#endif

#ifndef LOG_TRACE 
#define LOG_TRACE Logger(TRACE, __FILE__, __FUNCTION__, __LINE__).stream()
#endif

#ifndef LOG_DEBUG 
#define LOG_DEBUG Logger(DEBUG, __FILE__, __FUNCTION__, __LINE__).stream()
#endif

#ifndef LOG_INFO 
#define LOG_INFO Logger(INFO, __FILE__, __FUNCTION__, __LINE__).stream()
#endif

#ifndef LOG_WARN 
#define LOG_WARN Logger(WARN, __FILE__, __FUNCTION__, __LINE__).stream()
#endif

#ifndef LOG_ERROR 
#define LOG_ERROR Logger(ERROR, __FILE__, __FUNCTION__, __LINE__).stream()
#endif

#ifndef LOG_FATAL 
#define LOG_FATAL Logger(FATAL, __FILE__, __FUNCTION__, __LINE__).stream()
#endif
