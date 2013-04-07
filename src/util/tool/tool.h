#ifndef _TOOL_H_
#define _TOOL_H_

#include <string>
#include <stdlib.h>
#include <sstream>
#include <stdio.h>

using namespace std;

class Tool
{
public:
	static bool isNum(string str);

	template <class T>
	static int getArrayLen(T &array);

	static int S2I(string num, int default_val = -1);

	static int md5_str(char *s,char *md5_sum);
};

#endif