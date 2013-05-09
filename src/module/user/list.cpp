#include "user.h"

/**
 * get follow list
 *  
 * @method get_follow_list
 * @param {int} page_no page_no which is used for get follow list
 * @param {int} page_size page_size which is used for get follow list
 * @param {string} sid sid which is used for mark whether login or not
 * @param {char*} respone data. 
 * @return {int} get_follow_list status.
 */
// int get_follow_list(int page_no, int page_size, string sid, char *buf, int &send_len) {
//     string respon_data;
//     Response::HTTPResponse *http_res = new Response::HTTPResponse();
//     string msg;
//     int result;
//     int ret;
//     int total;

//     LOG_INFO << "page_no is " << page_no << " page_size is " << page_size << " sid is " << sid << endl;

//     do {
//         // page_no or page_size or sid is not be found
//         if (page_no <= 0 || page_size <= 0 || Tool::trim(sid).empty()) {
//             result = PARAM_ERROR;
//             _set_http_head(result, false, "page_no or page_size or sid is not be found", http_res);
//             break;
//         }

//         // session is not exist
//         if (Session::get(sid) == NULL) {
//             result = SESSION_NOT_EXIST;
//             _set_http_head(result, false, "session not exist", http_res);
//             break;
//         }

//         Config *c = Config::get_instance();
//         map<string, string> config = c->get_config();
//         eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));
        
//         if (!e.connet()) {
//             result = SQL_CONNECT_FAIL;
//             _set_http_head(result, false, "sql connet fail", http_res);
//         }

//         int begin_pos = (page_no - 1) * page_size;
//         int uid = Tool::S2I(Session::get(sid)->uid);
//         ret = e.excute("select followed_id from t_follow where follow_id = " + Tool::mysql_filter(uid) + 
//         " order by id desc limit " + Tool::mysql_filter(begin_pos) + "," + Tool::mysql_filter(page_size) + ";");
//         if (ret != DB_OK) {
//             result = DB_ERROR;
//             _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
//             break;
//         }

//         MYSQL mysql;
//         mysql = e.get_mysql();

//         MYSQL_RES *mysql_result = NULL;
//         MYSQL_ROW row = NULL;

//         mysql_result = mysql_store_result(&mysql);
//         row = mysql_fetch_row(mysql_result);

//         // follow_list construtor
//         UserResponse::FollowListResponse *follow_list = new UserResponse::FollowListResponse();
//         e.count("t_follow", "where follow_id = " + Tool::mysql_filter(uid) + ";", total);
//         if (ret != DB_OK) {
//             result = DB_ERROR;
//             _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
//             break;
//         }
//         Data::List *people_list = new Data::List();
//         while(NULL != row) {
//             UserData::User_Info *user_info = people_list->add_user_info();
//         	   _get_user_info(Tool::S2I(row[0]), user_info);
//             row = mysql_fetch_row(mysql_result);
//         }
//         people_list->set_is_end(begin_pos + page_size >= total);
//         follow_list->set_allocated_people_list(people_list);

//         e.close();

//         result = GET_FOLLOW_LIST_SUCCESS;
//         _set_http_head(result, true, "get follow list success", http_res);
//         http_res->set_allocated_follow_list_response(follow_list);
//     }while(0);

//     print_proto(http_res);

//     http_res->SerializeToString(&respon_data);
//     memcpy(buf, respon_data.c_str(), respon_data.length());
//     send_len = respon_data.length();
//     google::protobuf::ShutdownProtobufLibrary();

//     return result;
// }

/**
 * get followed list
 *  
 * @method get_followed_list
 * @param {int} page_no page_no which is used for get followed list
 * @param {int} page_size page_size which is used for get followed list
 * @param {string} sid sid which is used for mark whether login or not
 * @param {char*} respone data. 
 * @return {int} get_followed_list status.
 */
// int get_followed_list(int page_no, int page_size, string sid, char *buf, int &send_len) {
//     string respon_data;
//     Response::HTTPResponse *http_res = new Response::HTTPResponse();
//     string msg;
//     int result;
//     int ret;
//     int total;

//     LOG_INFO << "page_no is " << page_no << " page_size is " << page_size << " sid is " << sid << endl;

//     do {
//         // page_no or page_size or sid is not be found
//         if (page_no <= 0 || page_size <= 0 || Tool::trim(sid).empty()) {
//             result = PARAM_ERROR;
//             _set_http_head(result, false, "page_no or page_size or sid is not be found", http_res);
//             break;
//         }

//         // session is not exist
//         if (Session::get(sid) == NULL) {
//             result = SESSION_NOT_EXIST;
//             _set_http_head(result, false, "session not exist", http_res);
//             break;
//         }

//         Config *c = Config::get_instance();
//         map<string, string> config = c->get_config();
//         eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));
        
//         if (!e.connet()) {
//             result = SQL_CONNECT_FAIL;
//             _set_http_head(result, false, "sql connet fail", http_res);
//         }

//         int begin_pos = (page_no - 1) * page_size;
//         int uid = Tool::S2I(Session::get(sid)->uid);
//         ret = e.excute("select follow_id from t_follow where followed_id = " + Tool::mysql_filter(uid) + 
//         " order by id desc limit " + Tool::mysql_filter(begin_pos) + "," + Tool::mysql_filter(page_size) + ";");
//         if (ret != DB_OK) {
//             result = DB_ERROR;
//             _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
//             break;
//         }

//         MYSQL mysql;
//         mysql = e.get_mysql();

//         MYSQL_RES *mysql_result = NULL;
//         MYSQL_ROW row = NULL;

//         mysql_result = mysql_store_result(&mysql);
//         row = mysql_fetch_row(mysql_result);

//         // followed_list construtor
//         UserResponse::FollowedListResponse *followed_list = new UserResponse::FollowedListResponse();
//         e.count("t_follow", "where followed_id = " + Tool::mysql_filter(uid) + ";", total);
//         if (ret != DB_OK) {
//             result = DB_ERROR;
//             _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
//             break;
//         }
//         Data::List *people_list = new Data::List();
//         while(NULL != row) {
//             UserData::User_Info *user_info = people_list->add_user_info();
//             _get_user_info(Tool::S2I(row[0]), user_info);
//             row = mysql_fetch_row(mysql_result);
//         }
//         people_list->set_is_end(begin_pos + page_size >= total);
//         followed_list->set_allocated_people_list(people_list);

//         e.close();

//         result = GET_FOLLOWED_LIST_SUCCESS;
//         _set_http_head(result, true, "get followed list success", http_res);
//         http_res->set_allocated_followed_list_response(followed_list);
//     }while(0);

//     print_proto(http_res);

//     http_res->SerializeToString(&respon_data);
//     memcpy(buf, respon_data.c_str(), respon_data.length());
//     send_len = respon_data.length();
//     google::protobuf::ShutdownProtobufLibrary();

//     return result;
// }