#include "./recv.h"
#include "./close.h"
#include "./send.h"


/**
* 从参数字符串中解析参数放入map中
**/
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
        LOG << "key:" << it->first << "|val:" << it->second << endl;
    }
	return m;
}

void handle_read_request(process *process, char *module, map<string, string> param) {
	LOG << "handle_read_request" << endl;
	int module_type = get_module_type(module);
	int s;
	
	switch (module_type) {
		case USER_MODULE:
		{	
			s = user_handler(process, param);
			if (s == -1)
				break;
			else {
				process->status = STATUS_SEND_RESPONSE_HEADER;
			    // 修改此 sock 的监听状态，改为监视写状态
				event.data.fd = process->sock;
				event.events = EPOLLOUT;
				s = epoll_ctl(efd, EPOLL_CTL_MOD, process->sock, &event);
				if (s == -1) {
					ERR << "epoll_ctl error" << endl;
					abort();
				}
				LOG << "------send header------" << endl;
				LOG << process->buf << endl;
			}
			break;
		}
		case ROOM_MODULE:
		{
			//room_handler(process, req);
			break;
		}
		default:
		break;
	}
}


/**
*接收HTTP请求(LISTEN_HTTP_REQ_PORT端口)
**/
void read_http_request(process* process)
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
	    	LOG << "client " << process->sock << " close connection" << endl;
			del_timer(process->sock);
			cleanup(process);
			return;
		} else if (count > 0) {
			process->read_pos += count;
		}
	}

	int header_length = process->read_pos;
	LOG << "-----recv-----" << endl;
	LOG << "from sock:" << process->sock << " type:" << process->type << endl;
	buf[header_length]=0;
	LOG << buf << endl;
  	// 请求超长，不处理了
	if (header_length > process->kBufferSize - 1) {
		process->response_code = 400;
		process->status = STATUS_SEND_RESPONSE_HEADER;
    	strncpy(process->buf, header_400, sizeof(header_400));
		send_response_header(process);
		handle_error(process, "bad request");
		return;
	}
	buf[header_length]=0;
	read_complete =(strstr(buf, "\n\n") != 0) ||(strstr(buf, "\r\n\r\n") != 0);
	if (read_complete) {
    	// 重置读取位置
		reset_process(process);
		// 传输格式的位置 POST的时候format_pos=4,GET的时候format_post=3
		int format_pos = -1;
		if (strncmp(buf, "POST", 4) == 0) {
    		format_pos = 4;
		} else if (strncmp(buf, "GET", 3) == 0) {
    		format_pos = 3;
		}
		LOG << "format_pos|" << format_pos << endl;
		if (format_pos < 0)
		{
			process->response_code = 400;
			process->status = STATUS_SEND_RESPONSE_HEADER;
	    	strncpy(process->buf, header_400, sizeof(header_400));
			send_response_header(process);
			handle_error(process, "bad request");
			return;
		}

		// 解析第一行
		const char *n_loc = strchr(buf, '\n');
		const char *space_loc = strchr(buf + format_pos + 1, ' ');
		if (n_loc <= space_loc) {
			ERR << "read first line error" << endl;
			process->response_code = 400;
			process->status = STATUS_SEND_RESPONSE_HEADER;
	    	strncpy(process->buf, header_400, sizeof(header_400));
			send_response_header(process);
			handle_error(process, "bad request");
			return;
		}

		// 解析出模块名
		char module[50];
		int module_len = space_loc - buf - (format_pos + 2);
		strncpy(module, buf + (format_pos + 2), module_len);
		module[module_len] = 0;
		LOG << "module name|" << module << endl;


		// 如果首部有Content-Length就解析出来
		int content_length = -1;
		char temp[10];
		char *c = strstr(buf, HEADER_CONTENT_LENGTH);
		if (c != 0)
		{
		    char *rn = strchr(c, '\r');
		    if (rn == 0)
		    {
		        rn = strchr(c, '\n');
		        if (rn == 0)
		        {
		        	ERR << "not found line break" << endl;
					process->response_code = 400;
					process->status = STATUS_SEND_RESPONSE_HEADER;
			    	strncpy(process->buf, header_400, sizeof(header_400));
					send_response_header(process);
					handle_error(process, "bad request");
					return;
		        }
		    }
		    int l = rn - c - sizeof(HEADER_CONTENT_LENGTH) + 1;
		    strncpy(temp, c + sizeof(HEADER_CONTENT_LENGTH) - 1, l);
		    temp[l] = 0;
			LOG << "Content-Length|" << temp << endl;
			content_length = atoi(temp);
		}

		// 解析最后一行
		int request_len = strlen(buf);

		int last_line_begin = 0;
		int count = 0;
		int i = request_len - 1;
		int last_line_end = i;
		for (; i >= 0; i--)
		{
		    if (*(buf + i) == '\n')
		    {
		    	if (last_line_begin == 0)
		        {
		            last_line_begin = i + 1;
		            break;
		        }
		    }
		}

		char param_data[200];
		int param_len = last_line_end - last_line_begin + 1;
		strncpy(param_data, buf + last_line_begin, param_len);
		param_data[param_len] = 0;
		LOG << "param data|" << param_data << endl;

		// 最后一行长度为0则视为数据出错
		if (param_len == 0)
		{
			ERR << "receive data is null" << endl;
			process->response_code = 400;
			process->status = STATUS_SEND_RESPONSE_HEADER;
		    strncpy(process->buf, header_400, sizeof(header_400));
			send_response_header(process);
			handle_error(process, "bad request");
			return;
		}

		// 如果首部有Content-Length,就比较与当前接收到的数据长度是否一致
		if (content_length > 0)
		{
			if (content_length != strlen(param_data))
			{
				ERR << "receive data size not same" << endl;
				process->response_code = 400;
				process->status = STATUS_SEND_RESPONSE_HEADER;
		    	strncpy(process->buf, header_400, sizeof(header_400));
				send_response_header(process);
				handle_error(process, "bad request");
				return;
			} else {
				LOG << "receive data size same" << endl;
			}
		}

		// 解析参数
		map<string, string> param = parse_param(param_data);
		if (param.empty())
		{
			ERR << "param is null" << endl;
			process->response_code = 400;
			process->status = STATUS_SEND_RESPONSE_HEADER;
		    strncpy(process->buf, header_400, sizeof(header_400));
			send_response_header(process);
			handle_error(process, "bad request");
			return;
		}


		process->response_code = 200;
		handle_read_request(process, module, param);
	}
}

/**
*接收文件数据,保存到硬盘
**/
int recv_file(process* process, const char* filename) 
{ 
    int rval; 
    int read_total = 0;
    char *buf = process->buf; 
    int sock = process->sock;
    FILE *file = fopen(filename, "a+b"); 
    if (!file)
    {
        ERR << "Can't open file for writing" << endl;
        return -1;
    }

    do
    {
        rval = recv(sock, buf, sizeof(buf), 0);
        if (rval < 0)
        {
            if (errno != EAGAIN) {
	            ERR << "Can't read from socket" << "|" << rval << "|" << errno << endl;
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
                ERR << "Can't write to file" << endl;
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
*接收HTTP请求,解析后开始接收文件数据,保存(LISTEN_UPLOAD_REQ_PORT端口)
**/
void read_upload_request(process* process)
{
	int s;
	LOG << "RECV|" << process->status << endl;
	switch(process->status)
	{
		case STATUS_UPLOAD_READY:
		{
			LOG << "STATUS_UPLOAD_READY" << endl;
			int sock = process->sock;
			char* buf = process->buf;
			ssize_t count;
			while (1) {
				count = recv(sock, buf + process->read_pos, process->kBufferSize - process->read_pos, MSG_DONTWAIT);
				if (count == -1) {
					break;
				} else if (count == 0) {
			    	// 被客户端关闭连接
			    	LOG << "client " << process->sock << " close connection" << endl;
					cleanup(process);
					return;
				} else if (count > 0) {
					process->read_pos += count;
				}
			}
			int header_length = process->read_pos;
			LOG << "-----recv-----" << endl;
			LOG << "from sock:" << process->sock << " type:" << process->type << endl;
			buf[header_length]=0;
			LOG << buf << endl;
			
			// TODO:: 解析HTTP请求并设置好对应的文件总长度和md5
			#if 1
			if (!(strncmp(buf, "POST", 4) == 0 || strncmp(buf, "GET", 3) == 0) ) 
			{
				process->response_code = 400;
				process->status = STATUS_SEND_RESPONSE_HEADER;
		    	strncpy(process->buf, header_400, sizeof(header_400));
				send_response_header(process);
				handle_error(process, "bad request");
				return;
			}

			// 如果首部有Content-Length就解析出来
			int content_length = -1;
			char temp[10];
			char *c = strstr(buf, HEADER_CONTENT_LENGTH);
			if (c != 0)
			{
			    char *rn = strchr(c, '\r');
			    if (rn == 0)
			    {
			        rn = strchr(c, '\n');
			        if (rn == 0)
			        {
			        	ERR << "not found line break" << endl;
						process->response_code = 400;
						process->status = STATUS_SEND_RESPONSE_HEADER;
				    	strncpy(process->buf, header_400, sizeof(header_400));
						send_response_header(process);
						handle_error(process, "bad request");
						return;
			        }
			    }
			    int l = rn - c - sizeof(HEADER_CONTENT_LENGTH) + 1;
			    strncpy(temp, c + sizeof(HEADER_CONTENT_LENGTH) - 1, l);
			    temp[l] = 0;
				LOG << "Content-Length|" << temp << endl;
				content_length = atoi(temp);
			}

			// 解析最后一行
			int request_len = strlen(buf);

			int last_line_begin = 0;
			int i = request_len - 1;
			int last_line_end = i;
			for (; i >= 0; i--)
			{
			    if (*(buf + i) == '\n')
			    {
			    	if (last_line_begin == 0)
			        {
			            last_line_begin = i + 1;
			            break;
			        }
			    }
			}

			char param_data[200];
			int param_len = last_line_end - last_line_begin + 1;
			strncpy(param_data, buf + last_line_begin, param_len);
			param_data[param_len] = 0;
			LOG << param_len << endl;
			LOG << "param data|" << param_data << endl;

			// 最后一行长度为0则视为数据出错
			if (param_len == 0)
			{
				ERR << "receive data is null" << endl;
				process->response_code = 400;
				process->status = STATUS_SEND_RESPONSE_HEADER;
			    strncpy(process->buf, header_400, sizeof(header_400));
				send_response_header(process);
				handle_error(process, "bad request");
				return;
			}

			// 如果首部有Content-Length,就比较与当前接收到的数据长度是否一致
			if (content_length > 0)
			{
				if (content_length != strlen(param_data))
				{
					ERR << "receive data size not same" << endl;
					process->response_code = 400;
					process->status = STATUS_SEND_RESPONSE_HEADER;
			    	strncpy(process->buf, header_400, sizeof(header_400));
					send_response_header(process);
					handle_error(process, "bad request");
					return;
				} else {
					LOG << "receive data size same" << endl;
				}
			}

			// 解析参数
			map<string, string> param = parse_param(param_data);
			if (param.empty())
			{
				ERR << "param is null" << endl;
				process->response_code = 400;
				process->status = STATUS_SEND_RESPONSE_HEADER;
			    strncpy(process->buf, header_400, sizeof(header_400));
				send_response_header(process);
				handle_error(process, "bad request");
				return;
			}
			#endif

			if (! (param.count("md5") > 0 && param.count("file_size") > 0) )
			{
				ERR << "md5 or file_size not exist" << endl;
				process->response_code = 400;
				process->status = STATUS_SEND_RESPONSE_HEADER;
			    strncpy(process->buf, header_400, sizeof(header_400));
				send_response_header(process);
				handle_error(process, "bad request");
				return;
			}

			if (!Tool::isNum(param["file_size"]))
			{
				ERR << "file_size error|" << param["file_size"] << endl;
				process->response_code = 400;
				process->status = STATUS_SEND_RESPONSE_HEADER;
			    strncpy(process->buf, header_400, sizeof(header_400));
				send_response_header(process);
				handle_error(process, "bad request");
				return;
			}
			process->total_length = Tool::S2I(param["file_size"]);
			// char md5[] = "cefcb8e6d025249ad9156f30c0c7fe8c";
			strncpy(process->md5, param["md5"].c_str(), 33);
			if (param.count("suffix"))
			{
				strncpy(process->suffix, param["suffix"].c_str(), strlen(param["suffix"].c_str()) + 1);
			} else {
				process->suffix[0] = 0;
			}
			LOG << "total_length|" << process->total_length << endl;
			LOG << "MD5|" << process->md5 << endl;
			LOG << "suffix|" << process->suffix << endl;
			process->status = STATUS_UPLOAD_ONGOING;
			break;
		}
		case STATUS_UPLOAD_ONGOING:
		{
			LOG << "STATUS_UPLOAD_ONGOING" << endl;
			char file_name[256];
			Config *c = Config::get_instance();
			map<string, string> config = c->get_config();
			sprintf(file_name, "%s%s%s", config["UPLOAD_PATH"].c_str(), process->md5, process->suffix);
			LOG << "save filename|" << file_name << endl;
			// const char *file_name = "./test.bmp";
			s = recv_file(process, file_name);
			LOG << "recv file " << s << endl;
			if (s < 0)
			{
				// TODO::
				process->response_code = 400;
				process->status = STATUS_SEND_RESPONSE_HEADER;
		    	strncpy(process->buf, header_400, sizeof(header_400));
				send_response_header(process);
				handle_error(process, "bad request");
				break;
			}
			if (s == process->total_length)
			{
				LOG << "recv file finish" << endl;
				process->status = STATUS_UPLOAD_FINISHED;
				LOG << process->status << endl;
			} else {
				break;
			}
		}
		case STATUS_UPLOAD_FINISHED:
		{
			LOG << "STATUS_UPLOAD_FINISHED" << endl;
		    // TODO::保存文件成功,之后判断接收到的文件MD5与预期的是否一样,一样的话就写入数据库.返回响应信息
    		LOG << "save file succ!" << endl;
    		char md5[MD5_LEN + 1];
			char file_name[256];
			Config *c = Config::get_instance();
			map<string, string> config = c->get_config();
			sprintf(file_name, "%s%s%s", config["UPLOAD_PATH"].c_str(), process->md5, process->suffix);
    		if (Tool::calc_file_MD5(file_name, md5))
    		{
    			LOG << "Calc Success! MD5 sum :" << md5 << endl;
    			if (strcmp(md5, process->md5) == 0)
    			{
	    			LOG << "Success! MD5 sum is consistent" << endl;
	    			process->response_code = 200;
				    memset(process->buf, 0, sizeof(char) * process->kBufferSize); 
				    process->buf[0] = 0;
					write_to_header(header_200_start);
					write_to_header("\r\n");
					write_to_header("SUCC");
					write_to_header(header_end);
					process->status = STATUS_SEND_RESPONSE_HEADER;

					// 修改此 sock 的监听状态，改为监视写状态
					event.data.fd = process->sock;
					event.events = EPOLLOUT;
					s = epoll_ctl(efd, EPOLL_CTL_MOD, process->sock, &event);
					if (s == -1) {
						ERR << "epoll_ctl error" << endl;
						abort();
					}
    			} else {
					// MD5不一致
	    			LOG << "Fail! MD5 sum is inconsistent" << endl;
					process->response_code = 400;
					process->status = STATUS_SEND_RESPONSE_HEADER;
			    	strncpy(process->buf, header_400, sizeof(header_400));
					send_response_header(process);
					handle_error(process, "bad request");
    			}
    		} else {
    			// TODO::计算MD5失败
    			ERR << "Calc MD5 ERROR" << endl;
				process->response_code = 400;
				process->status = STATUS_SEND_RESPONSE_HEADER;
			    strncpy(process->buf, header_400, sizeof(header_400));
				send_response_header(process);
				handle_error(process, "bad request");
    		}
    		process->status = STATUS_UPLOAD_READY;
			break;
		}
		default:
		break;
	}
}

/**
*接收长连接请求(LISTEN_TCP_REQ_PORT端口)
**/
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
	LOG << "-----recv-----" << endl;
	LOG << "from sock:" << process->sock << " type:" << process->type << endl;
	buf[header_length]=0;
	LOG << buf << endl;
  	// 请求超长，不处理了
	if (header_length > process->kBufferSize - 1) {
		process->response_code = 400;
		process->status = STATUS_SEND_RESPONSE_HEADER;
    	strncpy(process->buf, header_400, sizeof(header_400));
		send_response_header(process);
		handle_error(process, "bad request");
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
