#include "config.h"

Config::Config()
{
	ifstream out;
    char *prj_path = Tool::get_project_path(1024);
    char config_path[strlen(prj_path) + 20];
    sprintf(config_path, "%sconfig/config", prj_path);
    cout << "config file path:" << config_path << endl;
    out.open(config_path, ios::in);
    do
    {
        if (!out.is_open())
        {
            cout << "read config file fail !!!!" << endl;
            break;
        }

        string line;
        int equal_pos;
        int line_len;

        while(!out.eof()){
            getline(out,line);
            if (line[0] == '#' || line.empty())
                continue;
            line_len = line.size();
            equal_pos = (int) line.find("=");
            // cout << "--------------------" << endl;
            // cout << "read data|" << line <<endl;
            if (equal_pos <= 0 || equal_pos == (line_len - 1))
            {
                cout << "illegal equal pos|" << line << endl;
                continue;
            }
            string key = line.substr(0, equal_pos);
            string val = line.substr(equal_pos + 1, line_len);
            // cout << trim(key) << "|" << trim(val) << endl;
            if (Tool::trim(key).empty() || Tool::trim(val).empty())
            {
                cout << "key or value is empty|" << line << endl;
                continue;
            }
            this->config.insert(pair<string, string>(key, val));
            // cout << "final:" << key << "|" << val << endl;
        }
    } while(0);
    out.close();
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
