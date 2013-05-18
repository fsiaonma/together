#include "user.h"
#include "../message/message_base.h"

/*
 * judge whether there is exist new message or not
 *  
 * @method exist_new_msg
 * @param {int} current_id current message id.
 * @return {int} exist_new_msg status.
 */
int exist_new_msg(int current_id, int recipient_id, char *buf, int &send_len) {
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result;
    int ret;

    LOG_INFO << "current_id is " << current_id << " recipient_id is " << recipient_id << endl;

    do {
        if (current_id <= 0 || recipient_id < 0) {
            result = PARAM_ERROR;
            _set_http_head(result, false, "current_id or recipient_id is not exist", http_res);
            break;
        }

        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), 
            config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

        bool exist;
        ret = e.is_exist("t_msg", "where id>" + Tool::mysql_filter(current_id) + " and recipient_id=" 
            + Tool::mysql_filter(recipient_id) + " and type=" + Tool::mysql_filter(USER_MODULE), exist);
        if (ret != DB_OK) {
            result = DB_ERROR;
            _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
            break;
        }
        UserResponse::IsExistNewMessageResponse *msg_exist_response = new UserResponse::IsExistNewMessageResponse();
        msg_exist_response->set_is_exist(exist);

        result = CHECK_EXIST_NEW_MSG_SUCCESS;
        _set_http_head(result, true, "check whether is exist new message success", http_res);
        http_res->set_allocated_exist_new_message_response(msg_exist_response);
    } while(0);

    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    memcpy(buf, respon_data.c_str(), respon_data.length());
    send_len = respon_data.length();
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}

/*
 * get new messages
 *  
 * @method get_new_msgs
 * @param {int} current_id current message id.
 * @return {int} get_new_msgs status.
 */
int get_all_new_msg(int current_id, int recipient_id, char *buf, int &send_len) {
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result;
    int ret;

    LOG_INFO << "current_id is " << current_id << " recipient_id is " << recipient_id << endl;

    do {
        if (current_id <= 0 || recipient_id < 0) {
            result = PARAM_ERROR;
            _set_http_head(result, false, "current_id or recipient_id is not exist", http_res);
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

        ret = e.excute("select id,sender_id,recipient_id from t_msg where id>" + Tool::mysql_filter(current_id) 
            + " and recipient_id=" + Tool::mysql_filter(recipient_id) 
            + " and type=" + Tool::mysql_filter(USER_MODULE) + ";");
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
            int follow_count = 0;
            int message_id = Tool::S2I(row[0]);
            int sender_id = Tool::S2I(row[1]);
            int recipient_id = Tool::S2I(row[2]);

            e.count("t_msg", "where id>=" + Tool::mysql_filter(message_id) 
            + " and recipient_id=" + Tool::mysql_filter(recipient_id) 
            + " and sender_id=" + Tool::mysql_filter(sender_id)
            + " and type=" + Tool::mysql_filter(USER_MODULE) + ";", follow_count);

            cout << "follow_count is " << follow_count << endl;

            if (follow_count == 1) {
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

                int count = 0;
                e.count("t_msg", "where id>=" + Tool::mysql_filter(current_id) 
                + " and recipient_id=" + Tool::mysql_filter(recipient_id) 
                + " and sender_id=" + Tool::mysql_filter(sender_id)
                + " and type=" + Tool::mysql_filter(USER_MODULE) + ";", count);            
                user_message_info->set_message_count(count);
            }

            row = mysql_fetch_row(mysql_result);
        }
        message_list->set_is_end(true);

        e.close();

        result = GET_ALL_NEW_MSG_SUCCESS;
        _set_http_head(result, true, "get all new message success", http_res);
        http_res->set_allocated_list(message_list);
    } while(0);

    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    memcpy(buf, respon_data.c_str(), respon_data.length());
    send_len = respon_data.length();
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}