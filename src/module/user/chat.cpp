#include "user.h"
#include "../message/message_base.h"

/**
 * get follow up msg
 *  
 * @method get_follow_up_msg
 * @param {int} current_id current message id
 * @param {int} sender_id sender_id which is used for marking the sender.
 * @param {int} recipient_id recipient_id which is used for marking the recipient.
 * @param {string} content content message content. 
 * @return {int} get_follow_up_msg status.
 */
int get_follow_up_msg(int current_id, int sender_id, int recipient_id, char *buf, int &send_len) {
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result;
    int ret;

    LOG_INFO << "current_id is " << current_id << " sender_id is " << sender_id << " recipient_id is " << recipient_id << endl;

    do {
        if (current_id <= 0 || sender_id <= 0 || recipient_id <= 0) {
            result = PARAM_ERROR;
            _set_http_head(result, false, "current_id or sender_id or recipient_id is not exist", http_res);
            break; 
        }

        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), 
            config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

        if (!e.connet()) {
            result = SQL_CONNECT_FAIL;
            _set_http_head(result, false, "sql connet fail", http_res);
        }

        ret = e.excute("select id,sender_id,recipient_id from t_message where id>" + 
            Tool::mysql_filter(current_id) + " and sender_id=" + 
            Tool::mysql_filter(sender_id) + " and recipient_id=" + 
            Tool::mysql_filter(recipient_id) + " and type=" + Tool::mysql_filter(USER_MODULE) + ";");

        cout << "select id,sender_id,recipient_id from t_message where id>" + 
            Tool::mysql_filter(current_id) + " and sender_id = " + 
            Tool::mysql_filter(sender_id) + " and recipient_id=" + 
            Tool::mysql_filter(recipient_id) + " and type='user';" << endl;

        if (ret != DB_OK) {
            result = DB_ERROR;
            _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
            break;
        }

        MYSQL mysql;
        mysql = e.get_mysql();

        MYSQL_RES *mysql_result = NULL;
        MYSQL_ROW row = NULL;

        mysql_result = mysql_store_result(&mysql);
        row = mysql_fetch_row(mysql_result);

        // follow_list construtor
        Data::List *message_list = new Data::List();
        while(NULL != row) {
            int message_id = Tool::S2I(row[0]);
            int sender_id = Tool::S2I(row[1]);
            int recipient_id = Tool::S2I(row[2]);
            int count = 0;

            UserResponse::UserMessageResponse *user_message_info = message_list->add_user_message_info();
        
            MessageData::Message_Info *message_info = new MessageData::Message_Info();
             _get_message_info(message_id, message_info);
             user_message_info->set_allocated_message_info(message_info);

            UserData::User_Info *sender_info = new UserData::User_Info();
            _get_user_info(sender_id, sender_info);
            user_message_info->set_allocated_sender(sender_info);
            
            UserData::User_Info *recipient_info = new UserData::User_Info();
            _get_user_info(recipient_id, recipient_info);
            user_message_info->set_allocated_recipient(recipient_info);

            e.count("t_message", "where id>=" + Tool::mysql_filter(current_id) + 
                " and sender_id = " + Tool::mysql_filter(sender_id) + 
                " and recipient_id=" + Tool::mysql_filter(recipient_id) + 
                " and type=" + Tool::mysql_filter(USER_MODULE) + ";", count);
            user_message_info->set_message_count(count);
        
            row = mysql_fetch_row(mysql_result);
        }

        message_list->set_is_end(true);
        e.close();
      
        result = GET_FOLLOW_UP_MSG_SUCCESS;
        _set_http_head(result, true, "get follow up message success", http_res);
        http_res->set_allocated_user_message_list_response(message_list);
    } while(0);

    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    memcpy(buf, respon_data.c_str(), respon_data.length());
    send_len = respon_data.length();
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}

// /*
//  * get previous msg
//  *  
//  * @method get_previous_msg
//  * @param {int} current_id current message id.
//  * @param {int} msgs_num msgs_num number of messages the client want to get.
//  * @param {int} sender_id sender_id which is used for marking the sender.
//  * @param {int} recipient_id recipient_id which is used for marking the recipient.
//  * @param {string} content content message content. 
//  * @return {int} get_previous_msg status.
//  */
// int get_previous_msg(int current_id, int msgs_num, int sender_id, int recipient_id, char *buf, int &send_len) {
//     string respon_data;
//     Response::HTTPResponse *http_res = new Response::HTTPResponse();
//     string msg;
//     int result;
//     int ret;

//     LOG_INFO << "current_id is " << current_id << " msgs_num is " << msgs_num << " sender_id is " << sender_id << "recipient_id is " << recipient_id << endl;

//     do {
//         if (current_id <= 0 || msgs_num < 0 || sender_id <= 0 || recipient_id <= 0) {
//             result = PARAM_ERROR;
//             _set_http_head(result, false, "current_id or msgs_num or sender_id or recipient_id is not exist", http_res);
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

//         ret = e.excute("select sender_id,recipient_id,content from t_message where id<=" + Tool:mysql_filter(current_id) + 
//             " and sender_id = " + Tool:mysql_filter(sender_id) + " and recipient_id=" + Tool:mysql_filter(recipient_id) + 
//             " and type='user' order by id desc limit " + msgs_num + ";");
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

//         result = GET_PREVIOUS_MSG_SUCCESS;
//         _set_http_head(result, true, "get previous message success", http_res);
//         http_res->set_allocated_message_list_response(message_list);
//     } while(0);

//     print_proto(http_res);

//     http_res->SerializeToString(&respon_data);
//     memcpy(buf, respon_data.c_str(), respon_data.length());
//     send_len = respon_data.length();
//     google::protobuf::ShutdownProtobufLibrary();

//     return result;
// }

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