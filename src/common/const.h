#ifndef INDEX_FILE
#define INDEX_FILE "/index.htm"
#endif

#ifndef header_200_start
#define header_200_start "HTTP/1.1 200 OK\r\n" \
"Content-Type: image/bmp\r\n"
#endif

#ifndef header_400
#define header_400 "HTTP/1.1 400 Bad Request\r\n" \
    "Content-Type: text/html\r\nConnection: Close\r\n\r\n<h1>Bad request</h1>"
#endif

#ifndef HEADER_CONTENT_LENGTH
#define HEADER_CONTENT_LENGTH "Content-Length: "
#endif

#ifndef header_end
#define header_end "\r\n"
#endif
    
#ifndef copy_str
#define copy_str(dst, src) strncpy(dst, src, strlen(src) + 1)
#endif

#ifndef write_to_header
#define write_to_header(string_to_write) copy_str(process->buf + strlen(process->buf), string_to_write)
#endif

#ifndef TIMER_INFINITE
#define TIMER_INFINITE -1
#endif

#ifndef USE_TCP_CORK
#define USE_TCP_CORK 1
#endif

#ifndef STR_VALUE
#define STR_VALUE(val) #val
#endif

#ifndef STR
#define STR(name) STR_VALUE(name)
#endif

#ifndef PATH_LEN
#define PATH_LEN 256
#endif

#ifndef MD5_LEN
#define MD5_LEN 32
#endif

#ifndef _CONST_H_
#define _CONST_H_


// 监听端口的数目
const int LISTEN_PORT_SIZE = 3;
// 处理HTTP的类型标识
const int LISTEN_HTTP_REQ_TYPE = 0;
// 处理文件上传的类型标识
const int LISTEN_UPLOAD_REQ_TYPE = 1;
// 处理长连接的类型标识
const int LISTEN_TCP_REQ_TYPE = 2;

// 最大socket数
const int MAX_PORCESS = 10000;
// 处理的最大事件数
const int MAXEVENTS = 10000;
// 用于标识process的sock
const int NO_SOCK = -1;
// 用于标识process的fd
const int NO_FILE = -1;
// 用于标识process的type
const int NO_TYPE = -1;
// 用于标识process的status
const int NO_STATUS = -1;


// process中status的不同状态的标识
const int STATUS_READ = 1;
const int STATUS_HANDLE_READ_REQUEST = 2;
const int STATUS_SEND_RESPONSE_HEADER = 3;
const int STATUS_SEND_RESPONSE = 4;
const int STATUS_UPLOAD_READY = 5;
const int STATUS_UPLOAD_ONGOING = 6;
const int STATUS_UPLOAD_FINISHED = 7;

// 功能模块的标识码
const int USER_MODULE = 100;
const int ROOM_MODULE = 200;

// user action code.
const int USER_REGIEST = 101;
const int USER_LOGIN = 102;

// system status code
const int PARAM_ERROR = 1001;

// regiest result.
const int REGIEST_SUCCESS = 11000;
const int USERNAME_IS_EXIST = 11001;

#endif





