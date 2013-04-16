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

char *Tool::get_project_path(int count)
{
    string str = "", result = "";
    char buf[1024];

    int rslt = readlink("/proc/self/exe", buf, count - 1);
    if (rslt < 0 || (rslt >= count - 1)) {
        return NULL;
    }
    str = buf;
    while(str.substr(0, str.find('/')) != "together") {
        result += str.substr(0, str.find('/') + 1);
        str = str.erase(0, str.find('/') + 1);
    }
    result += "together/";
    char *result_buf = Tool::S2C(result);
    
    return result_buf;
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

string Tool::base64_decode(const char* Data)
{
    //解码表
    const char DecodeTable[] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        62, // '+'
        0, 0, 0,
        63, // '/'
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // '0'-'9'
        0, 0, 0, 0, 0, 0, 0,
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
        13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
        0, 0, 0, 0, 0, 0,
        26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
        39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
    };
    int DataByte = strlen(Data);
    //返回值
    string strDecode;
    int nValue;
    int i= 0;
    while (i < DataByte)
    {
        if (*Data != '\r' && *Data!='\n')
        {
            nValue = DecodeTable[*Data++] << 18;
            nValue += DecodeTable[*Data++] << 12;
            strDecode+=(nValue & 0x00FF0000) >> 16;
            if (*Data != '=')
            {
                nValue += DecodeTable[*Data++] << 6;
                strDecode+=(nValue & 0x0000FF00) >> 8;
                if (*Data != '=')
                {
                    nValue += DecodeTable[*Data++];
                    strDecode+=nValue & 0x000000FF;
                }
            }
            i += 4;
        }
        else// 回车换行,跳过
        {
            Data++;
            i++;
        }
     }
    return strDecode;
}

vector<string> Tool::split(string str, string pattern)
{
    string::size_type pos;
    vector<string> result;
    str+=pattern;//扩展字符串以方便操作
    int size=str.size();
 
    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern, i);
        if(pos < size)
        {
            string s=str.substr(i, pos - i);
            result.push_back(s);
            i=pos + pattern.size() - 1;
        }
    }
    return result;
}
