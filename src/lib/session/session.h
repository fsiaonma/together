#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "../../util/tool/tool.h"

using namespace std;

class session {
	public:
		string sid;
		session(string username, string dev_id);
		~session();
};