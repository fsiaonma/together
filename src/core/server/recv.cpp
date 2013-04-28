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
 		abort();
 	}
 	LOG_INFO << "------send header------" << endl;
 	LOG_INFO << process->buf << endl;
 }


/**
 * [read_http_request 接收HTTP请求(LISTEN_HTTP_REQ_PORT端口)]
 * @param process [process对象]
 */
 void read_http_request(process* process)
 {
	int sock = process->sock;
	char* _buf = process->buf;
	ssize_t count;
	string request;
	int content_length = 0;
	int other_sign_num = 0;
	string module_name;
	// 接收HTTP请求
	while (1) {
		count = recv(sock, _buf + process->read_pos, process->kBufferSize - process->read_pos, MSG_DONTWAIT);
		if (count == -1) {
			break;
		} else if (count == 0) {
	    	LOG_ERROR << "client " << process->sock << " close connection" << endl;
			cleanup(process);
			break;
		} else if (count > 0) {
			process->read_pos += count;
			_buf[process->read_pos] = 0;
			request.append(_buf);
			LOG_INFO << _buf << endl;
			LOG_INFO << "process->read_pos|" << process->read_pos << endl;
			if (process->read_pos == process->kBufferSize)
			{
				process->read_pos = 0;
			}
		}
	}
	int request_len = request.length();
	for (int i = request_len - 1; i >= 1; i--)
	{
		if (request[i] == '\0' || request[i] == '\r' || request[i] == '\n') {
			other_sign_num++;
			continue;
		}
		else
			break;
	}
	LOG_INFO << "other_sign_num|" << other_sign_num << endl;
	LOG_INFO << "-----recv-----" << endl;
	LOG_INFO << "from sock:" << process->sock << " type:" << process->type << endl;

	// 按行截取HTTP请求
	vector<string> line = Tool::split(request, "\n");
	int line_size = line.size();
	int blank_linenum = 0;

	// 获得空行的位置
	for (int i = 0; i < line_size; i++)
	{
	    if (line[i] == "" || line[i] == "\r") {
	        blank_linenum = i;
	        break;
	    }
	}
	if (blank_linenum == 0) {
		LOG_ERROR << "request is null" << endl;
		BAD_REQUEST
		return ;
	}

	// get first line
	string firstline = line[0];

	int first_blank = firstline.find(' ');
	int last_blank = firstline.find_last_of(' ');
	if (firstline.substr(0, 4) != "POST") {
		LOG_ERROR << "http request type error" << endl;
		BAD_REQUEST
		return ;
	}

	if (first_blank > 0 && last_blank > 0 && (last_blank - first_blank > 2))
	{
		module_name = firstline.substr(first_blank + 2, last_blank - first_blank - 2);
	} else {
		LOG_ERROR << "module name err|" << module_name << endl;
		BAD_REQUEST
		return ;
	}
	LOG_INFO << "module_name|" << module_name << endl;

	// 解析空行前(HTTP首部)的内容，如果有Content-Length这个属性就保存下来
	vector<string> prope_list;
	for (int i = 1; i < blank_linenum; i++)
	{
		prope_list = Tool::split(line[i], ": ");
		if (prope_list[0] == "Content-Length") {
			if (prope_list.size() == 2) {
				content_length = Tool::S2I(prope_list[1]);
				if (content_length < 0)
				{
					LOG_ERROR << "content_length err|" << prope_list[1] << endl;
					BAD_REQUEST
					return;
				}
			} else {
				LOG_ERROR << "prope list size err" << endl;
				BAD_REQUEST
				return;
			}
		}
	}
	LOG_INFO << "content_length|" << content_length << endl;
	LOG_INFO << line[blank_linenum + 1] << endl;

	// 判断空行下一行(即具体参数那行)是否为空
	if (line[blank_linenum + 1] == "" || line[blank_linenum + 1] == "\r") {
		LOG_ERROR << "param line is null" << endl;
		BAD_REQUEST
		return;
	}

	// 比对content_length与接收参数的长度是否一致
	if (content_length > 0)
	{
		if ((int)line[blank_linenum + 1].size() + other_sign_num != content_length) {
			LOG_ERROR << "content_length not equal" << endl;
			BAD_REQUEST
			return;
		}
	}

	// 解析参数行
	vector<string> param_list = Tool::split(line[blank_linenum + 1], "&");
	int param_list_len = param_list.size();
	map<string, string> param;
	for (int i = 0; i < param_list_len; i++)
	{
	    vector<string> _param = Tool::split(param_list[i], "=");
	    if (_param.size() == 2)
	    {
	        LOG_INFO << "key,val|" << _param[0] << "|" << _param[1] << endl;
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

	    LOG_INFO << "11qqqw" << endl;

	    MYSQL_RES *result = NULL;
	    MYSQL_FIELD *field = NULL;
	    MYSQL_ROW row = NULL;

	    result = mysql_store_result(&mysql);
	    int rowcount = mysql_num_rows(result);
	    int fieldcount = mysql_num_fields(result);
	    row = mysql_fetch_row(result);

	    LOG_INFO << rowcount << "|" << fieldcount << endl;

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
	    LOG_INFO << "md5:" << md5 << "|" << "suffix:" << suffix << "|" << "user_id" << user_id << endl;
	    // get file info
	    string file_path = config["UPLOAD_PATH"] + md5 + "_" + user_id + suffix;
	    LOG_INFO << "download filename:" << file_path << endl;

	    // struct _stat info;
    	// _stat(file_path.c_str(), &info);
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

	    // mysql_free_result(result);
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
	 		abort();
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
	LOG_INFO << "RECV|" << process->status << endl;
	switch(process->status)
	{
		case STATUS_UPLOAD_READY:
		{
			LOG_INFO << "STATUS_UPLOAD_READY" << endl;
			int sock = process->sock;
			char* _buf = process->buf;
			ssize_t count;
			string request;
			int content_length = 0;
			int other_sign_num = 0;
			// 接收HTTP请求
			while (1) {
				count = recv(sock, _buf + process->read_pos, process->kBufferSize - process->read_pos, MSG_DONTWAIT);
				if (count == -1) {
					break;
				} else if (count == 0) {
					break;
				} else if (count > 0) {
					process->read_pos += count;
					_buf[process->read_pos] = 0;
					request.append(_buf);
					LOG_INFO << _buf << endl;
					LOG_INFO << "process->read_pos|" << process->read_pos << endl;
					if (process->read_pos == process->kBufferSize)
					{
						process->read_pos = 0;
					}
				}
			}
			LOG_INFO << "-----recv-----" << endl;
			LOG_INFO << "from sock:" << process->sock << " type:" << process->type << endl;
			int request_len = request.length();
			// 将最后的等号替换成+，方便之后截取
			for (int i = request_len - 1; i >= 1; i--)
			{
				if (request[i] == '\0' || request[i] == '\r' || request[i] == '\n') {
					other_sign_num++;
					continue;
				}
				if (request[i] == '=')
					request[i] = '+';
				else
					break;
			}

			// 按行截取HTTP请求
			vector<string> line = Tool::split(request, "\n");
			int line_size = line.size();
			int blank_linenum = 0;

			// 获得空行的位置
			for (int i = 0; i < line_size; i++)
			{
			    if (line[i] == "" || line[i] == "\r") {
			        blank_linenum = i;
			        break;
			    }
			}
			if (blank_linenum == 0) {
				LOG_ERROR << "request is null" << endl;
				BAD_REQUEST
				return ;
			}

			// 解析空行前(HTTP首部)的内容，如果有Content-Length这个属性就保存下来
			vector<string> prope_list;
			for (int i = 1; i < blank_linenum; i++)
			{
				prope_list = Tool::split(line[i], ": ");
				if (prope_list[0] == "Content-Length") {
					if (prope_list.size() == 2) {
						content_length = Tool::S2I(prope_list[1]);
						if (content_length < 0)
						{
							LOG_ERROR << "content_length err|" << prope_list[1] << endl;
							BAD_REQUEST
							return;
						}
					} else {
						LOG_ERROR << "prope list size err" << endl;
						BAD_REQUEST
						return;
					}
				}
			}
			LOG_INFO << "content_length|" << content_length << endl;
			LOG_INFO << line[blank_linenum + 1] << endl;

			// 判断空行下一行(即具体参数那行)是否为空
			if (line[blank_linenum + 1] == "" || line[blank_linenum + 1] == "\r") {
				LOG_ERROR << "param line is null" << endl;
				BAD_REQUEST
				return;
			}

			// 比对content_length与接收参数的长度是否一致
			if (content_length > 0)
			{
				if ((int)line[blank_linenum + 1].size() + other_sign_num != content_length) {
					LOG_ERROR << "content_length not equal" << endl;
					BAD_REQUEST
					return;
				}
			}

			// 解析参数行
			vector<string> param_list = Tool::split(line[blank_linenum + 1], "&");
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
						int filedata_len = _param[1].size();
						for (int j = filedata_len - 1; j >= 1; j--)
						{
							if (_param[1][j] == '+')
								_param[1][j] = '=';
							else
								break;
						}
					}
			        LOG_INFO << "key,val|" << _param[0] << "|" << _param[1] << endl;
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
					write_to_header(header_200_start);
					write_to_header("\r\n");
					write_to_header("SUCC");
					write_to_header(header_end);
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
						abort();
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
				} else {
					// MD5不一致
					LOG_ERROR << "Fail! MD5 sum is inconsistent" << endl;
					BAD_REQUEST
				}
			} else {
    			// TODO::计算MD5失败
				LOG_ERROR << "Calc MD5 err" << endl;
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
	int sock = process->sock;
	char* buf = process->buf;
	char read_complete = 0;

	ssize_t count;

	while (1) {
		count = recv(sock, buf + process->read_pos, process->kBufferSize - process->read_pos, MSG_DONTWAIT);
		if (count == -1) {
			break;
		} else if (count == 0) {
	    	// 被客户端关闭连接
			del_timer(process->sock);
			cleanup(process);
			return;
		} else if (count > 0) {
			process->read_pos += count;
		}
	}
	int header_length = process->read_pos;
	LOG_INFO << "-----recv-----" << endl;
	LOG_INFO << "from sock:" << process->sock << " type:" << process->type << endl;
	buf[header_length]=0;
	LOG_INFO << buf << endl;
  	// 请求超长，不处理了
	if (header_length > process->kBufferSize - 1) {
		BAD_REQUEST
		return;
	}
	#if 0
	read_complete =(strstr(buf, "\n\n") != 0) ||(strstr(buf, "\r\n\r\n") != 0);
	#else
	read_complete = 1;
	#endif
	if (read_complete) {
    	// 重置读取位置
		reset_process(process);
		process->response_code = 200;
		// handle_read_request(process, buf);
	}
}
