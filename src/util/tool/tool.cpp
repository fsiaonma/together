#include "tool.h"


bool Tool::isNum(string str)
{
    stringstream sin(str);
    double d;
    char c;
    if(!(sin >> d))
        return false;
    if (sin >> c)
        return false;
    return true;
}

template <class T>
int Tool::getArrayLen(T &array)
{
    return (sizeof(array) / sizeof(array[0]));
}

int Tool::S2I(string num, int default_val)
{
	if (isNum(num)) {
		return atoi(num.c_str());
	} else {
		return default_val;
	}
}

int Tool::md5_str(char *s,char *md5_sum)
{
    char c[50];
    sprintf(c, "printf '%s' | md5sum | cut -d ' ' -f1", s);
    FILE *p = popen(c, "r");
    if (p == NULL) 
        return 0;
    int i, ch;
    for (i = 0; i < 32 && isxdigit(ch = fgetc(p)); i++) {
        *md5_sum++ = ch;
    }
    *md5_sum = '\0';
    pclose(p);
    return i == 32;
}