#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include "../../util/tool/tool.h"
using namespace std;

class Config
{
public:
	static Config *get_instance();
	static void  del_instance();
	map<string, string> get_config();
	~Config();
private:
	static Config *instance;
	map<string, string> config;
	Config();
};

#endif





