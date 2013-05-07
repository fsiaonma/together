#ifndef INDEX_FILE
#define INDEX_FILE "/index.htm"
#endif

#ifndef header_200_start
#define header_200_start "HTTP/1.1 200 OK\r\n" \
"Content-Type: text/html\r\n"
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

#ifndef BAD_REQUEST
#define BAD_REQUEST process->response_code = 400; \
process->status = STATUS_SEND_RESPONSE_HEADER; \
strncpy(process->buf, header_400, sizeof(header_400)); \
send_response_header(process); \
handle_error(process, "bad request");
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

#ifndef MD5_LEN
#define MD5_LEN 32
#endif

#ifndef DEBUG
#define DEBUG 1
#endif

#ifndef _CONST_H_
#define _CONST_H_

// 监听端口的数目
static const int LISTEN_PORT_SIZE = 3;
// 处理HTTP的类型标识
static const int LISTEN_HTTP_REQ_TYPE = 0;
// 处理文件上传的类型标识
static const int LISTEN_UPLOAD_REQ_TYPE = 1;
// 处理长连接的类型标识
static const int LISTEN_TCP_REQ_TYPE = 2;

// 最大socket数
static const int MAX_PORCESS = 10000;
// 处理的最大事件数
static const int MAXEVENTS = 10000;
// 用于标识process的sock
static const int NO_SOCK = -1;
// 用于标识process的fd
static const int NO_FILE = -1;
// 用于标识process的type
static const int NO_TYPE = -1;
// 用于标识process的status
static const int NO_STATUS = -1;


// process中status的不同状态的标识
static const int STATUS_READ = 1;
static const int STATUS_HANDLE_READ_REQUEST = 2;
static const int STATUS_SEND_RESPONSE_HEADER = 3;
static const int STATUS_SEND_RESPONSE = 4;
static const int STATUS_UPLOAD_READY = 5;
static const int STATUS_UPLOAD_FINISHED = 6;

// others
static const int GENDERTYPE_NUM = 3;

// --------------- Module Code ---------------
// 功能模块的标识码
static const int UNKNOWN_MODULE = 99;
static const int USER_MODULE = 100;
static const int ROOM_MODULE = 200;

// --------------- Module Action Code ---------------
// ============ USER ============
static const int USER_REGIEST = 101;
static const int USER_LOGIN = 102;
static const int USER_LOGOUT = 103;
static const int USER_VIEW_INFO = 104;
static const int USER_SET_INFO = 105;
static const int USER_PRISE = 106;
static const int USER_FOLLOW = 107;
static const int USER_IS_EXIST = 108;


// ============ ROOM ============
static const int ROOM_CREATE = 201;
static const int ROOM_SHOWLIST = 202;
static const int ROOM_JOIN = 203;
static const int ROOM_QUIT = 204;


// --------------- Status Code ---------------
// ============ System ============
static const int PARAM_ERROR = 1001;
static const int DB_ERROR = 1002;

// ============ DataBase ============
static const int DB_OK = 5000;
static const int DB_CONNECT_FAIL = 5001;
static const int DB_COUNT_ERR = 5002;
static const int DB_QUERY_ERR = 5003;
// ----- procedure status code -----
static const int DB_PR_PARAM_ERR = 5100;
static const int DB_PR_ERR = 5199;
static const int DB_PR_JOIN_ROOM_SUCCESS = 5101;
static const int DB_PR_JOIN_ROOM_HAVEBEENJOINED = 5102;
static const int DB_PR_JOIN_ROOM_OVERLIMITNUM = 5103;
static const int DB_PR_QUIT_ROOM_SUCCESS = 5104;
static const int DB_PR_QUIT_ROOM_NOTJOINED = 5105;

// ============ Session ============
static const int SESSION_OK = 6000;
static const int SESSION_NOT_EXIST = 6001;


// --------------- Function Result Code ---------------
// ============ User ============
// regiest result code
static const int REGIEST_SUCCESS = 11000;
static const int REGIEST_FAIL = 11001;
static const int USERNAME_IS_EXIST = 11002;

// login result code
static const int LOGIN_SUCCESS = 12000;
static const int USER_NOT_EXIST = 12001;
static const int LOGIN_REPLACE = 12002;

// logout result code
static const int LOGOUT_SUCCESS = 13000;

// view user info result code
static const int VIEW_USER_INFO_SUCCESS = 14000;

// set user info result code
static const int SET_USER_INFO_SUCCESS = 15000; 

// set user prise result code
static const int USER_PRISE_SUCCESS = 16000;
static const int USER_PRISE_FAIL = 16001;

// set user follow result code
static const int USER_FOLLOW_SUCCESS = 17000;
static const int USER_ALREADY_FOLLOW = 17001;
static const int USER_FOLLOW_FAIL = 17002;

// check username is exist code
static const int USERNAME_AVAILABLE = 18000;

// ============ Room ============
static const int CREATE_ROOM_SUCCESS = 21000;

static const int SHOW_ROOM_LIST_SUCCESS = 21001;

static const int JOIN_ROOM_SUCCESS = 21002;
static const int JOIN_ROOM_USER_OR_ROOM_NOEXIST = 21003;
static const int JOIN_ROOM_HAVEBEENJOINED = 21004;
static const int JOIN_ROOM_OVERLIMITNUM = 21005;

static const int QUIT_ROOM_SUCCESS = 21006;
static const int QUIT_ROOM_USER_OR_ROOM_NOEXIST = 21007;
static const int QUIT_ROOM_NOTJOINED = 21008;

#endif





