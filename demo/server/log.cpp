#include "log.h"


char *get_now_time()
{
    time_t t = time(NULL);
    tm *lt = localtime(&t);
    static char s[10];
    sprintf(s, "%d:%d:%d", lt->tm_hour, lt->tm_min, lt->tm_sec);
    return s;
}