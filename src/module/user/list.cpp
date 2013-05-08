#include "user.h"

/**
 * get follow list
 *  
 * @method follow
 * @param {int} page_no page_no which is used for get follow list
 * @param {int} page_size page_size which is used for get follow list
 * @param {int} uid uid which is used for mark the user
 * @param {string} sid sid which is used for mark whether login or not
 * @param {char*} respone data. 
 * @return {int} get_follow_list status.
 */
// int get_follow_list(int page_no, int page_size, int uid, string sid, char *buf) {
//     string respon_data;
//     Response::HTTPResponse *http_res = new Response::HTTPResponse();
//     string msg;
//     int result;
//     int ret;
//     int total;

//     do {
//         LOG_INFO << "uid is " << uid << endl;
        
//         // uid
//         if (uid <= 0) {
//             result = PARAM_ERROR;
//             _set_http_head(result, false, "uid is not found", http_res);
//             break;
//         }

//         Config *c = Config::get_instance();
//         map<string, string> config = c->get_config();
//         eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));
        
//         if (!e.connet()) {
//             result = SQL_CONNECT_FAIL;
//             _set_http_head(result, false, "sql connet fail", http_res);
//         }

//         ret = e.excute("select followed_id from t_follow where follow_id = " + Tool::mysql_filter(uid) + 
//         " order by id desc limit " + Tool::mysql_filter(page_no * page_size) + " " + Tool::mysql_filter(page_size) + ";");
//         if (ret != DB_OK) {
//             result = DB_ERROR;
//             _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
//             break;
//         }

//         MYSQL mysql;
//         mysql = e.get_mysql();

//         MYSQL_RES *result = NULL;
//         MYSQL_ROW row = NULL;

//         result = mysql_store_result(&mysql);
//         int fieldcount = mysql_num_fields(result);
//         row = mysql_fetch_row(result);

//         // follow_list construtor
//         UserResponse::FollowListResponse *follow_list = new UserResponse::FollowListResponse();
//         e.count("t_follow", "where follow_id = " + Tool::mysql_filter(uid) + ";", total);
//         if (ret != DB_OK) {
//             result = DB_ERROR;
//             _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
//             break;
//         }
//         people_list.set_is_end(page_no * page_size + page_size >= total);
//         Data::List *people_list = new Data::List();
//         while(NULL != row) {
//             UserData::User_Info *user_info;
//             user_info->set_uid(Tool::S2I(row[0]));
//             people_list->add_user_info(user_info);
//         }
//         follow_list->set_allocated_people_list(people_list);

//         e.close();

//         result = GET_FOLLOW_LIST_SUCCESS;
//         _set_http_head(result, true, "get follow list success", http_res);
//         http_res->set_allocated_follow_list_response(user_list);
//     }while(0);

//     print_proto(http_res);

//     http_res->SerializeToString(&respon_data);
//     const char *p = respon_data.c_str();
//     strncpy(buf, p, strlen(p) + 1);
//     google::protobuf::ShutdownProtobufLibrary();

//     return result;
// }