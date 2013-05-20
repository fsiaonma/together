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
memset(process->buf, 0, process->kBufferSize); \
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
#define DEBUG 0
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
static const int MESSAGE_MODULE = 300;

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
static const int GET_FOLLOWING_LIST = 109;
static const int GET_FOLLOWERS_LIST = 111;
static const int USER_UNFOLLOW = 112;
static const int GET_MSG_LIST = 113;

// ============ ROOM ============
static const int ROOM_CREATE = 201;
static const int ROOM_SHOWLIST = 202;
static const int ROOM_JOIN = 203;
static const int ROOM_QUIT = 204;
static const int ROOM_PEOPLE_LIST = 205;
static const int SHOW_ROOM_INFO = 206;
static const int SHOW_USER_ROOM = 207;

// ============ CHAT ============
static const int BIND_USER_CHAT = 301;
static const int SAVE_MSG = 302;
static const int START_ROOM = 303;
static const int LC_JOIN_ROOM = 304;
static const int LC_QUIT_ROOM = 305;

// ============ MESSAGE ============
static const int GROUP_CHAT = 1;
static const int PRIVATE_CHAT = 2;
static const int GET_MSG = 401;
static const int CHANGE_MSG_STATUS = 402;

// --------------- Status Code -----------roomId=1001&sid=b7fbee9a885057aa638df19ecfccb5ba----
// ============ System ============
static const int PARAM_ERROR = 1001;
static const int DB_ERROR = 1002;
static const int DB_NO_DATA = 1003;

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
static const int DB_PR_QUIT_ROOM_ISOWNER = 5106;
static const int DB_PR_INSERT_MSG_SENDER_NOTEXIST = 5107;
static const int DB_PR_INSERT_MSG_ROOM_NOTEXIST = 5108;
static const int DB_PR_INSERT_MSG_RECIPIENT_NOTEXIST = 5109;
static const int DB_PR_INSERT_MSG_MSGTYPE_ERROR = 5110;
static const int DB_PR_INSERT_MSG_SUCCESS = 5110;

// ============ Session ============
static const int SESSION_OK = 6000;
static const int SESSION_NOT_EXIST = 6001;

// ============ Chat ============
static const int CHAT_PARAM_ERR = 7000;
static const int CHAT_HANDLE_ERR = 7001;


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
static const int USER_CANT_PRISE_HIMSELF = 16002;

// set user follow result code
static const int USER_FOLLOW_SUCCESS = 17000;
static const int USER_ALREADY_FOLLOW = 17001;
static const int USER_FOLLOW_FAIL = 17002;
static const int USER_CANT_FOLLOW_HIMSELF = 17003;

// check username is exist code
static const int USERNAME_AVAILABLE = 18000;

// get follow list code
static const int GET_FOLLOWING_LIST_SUCCESS = 19000;

// get followed list code
static const int GET_FOLLOWERS_LIST_SUCCESS = 11100;

// unfollow user code
static const int USER_UNFOLLOW_SUCCESS = 11200;
static const int USER_HAVENT_FOLLOW = 11201;
static const int USER_UNFOLLOW_FAIL = 11202;

// get all new message code
static const int GET_MSG_LIST_SUCCESS = 11300;

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
static const int QUIT_ROOM_ISOWNER = 21009;

static const int SHOW_ROOM_PEO_LIST_SUCCESS = 21010;

static const int SHOW_ROOM_INFO_SUCCESS = 21011;
static const int SHOW_ROOM_INFO_ROOM_NOTEXIST = 21012;

static const int SHOW_USER_ROOM_SUCCESS = 21013;

// ============ Chat ============
static const int BIND_USER_CHAT_SUCCESS = 31000;
static const int BIND_USER_CHAT_USER_NOTEXIST = 31001;
static const int SAVE_MSG_SINGLE_SUCCESS = 31002;
static const int SAVE_MSG_GROUP_SUCCESS = 31003;
static const int SAVE_MSG_SENDER_NOTEXIST = 31004;
static const int SAVE_MSG_ROOM_NOTEXIST = 31005;
static const int SAVE_MSG_RECIPIENT_NOTEXIST = 31006;
static const int SAVE_MSG_MSGTYPE_ERROR = 31007;
static const int START_ROOM_SUCCESS = 31008;
static const int START_ROOM_ISNOT_OWNER = 31009;
static const int START_ROOM_HASSTARTED_OR_NOTEXIST = 31010;
static const int LC_JOIN_ROOM_SUCCESS = 31011;
static const int LC_QUIT_ROOM_SUCCESS = 31012;

// ============ Message ============
// get message code
static const int GET_LATEST = -1;
static const int GET_PREVIOUS = 0;
static const int GET_FOLLOW = 1;
static const int GET_MSG_SUCCESS = 41000;
static const int GET_MSG_FAIL = 41001;

// message status code
static const bool MSG_NOT_READ = false;
static const bool MSG_HAVE_READ = true;
static const int CHANGE_MSG_STATUS_FAIL = 42000;
static const int CHANGE_MSG_STATUS_SUCCESS = 42001;

#endif





