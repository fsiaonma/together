#include "tool.h"

/**
 * [Tool::isNum description]
 * @param  str [description]
 * @return     [description]
 */
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

/**
 * [Tool::S2I description]
 * @param  num         [description]
 * @param  default_val [description]
 * @return             [description]
 */
int Tool::S2I(string num, int default_val)
{
	if (isNum(num)) {
		return atoi(num.c_str());
	} else {
		return default_val;
	}
}

/**
 * [Tool::L2S description]
 * @param  num [description]
 * @return     [description]
 */
string Tool::L2S(long num) {
    stringstream ss;
    string result = ""; 
    ss << num;
    ss >> result;
    return result;
}

/**
 * [Tool::S2C description]
 * @param  str [description]
 * @return     [description]
 */
int Tool::S2C(string str, char *buf) {
    int i = 0, result = 1;
    if (Tool::trim(str).empty()) {
        result = 0;
    } else {
        const char *str_tmp = str.c_str();
        char temp_buf[strlen(str_tmp) + 1];
        strcpy(temp_buf, str_tmp);
        int len = strlen(temp_buf);
        for (i = 0; i < len; ++i) {
            buf[i] = temp_buf[i];
        }
        buf[i] = '\0';
    }
    return result;
}


/**
 * [Tool::md5 description]
 * @param  s [description]
 * @return   [description]
 */
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


/**
 * [Tool::trim description]
 * @param  s [description]
 * @return   [description]
 */
string& Tool::trim(string &s) 
{
    if (s.empty()) {
        return s;
    }
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}

/**
 * [Tool::get_project_path description]
 * @param  count [description]
 * @return       [description]
 */
int Tool::get_project_path(char *buf, int count) {
    string str = "", temp_buf = "";
    int result = 1;

    char cur_path[1024];
    int rslt = readlink("/proc/self/exe", cur_path, count - 1);
    if (rslt < 0 || (rslt >= count - 1)) {
        result = 0;
    } else {
        str = cur_path;
        while(str.substr(0, str.find('/')) != "together") {
            temp_buf += str.substr(0, str.find('/') + 1);
            str = str.erase(0, str.find('/') + 1);
        }
        temp_buf += "together/";
        Tool::S2C(temp_buf, buf);
    }
    
    return result;
}

/**
 * [Tool::calc_file_MD5 description]
 * @param  file_name [description]
 * @param  md5_sum   [description]
 * @return           [description]
 */
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


/**
 * [Tool::base64_decode description]
 * @param  Data [description]
 * @return      [description]
 */
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
            nValue = DecodeTable[(int)(*Data++)] << 18;
            nValue += DecodeTable[(int)(*Data++)] << 12;
            strDecode+=(nValue & 0x00FF0000) >> 16;
            if (*Data != '=')
            {
                nValue += DecodeTable[(int)(*Data++)] << 6;
                strDecode+=(nValue & 0x0000FF00) >> 8;
                if (*Data != '=')
                {
                    nValue += DecodeTable[(int)(*Data++)];
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

/**
 * 
 */
vector<string> Tool::split(string str, string pattern)
{
    string::size_type pos;
    vector<string> result;
    str+=pattern;//扩展字符串以方便操作
    int size=str.size();
 
    for(int i=0; i < size; i++)
    {
        pos = str.find(pattern, i);
        if((int)pos < size)
        {
            string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}

/**
 * [Tool::now_time get now system time]
 * @return [now time string]
 */
string Tool::now_time()
{
    time_t t = time(NULL);
    char buf[32];
    strftime(buf, sizeof(buf), "%Y%m%d%H%M%S",localtime(&t));
    string str(buf);
    return str;
}


string Tool::url_decode(const string &sIn)
{

    string sOut;
    for(size_t ix = 0; ix < sIn.size(); ix++ )
    {
        unsigned char ch = 0;
        if(sIn[ix]=='%')
        {
            ch = (fromHex(sIn[ix+1])<<4);
            ch |= fromHex(sIn[ix+2]);
            ix += 2;
        }
        else if(sIn[ix] == '+')
        {
            ch = ' ';
        }
        else
        {
            ch = sIn[ix];
        }
        sOut += (char)ch;
    }
    return sOut;
}
