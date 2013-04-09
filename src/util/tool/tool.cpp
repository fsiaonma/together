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

int Tool::S2I(string num, int default_val)
{
	if (isNum(num)) {
		return atoi(num.c_str());
	} else {
		return default_val;
	}
}

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

string Tool::md5(string s) {
    char md5_sum[33];
    string ss = "printf '" + s + "' | md5sum | cut -d ' ' -f1";
    FILE *p = popen(ss.c_str(), "r");
    if (p == NULL) 
        return 0;
    int i, ch;
    for (i = 0; i < 32 && isxdigit(ch = fgetc(p)); i++) {
        md5_sum[i] = ch;
    }
    md5_sum[i] = '\0';
    pclose(p);
    if (i == 32)
        return string(md5_sum);
    else
        return "";
}

string& Tool::trim(string &s) 
{
    if (s.empty()) {
        return s;
    }
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}

char *Tool::get_project_path(char * buf, int count)
{
    int i;
    int rslt = readlink("/proc/self/exe", buf, count - 1);
    if (rslt < 0 || (rslt >= count - 1))
    {
        return NULL;
    }
    buf[rslt] = '\0';
    bool in_project_path = false;
    for (i = rslt; i >= 0; i--)
    {
        if (buf[i] == '/')
        {
            if (i > 0 && !in_project_path)
            {
                in_project_path = true;
                continue;
            }
            buf[i + 1] = '\0';
            break;
        }
    }
    printf("project path:%s\n", buf);
    return buf;
}

int Tool::calc_file_MD5(char *file_name, char *md5_sum)
{
    #define MD5SUM_CMD_FMT "md5sum %." STR(PATH_LEN) "s 2>/dev/null"
    char cmd[PATH_LEN + sizeof (MD5SUM_CMD_FMT)];
    sprintf(cmd, MD5SUM_CMD_FMT, file_name);
    #undef MD5SUM_CMD_FMT

    FILE *p = popen(cmd, "r");
    if (p == NULL) return 0;

    int i, ch;
    for (i = 0; i < 32 && isxdigit(ch = fgetc(p)); i++) {
        *md5_sum++ = ch;
    }

    *md5_sum = '\0';
    pclose(p);
    return i == 32;
}
