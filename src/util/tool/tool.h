#ifndef _TOOL_H_
#define _TOOL_H_

#include <string>
#include <stdlib.h>
#include <sstream>

using namespace std;

class Tool
{
public:
	static bool isNum(string str);

	template <class T>
	static int getArrayLen(T &array);

	static int S2I(string num, int default_val = -1);
};

#endif