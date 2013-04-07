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

<<<<<<< HEAD
string Tool::L2S(long num) {
    stringstream ss;
    string result = ""; 
    ss << num;
    ss >> result;
    return result;
}

char *Tool::S2C(string str) {
    const char *str_tmp = str.c_str();
    char *buf = new char[strlen(str_tmp) + 1];
    strcpy(buf, str_tmp);
    return buf;
}

int Tool::md5_str(char *s,char *md5_sum)
=======
string md5(string s)
>>>>>>> 857a4525893dbab4c8248cc371da3f67b3032fb9
{
    const char *input = s.c_str();
    char c[50];
    char md5_sum[33];
    sprintf(c, "printf '%s' | md5sum | cut -d ' ' -f1", input);
    cout << "md5:" << c << endl;
    FILE *p = popen(c, "r");
    if (p == NULL) 
        return 0;
    int i, ch;
    for (i = 0; i < 32 && isxdigit(ch = fgetc(p)); i++) {
        md5_sum[i] = ch;
    }
<<<<<<< HEAD

    *md5_sum = '\0';
=======
    md5_sum[i] = '\0';
>>>>>>> 857a4525893dbab4c8248cc371da3f67b3032fb9
    pclose(p);
    if (i == 32)
        return string(md5_sum);
    else
        return "";
}