#include "user.h"

void regiest(string username, string password) {
	LOG << "regiest params: username is " << username << " password is " << password << endl;
	Config *c = Config::get_instance();
    map<string, string> config = c->get_config();
    eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), atoi(config["PORT"].c_str()));

    data::HTTPResponse *http_response = new data::HTTPResponse();

    if (e.is_exist("username", username)) {
        cout << "username is already exist" << endl;
    } else {
    	PARAM regist_item;
	    PARAMLIST regist_datas;
	 	regist_item.key = "username";
	    regist_item.value = username;
	    regist_datas.push_back(regist_item);
	    regist_item.key = "password";
	    regist_item.value = password;
	    regist_datas.push_back(regist_item);
	    e.insert("user", regist_datas);
    }    
}

void login(string username, string password) {
	cout << "login" << endl;
}

int user_handler(process *process, map<string, string> param) {
	//send file
	// int s;
	// char *file = "/home/kc/code/t.bmp";
	// struct stat filestat;
	// s = get_index_file(file, &filestat);
	// int fd = open(file, O_RDONLY);
	// process->fd = fd;
	// process->total_length = filestat.st_size;
	// char tempstring[30];
	// {
	// 	if (process->response_code == 200) {
    //      // 写入 content 长度
	// 		snprintf(tempstring, sizeof(tempstring), "Content-Length: %ld\r\n", filestat.st_size);
	// 		write_to_header(tempstring);
	// 	}
	// }

	const char *response_data;
    int action_type = atoi(param["action"].c_str());
    cout << "action_type: " << action_type << endl;
    switch (action_type) {
    	case USER_REGIEST: {
    	    regiest(param["username"], param["password"]);
    	    break ;
    	}
    	case USER_LOGIN: {
    		login(param["username"], param["password"]);
    		break ;
    	}
    }

    // start to write header
	process->buf[0] = 0;
	write_to_header(header_200_start);
	//send data
    write_to_header("\r\n");
    write_to_header(response_data);
    // 结束 header
	write_to_header(header_end);
}


