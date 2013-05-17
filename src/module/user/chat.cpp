#include "user.h"
#include "../message/message_base.h"

// /*
//  * judge whether there is exist new message or not
//  *  
//  * @method exist_new_msg
//  * @param {int} current_id current message id.
//  * @return {int} exist_new_msg status.
//  */
// int exist_new_msg(int current_id, int recipient_id, int &exist) {
//     int result;
//     int ret;

//     LOG_INFO << "current_id is " << current_id << " recipient_id is " << recipient_id << endl;

//     do {
//         if (current_id <= 0 || recipient_id < 0) {
//             result = PARAM_ERROR;
//             LOG_ERROR << "current_id or recipient_id is not exist" << endl;
//             break; 
//         }
//         ret = e.is_exist("t_message", "where id>" + Tool::mysql_filter(current_id) + " and recipient_id=" + Tool::mysql_filter(recipient_id) + " type='user'", exist);
//         if (ret != DB_OK) {
//             result = DB_ERROR;
//             _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
//             break;
//         }
//     } while(0);

//     return result;
// } 

// /*
//  * get new messages
//  *  
//  * @method get_new_msgs
//  * @param {int} current_id current message id.
//  * @return {int} get_new_msgs status.
//  */
// int get_all_new_msg(int current_id, int recipient_id, char *buf, int &send_len) {
//     string respon_data;
//     Response::HTTPResponse *http_res = new Response::HTTPResponse();
//     string msg;
//     int result;
//     int ret;

//     LOG_INFO << "current_id is " << current_id << " recipient_id is " << recipient_id << endl;

//     do {
//         if (current_id <= 0 || recipient_id < 0) {
//             result = PARAM_ERROR;
//             _set_http_head(result, false, "current_id or recipient_id is not exist", http_res);
//             break; 
//         }

//         Config *c = Config::get_instance();
//         map<string, string> config = c->get_config();
//         eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), 
//             config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

//         if (!e.connet()) {
//             result = SQL_CONNECT_FAIL;
//             _set_http_head(result, false, "sql connet fail", http_res);
//         }

//         ret = e.excute("select sender_id,recipient_id,content from t_message where id>" + Tool:mysql_filter(current_id) + 
//             " and recipient_id=" + Tool:mysql_filter(recipient_id) + 
//             " and type='user';");
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
//         Data::List *message_list = new Data::List();
//         while(NULL != row) {
//             UserData::Message_Info *message_Info = message_list->add_message_Info();
//             message_Info.set_sender_id(row[0]);
//             message_Info.set_recipient_id(row[1]);
//             message_Info.set_content(row[2]);
//             row = mysql_fetch_row(mysql_result);
//         }
//         message_list->set_is_end(true);
//         e.close();

//         result = GET_ALL_NEW_MSG_SUCCESS;
//         _set_http_head(result, true, "get all new message success", http_res);
//         http_res->set_allocated_message_list_response(message_list);
//     } while(0);

//     print_proto(http_res);

//     http_res->SerializeToString(&respon_data);
//     memcpy(buf, respon_data.c_str(), respon_data.length());
//     send_len = respon_data.length();
//     google::protobuf::ShutdownProtobufLibrary();

//     return result;
// }