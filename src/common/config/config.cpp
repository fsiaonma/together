#include "config.h"

Config::Config()
{
	// TODO::parse config file
	this->config.insert(pair<string, string>("HTTP_PORT", "9080"));
	this->config.insert(pair<string, string>("UPLOAD_PORT", "9081"));
	this->config.insert(pair<string, string>("TCP_PORT", "9082"));
	this->config.insert(pair<string, string>("KEEPALIVE_TIMEOUT", "5000"));
}

Config::~Config() {}

Config* Config::instance = new Config;

Config* Config::get_instance()
{
	return instance;
}

void Config::del_instance()
{
	if (0 != instance)
	{
		delete instance;
		instance = 0;
	}
}

map<string, string> Config::get_config()
{
	return this->config;
}
