#ifndef _TOOL_H_
#define _TOOL_H_

#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <stdio.h>
#include <sstream>
#include <iostream>

using namespace std;

class Tool
{
public:
	static bool isNum(string str);

	template <class T>
	static int getArrayLen(T &array);

	static int S2I(string num, int default_val = -1);
	static string L2S(long num);
	static char *S2C(string str);

	static string md5(string s);
};

#endif