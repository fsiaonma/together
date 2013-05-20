#include "user.h"
#include "../message/message_base.h"

/*
 * get new messages
 *  
 * @method get_new_msgs
 * @param {int} current_id current message id.
 * @return {int} get_new_msgs status.
 */
int get_msg_list(int recipient_id, char *buf, int &send_len) {
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result;
    int ret;

    LOG_INFO << " recipient_id is " << recipient_id << endl;

    do {
        if (recipient_id < 0) {
            result = PARAM_ERROR;
            _set_http_head(result, false, "recipient_id is not exist", http_res);
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

        ret = e.excute("select id,sender_id,recipient_id from t_msg where recipient_id=" + Tool::mysql_filter(recipient_id) 
            + " and sender_id<>" + Tool::mysql_filter(recipient_id)
            + " and status=" + Tool::mysql_filter(MSG_NOT_READ)
            + " and type=" + Tool::mysql_filter(PRIVATE_CHAT) + ";");

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
            + " and status=" + Tool::mysql_filter(MSG_NOT_READ)
            + " and type=" + Tool::mysql_filter(PRIVATE_CHAT) + ";", follow_count);

            cout << "follow_count is " << follow_count << endl;

            if (follow_count == 1) {
                UserResponse::UserMessageResponse *user_message_info = message_list->add_user_message_info();
            
                MessageData::Message_Info *message_info = new MessageData::Message_Info();
                 _get_message_info(message_id, message_info);
                 user_message_info->set_allocated_message_info(message_info);

                UserData::User_Info *sender_info = new UserData::User_Info();
                ret = _get_user_info(sender_id, sender_info);
                // exception
                if (ret != DB_OK) {
                    result = DB_ERROR;
                    _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
                    break;
                }
                user_message_info->set_allocated_sender(sender_info);
                
                UserData::User_Info *recipient_info = new UserData::User_Info();
                ret = _get_user_info(recipient_id, recipient_info);
                // exception
                if (ret != DB_OK) {
                    result = DB_ERROR;
                    _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
                    break;
                }
                user_message_info->set_allocated_recipient(recipient_info);

                int count = 0;
                e.count("t_msg", "where recipient_id=" + Tool::mysql_filter(recipient_id)
                + " and sender_id=" + Tool::mysql_filter(sender_id)
                + " and status=" + Tool::mysql_filter(MSG_NOT_READ)
                + " and type=" + Tool::mysql_filter(PRIVATE_CHAT) + ";", count);            
                user_message_info->set_message_count(count);
            }

            row = mysql_fetch_row(mysql_result);
        }
        message_list->set_is_end(true);

        e.close();

        result = GET_MSG_LIST_SUCCESS;
        _set_http_head(result, true, "get message list success", http_res);
        http_res->set_allocated_list(message_list);
    } while(0);

    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    memcpy(buf, respon_data.c_str(), respon_data.length());
    send_len = respon_data.length();
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}