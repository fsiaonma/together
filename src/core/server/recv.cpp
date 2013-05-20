#include "./recv.h"
#include "./close.h"
#include "./send.h"


/**
 * [parse_param 从参数字符串中解析参数放入map中]
 * @param param_data [http请求的最后一行,post传过来的参数]
 */
 map<string, string> parse_param(char *param_data)
 {
 	char *p;
 	char *buf1 = param_data;

 	char *outer_ptr = NULL;
 	char *inner_ptr = NULL;

 	int k;
 	string key;
 	map<string, string> m;
 	while((p=strtok_r(buf1, "&", &outer_ptr))!=NULL)
 	{
 		buf1=p;
 		k = 0;
 		while((p=strtok_r(buf1, "=", &inner_ptr))!=NULL)
 		{
 			k++;
 			if (k == 1) {
 				key.assign(p);
 			} else if (k == 2) {
 				m.insert(pair<string, string>(key, p));
 				break;
 			}
 			buf1=NULL;
 		}  
 		buf1=NULL;
 	}
 	map<string, string>::iterator it;
 	for (it = m.begin(); it != m.end(); it++)
 	{
 		LOG_INFO << "key:" << it->first << "|val:" << it->second << endl;
 	}
 	return m;
 }

/**
 * [handle_read_request 处理HTTP的请求]
 * @param process [process对象]
 * @param module  [模块名]
 * @param param   [保存了请求中参数及其对应的值,map<string, string>]
 */
 void handle_read_request(process *process, const char *module, map<string, string> param) {
    memset(process->buf, 0, process->kBufferSize); 
 	LOG_INFO << "handle_read_request" << endl;
 	int module_type = get_module_type(module);
 	int s;

 	switch (module_type) {
 		case USER_MODULE:
 		{	
 			s = user_handler(process, param);
 			if (s == -1) {
 				LOG_ERROR << "user_handler err" << endl;
	 			BAD_REQUEST
	 			return;
 			}
 			break;
 		}
 		case ROOM_MODULE:
 		{
 			s = room_handler(process, param);
 			if (s == -1) {
 				LOG_ERROR << "user_handler err" << endl;
	 			BAD_REQUEST
	 			return;
 			}
 			break;
 		}
 		case MESSAGE_MODULE:
 		{
 			s = message_handler(process, param);
 			if (s == -1) {
 				LOG_ERROR << "message_handler err" << endl;
	 			BAD_REQUEST
	 			return;
 			}
 			break;
 		}
 		default:
 		{
 			LOG_ERROR << "module_type err|" << module_type << endl;
 			BAD_REQUEST
 			return;
 		}
 	}

 	process->status = STATUS_SEND_RESPONSE_HEADER;
	// 修改此 sock 的监听状态，改为监视写状态
 	event.data.fd = process->sock;
 	event.events = EPOLLOUT;
 	s = epoll_ctl(efd, EPOLL_CTL_MOD, process->sock, &event);
 	if (s == -1) {
 		LOG_ERROR << "epoll_ctl error" << endl;
 		BAD_REQUEST
 		// abort();
 	}
 	LOG_INFO << "------send header------" << endl;
 	// LOG_DEBUG << process->buf << endl;
 }


/**
 * [read_http_request 接收HTTP请求(LISTEN_HTTP_REQ_PORT端口)]
 * @param process [process对象]
 */
 void read_http_request(process* process)
 {
	int sock = process->sock;
	process->send_length = -1;
	char* _buf = process->buf;
	ssize_t count;
	string request;

	string module_name;
	// 接收HTTP请求
	while (1) {
		count = recv(sock, _buf + process->read_pos, process->kBufferSize - process->read_pos, MSG_DONTWAIT);
		if (count == -1) {
			if (errno == EAGAIN)
				break;
		} else if (count == 0) {
	    	LOG_WARN << "client " << process->sock << " close connection" << endl;
			cleanup(process);
			break;
		} else if (count > 0) {
			process->read_pos += count;
			_buf[process->read_pos] = 0;
			request.append(_buf);
			LOG_DEBUG << _buf << endl;
			LOG_DEBUG << "process->read_pos|" << process->read_pos << endl;
			if (process->read_pos == process->kBufferSize)
			{
				process->read_pos = 0;
			}
		}
	}
	int request_len = request.length();
	LOG_DEBUG << "request_len|" << request_len << endl;
	LOG_INFO << "recv from sock:" << process->sock << " type:" << process->type << endl;
	LOG_INFO << request << endl;
	
	// 按行截取HTTP请求
	vector<string> line = Tool::split(request, "\n");

	// get first line
	string firstline = line[0];

	int first_blank = firstline.find(' ');
	int last_blank = firstline.find_last_of(' ');
	int question_mark = firstline.find('?');
	if (firstline.substr(0, 3) != "GET") {
		LOG_ERROR << "http request type error" << endl;
		BAD_REQUEST
		return ;
	}

	if (first_blank > 0 && question_mark > 0 && (question_mark - first_blank > 2))
	{
		module_name = firstline.substr(first_blank + 2, question_mark - first_blank - 2);
	} else {
		LOG_ERROR << "module name err|" << module_name << endl;
		BAD_REQUEST
		return ;
	}
	LOG_INFO << "module_name|" << module_name << endl;

	string params;
	if (question_mark > 0 && last_blank > 0 && (last_blank - question_mark > 1))
	{
		params = firstline.substr(question_mark + 1, last_blank - question_mark - 1);
	} else {
		LOG_ERROR << "param err|" << params << endl;
		BAD_REQUEST
		return ;
	}
	LOG_INFO << "param|" << params << endl;

	// 解析参数
	vector<string> param_list = Tool::split(Tool::url_decode(params), "&");
	int param_list_len = param_list.size();
	map<string, string> param;
	for (int i = 0; i < param_list_len; i++)
	{
		LOG_DEBUG << param_list[i] << endl;
	    vector<string> _param = Tool::split(param_list[i], "=");
	    if (_param.size() == 2)
	    {
	        // LOG_INFO << "key,val|" << _param[0] << "|" << _param[1] << endl;
	        param.insert(pair<string, string>(_param[0], _param[1]));
	    } else {
	    	LOG_ERROR << "_param size err" << endl;
	    	BAD_REQUEST
	    	return;
	    }
	}

	process->response_code = 200;
	if (module_name == "download") {
		if (param.count("fileId") == 0) {
	    	BAD_REQUEST
	    	return;
		}
		download_file(process, Tool::S2I(param["fileId"]));
	} else {
 		handle_read_request(process, module_name.c_str(), param);
	}
 }

 void download_file(process* process, int fileId)
 {
 	if (fileId < 0) {
 		BAD_REQUEST
 		return;
 	}
 	LOG_INFO << "download fileId|" << fileId << endl;
 	// get file info from database
 	bool is_succ = false;
	int s;
 	string msg = "";
 	MYSQL mysql;

    Config *c = Config::get_instance();
    map<string, string> config = c->get_config();
    eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));
 	e.connet();
 	do
 	{
	    string sql = "select * from t_file where id = " + Tool::toString(fileId) + ";";
	    LOG_INFO << sql << endl;

	    e.excute(sql);
	    mysql = e.get_mysql();

	    MYSQL_RES *result = NULL;
	    MYSQL_FIELD *field = NULL;
	    MYSQL_ROW row = NULL;

	    result = mysql_store_result(&mysql);
	    int rowcount = mysql_num_rows(result);
	    int fieldcount = mysql_num_fields(result);
	    row = mysql_fetch_row(result);

	    LOG_DEBUG << rowcount << "|" << fieldcount << endl;

	    string md5, suffix, user_id;

	    if (rowcount == 1)
	    {
	    	for(int i = 0; i < fieldcount; i++) {
	            if (row[i] != NULL) {
	            	field = mysql_fetch_field_direct(result, i);
        			string key = field->name;
        			if (key == "md5")
        				md5 = row[i];
        			else if (key == "suffix")
        				suffix = row[i];
        			else if (key == "uploader_id")
        				user_id = row[i];
	            }
        	}
        	LOG_INFO << "get file info from database succ" << endl;
	    } else {
	    	msg = "get file info from database fail";
	    	break;
	    }
	    if (Tool::trim(md5).empty() || Tool::trim(suffix).empty() || Tool::S2I(user_id) < 0)
	    {
	    	msg = "md5 or suffix or user_id is illeagal";
	    	break;
	    }
	    LOG_INFO << "md5:" << md5 << "|" << "suffix:" << suffix << "|" << "user_id:" << user_id << endl;
	    // get file info
	    string file_path = config["UPLOAD_PATH"] + md5 + "_" + user_id + suffix;
	    LOG_INFO << "download filename:" << file_path << endl;

    	struct stat filestat;
		s = lstat(file_path.c_str(), &filestat);
		if (s == -1)
		{
			msg = "get file info error";
			break;
		}
    	int file_size = filestat.st_size;
    	LOG_INFO << "filesize:" << file_size << endl;

    	int fd = open(file_path.c_str(), O_RDONLY);
		process->fd = fd;
		process->total_length = file_size;
		is_succ = true;

		process->buf[0] = 0;
		reset_process(process);
		write_to_header(header_200_start);
		char tempstring[30];
		snprintf(tempstring, sizeof(tempstring), "Content-Length: %ld\r\n", filestat.st_size);
		write_to_header(tempstring);
		write_to_header(header_end);
		LOG_INFO << process->buf << endl;

 	} while(0);
 	e.close();
 	if (is_succ)
 	{
 		LOG_INFO << "send file ready success" << endl;
	 	process->status = STATUS_SEND_RESPONSE_HEADER;
		// 修改此 sock 的监听状态，改为监视写状态
	 	event.data.fd = process->sock;
	 	event.events = EPOLLOUT;
	 	s = epoll_ctl(efd, EPOLL_CTL_MOD, process->sock, &event);
	 	if (s == -1) {
	 		LOG_ERROR << "epoll_ctl error" << endl;
	 		// abort();
	 		BAD_REQUEST
	 	}
 	} else {
 		LOG_ERROR << msg << endl;
 		BAD_REQUEST
 		return ;
 	}
 }

/**
 * [recv_file 接收文件数据,保存到硬盘]
 * @param  process  [process对象]
 * @param  filename [保存的文件名]
 * @return          [接收的文件大小]
 */
 int recv_file(process* process, const char* filename) 
 { 
 	int rval; 
 	int read_total = 0;
 	char *buf = process->buf; 
 	int sock = process->sock;
 	FILE *file = fopen(filename, "a+b"); 
 	if (!file)
 	{
 		LOG_ERROR << "Can't open file for writing" << endl;
 		return -1;
 	}

 	do
 	{
 		rval = recv(sock, buf, sizeof(buf), 0);
 		if (rval < 0)
 		{
 			if (errno != EAGAIN) {
 				LOG_ERROR << "Can't read from socket" << "|" << rval << "|" << errno << endl;
 				fclose(file);
 				return -1;
 			} else {
 				read_total += rval;
 				fclose(file);
 				return read_total;
 			}
 		}
 		if (rval == 0)
 			break;
 		int off = 0;
 		do
 		{
 			int written = fwrite(&buf[off], 1, rval - off, file);
 			if (written < 1)
 			{
 				LOG_ERROR << "Can't write to file" << endl;
 				fclose(file);
 				return read_total;
 			}
 			off += written;
 		}while (off < rval);
 		read_total += rval;
 	} while(1);

 	fclose(file); 
 	return read_total;
 } 


/**
 * [read_upload_request 接收HTTP请求,解析后开始接收文件数据,保存(LISTEN_UPLOAD_REQ_PORT端口)]
 * @param process [process对象]
 */
void read_upload_request(process* process)
{
	int s;
	int user_id = -1;
	LOG_INFO << "RECV UPLOAD REQUEST|" << process->status << endl;
	switch(process->status)
	{
		case STATUS_UPLOAD_READY:
		{
			LOG_INFO << "STATUS_UPLOAD_READY" << endl;
			int sock = process->sock;
			char buf[500];
			ssize_t count;
			string &request = process->request;
			int need_to_recv = 0;
			// 接收HTTP请求
			while (1) {
				count = recv(sock, buf, 500, MSG_DONTWAIT);
				if (count == -1) {
					LOG_INFO << "total recv:" << process->read_pos << endl;
					LOG_INFO << "need to recv:" << need_to_recv << endl;
					if (need_to_recv == process->read_pos) {
						LOG_INFO << "recv all data !!" << endl;
						break;
					}
					if (errno == EAGAIN)
						return ;
				} else if (count == 0) {
					break;
				} else if (count > 0) {
					process->read_pos += count;
					buf[count] = 0;
					request.append(buf);

					if (request.substr(0, 7) == "length=") {
						int equal_mark = request.find('=');
						int _mark = request.find('&');
						if (_mark > equal_mark) {
							string data_len = request.substr(7, (_mark - equal_mark - 1));
							need_to_recv = Tool::S2I(data_len);
							// LOG_INFO << "data len:" << data_len << endl;
						}
					}
				}
			}
			LOG_INFO << "recv from sock:" << process->sock << " type:" << process->type << endl;
			int request_len = request.size();
			LOG_INFO << "request len:" << request_len << endl;

			// 解析参数
			vector<string> param_list = Tool::split(request, "&");
			int param_list_len = param_list.size();
			map<string, string> param;
			for (int i = 0; i < param_list_len; i++)
			{
			    vector<string> _param = Tool::split(param_list[i], "=");
			    if (_param.size() == 2)
			    {
					if (_param[0] == "md5") {
						strncpy(process->md5, _param[1].c_str(), 33);
					} else if (_param[0] == "filedata") {
						string ss = Tool::url_decode(_param[1]);
						_param[1] = ss;
					}
			        // LOG_DEBUG << "key,val|" << _param[0] << "|" << _param[1] << endl;
			        param.insert(pair<string, string>(_param[0], _param[1]));
			    } else {
			    	LOG_ERROR << "_param size err" << endl;
			    	BAD_REQUEST
			    	return;
			    }
			}

			// 如果参数为空
			if (param.empty())
			{
				LOG_ERROR << "param is null" << endl;
				BAD_REQUEST
				return;
			}

			// TODO:: session校验
			if (param.count("sid") > 0)
			{
				SESSION *p_session = NULL;
				p_session = Session::get(param["sid"]);
				if (p_session == NULL) {
					LOG_ERROR << "sid error" << endl;
					BAD_REQUEST
					return;
				}
			} else {
				LOG_ERROR << "param sid not exist" << endl;
				BAD_REQUEST
				return;
			}

			// md5参数校验
			if (! (param.count("md5") > 0 && param["md5"].length() == 32) )
			{
				LOG_ERROR << "md5 err" << endl;
				BAD_REQUEST
				return;
			}

			// uid参数校验
			if ( param.count("uid") <= 0 || Tool::S2I(param["uid"]) < 0 )
			{
				LOG_ERROR << "uid error" << endl;
				BAD_REQUEST
				return;
			}
			user_id = Tool::S2I(param["uid"]);

			// 如果没有filedata参数
			if (! (param.count("filedata") > 0) )
			{
				LOG_ERROR << "filedata not exist" << endl;
				BAD_REQUEST
				return;
			}

			// 如果有suffix(后缀名)参数
			if (param.count("suffix"))
			{
				if (param["suffix"].length() > 10)
				{
					LOG_ERROR << "suffix too long" << endl;
					BAD_REQUEST
					return;
				}
				strncpy(process->suffix, param["suffix"].c_str(), strlen(param["suffix"].c_str()) + 1);
			} else {
				process->suffix[0] = 0;
			}

			LOG_INFO << "sid|" << param["sid"] << endl;
			LOG_INFO << "uid|" << user_id << endl;
			LOG_INFO << "MD5|" << process->md5 << endl;
			LOG_INFO << "suffix|" << process->suffix << endl;

			// base64解码得到文件内容
			string strTmpResult = Tool::base64_decode(param["filedata"].c_str());
			int len = strTmpResult.length();
			Config *c = Config::get_instance();
			map<string, string> config = c->get_config();
			string filename = config["UPLOAD_PATH"] + param["md5"] + "_" + Tool::toString(user_id) + param["suffix"];

			// 写入文件
			const char *file_data = strTmpResult.c_str();
			int write_size = 1024;
			FILE *file = fopen(filename.c_str(), "w+b"); 

			int neee_to_write;
			int off = 0;
			LOG_INFO << "file_len|" << len << endl;
			do
			{
			    neee_to_write = ((len - off) < write_size ? (len - off): write_size);
			    int written = fwrite(&file_data[off], 1, neee_to_write, file);
			    if (written < 1)
			    {
			    	BAD_REQUEST
			        fclose(file);
			        return;
			    }
			    off += written;
			}while (off < len);
			fclose(file); 

			process->status = STATUS_UPLOAD_FINISHED;
		}
		case STATUS_UPLOAD_FINISHED:
		{
			LOG_INFO << "STATUS_UPLOAD_FINISHED" << endl;
			// TODO::保存文件成功,之后判断接收到的文件MD5与预期的是否一样,一样的话就写入数据库.返回响应信息
			LOG_INFO << "save file succ!" << endl;
			char md5[MD5_LEN + 1];
			char file_name[256];
			Config *c = Config::get_instance();
			map<string, string> config = c->get_config();
			sprintf(file_name, "%s%s_%d%s", config["UPLOAD_PATH"].c_str(), process->md5, user_id, process->suffix);
			// 保存的文件的MD5
			if (Tool::calc_file_MD5(file_name, md5))
			{
				LOG_INFO << "Calc Success! MD5 sum :" << md5 << endl;
				// MD5一致
				if (strcmp(md5, process->md5) == 0)
				{
					LOG_INFO << "Success! MD5 sum is consistent" << endl;
					process->response_code = 200;
					memset(process->buf, 0, sizeof(char) * process->kBufferSize); 
					process->buf[0] = 0;
					process->status = STATUS_SEND_RESPONSE_HEADER;


			        // database params
			        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

			        map<string, string> insert_params;
			        insert_params["suffix"] = Tool::mysql_filter(Tool::toString(process->suffix));
			        insert_params["md5"] = Tool::mysql_filter(Tool::toString(process->md5));
			        insert_params["uploader_id"] = Tool::mysql_filter(user_id);

			        int file_insert_id = -1;
			        int ret = e.insert("t_file", insert_params, file_insert_id);


					// 修改此 sock 的监听状态，改为监视写状态
					event.data.fd = process->sock;
					event.events = EPOLLOUT;
					s = epoll_ctl(efd, EPOLL_CTL_MOD, process->sock, &event);
					if (s == -1) {
						LOG_ERROR << "epoll_ctl error" << endl;
						// abort();
						BAD_REQUEST
					}
			        // exception
			        if (ret != DB_OK) 
			        {
			        	// delete file
			        	if(remove(file_name))
			        	{
			        		LOG_ERROR << "DB_ERROR|remove file error" << endl;
			        	} else {
			        		LOG_ERROR << "DB_ERROR|insert into t_file error" << endl;
			        	}
			        	BAD_REQUEST
			        }
			        string f_id = Tool::toString(file_insert_id);
					write_to_header(header_200_start);
					write_to_header("\r\n");
					write_to_header(f_id.c_str());
					// write_to_header(header_end);
				} else {
					// MD5不一致
					LOG_ERROR << "Fail! MD5 sum is inconsistent" << endl;
		        	// delete file
		        	if(remove(file_name))
		        	{
		        		LOG_ERROR << "DB_ERROR|remove file error" << endl;
		        	} else {
		        		LOG_ERROR << "DB_ERROR|insert into t_file error" << endl;
		        	}
					BAD_REQUEST
				}
			} else {
    			// TODO::计算MD5失败
				LOG_ERROR << "Calc MD5 err" << endl;
	        	// delete file
	        	if(remove(file_name))
	        	{
	        		LOG_ERROR << "DB_ERROR|remove file error" << endl;
	        	} else {
	        		LOG_ERROR << "DB_ERROR|insert into t_file error" << endl;
	        	}
				BAD_REQUEST
			}
			process->status = STATUS_UPLOAD_READY;
			break;
		}
		default:
		break;
	}
}

/**
 * [read_tcp_request 接收长连接请求(LISTEN_TCP_REQ_PORT端口)]
 * @param process [process对象]
 */
void read_tcp_request(process* process)
{
	int s;
	int sock = process->sock;
	char* _buf = process->buf;
	ssize_t count;
	string request;

	string module_name;
    memset(process->buf, 0, process->kBufferSize);
	// 接收HTTP请求
	while (1) {
		count = recv(sock, _buf + process->read_pos, process->kBufferSize - process->read_pos, MSG_DONTWAIT);
		if (count == -1) {
			if (errno == EAGAIN)
				break;
		} else if (count == 0) {
	    	LOG_WARN << "client " << process->sock << " close connection" << endl;
	    	del_by_sock(process->sock);
			cleanup(process);
			return;
		} else if (count > 0) {
			process->read_pos += count;
			_buf[process->read_pos] = 0;
			request.append(_buf);
			if (process->read_pos == process->kBufferSize)
			{
				process->read_pos = 0;
			}
		}
	}
	LOG_INFO << "request|" << request << endl;
	reset_process(process);

	
	vector<string> param_list = Tool::split(Tool::url_decode(request), "&");
	int param_list_len = param_list.size();
	map<string, string> param;
	for (int i = 0; i < param_list_len; i++)
	{
		LOG_DEBUG << param_list[i] << endl;
	    vector<string> _param = Tool::split(param_list[i], "=");
	    if (_param.size() == 2)
	    {
	        param.insert(pair<string, string>(_param[0], _param[1]));
	    } else {
	    	LOG_ERROR << "_param size err" << endl;
	    	char r[10];
	    	sprintf(r, "%d", CHAT_PARAM_ERR);
	    	write_to_header(r);
	    	send(sock, r, strlen(r), 0);
	    	return ;
	    }
	}
	list<int> send_sock_list;
	s = chat_handler(process, param, send_sock_list);
	if (s < 0) {
    	char r[10];
    	sprintf(r, "%d", CHAT_HANDLE_ERR);
    	write_to_header(r);
    	send(sock, r, strlen(r), 0);
		return ;
	}

	list<int>::iterator iter;
    for(iter = send_sock_list.begin(); iter != send_sock_list.end(); iter++)
    {
    	LOG_INFO << "send to:" << *iter << endl;
        send(*iter, process->buf, strlen(process->buf), 0);
    }

}
