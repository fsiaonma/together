#include "message.h"

/**
 * get follow up message
 *  
 * @method get_follow_up_msg
 * @param {int} current_id current message id
 * @param {int} recipient_id recipient_id which is used for marking the recipient.
 * @param {int} tid tid which is used for marking the type id.
 * @param {int} type request type: room or user.
 * @param {string} content content message content. 
 * @return {int} get_follow_up_msg status.
 */
int get_follow_up_msg(int current_id, int recipient_id, int tid, int type, char *buf, int &send_len) {
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result;
    int ret;

    LOG_INFO << "current_id is " << current_id << " recipient_id is " << recipient_id 
    		 << " tid is " << tid << " type is " << type << endl;

    do {
        if (current_id <= 0 || recipient_id <= 0 || tid <= 0 || type < 0) {
            result = PARAM_ERROR;
            _set_http_head(result, false, "current_id or recipient_id or tid or type is not exist", http_res);
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

        string sql = "", type_id = "";

        if (type == USER_MODULE) {
        	type_id = "sender_id";
        } else if (type == ROOM_MODULE) {
        	type_id = "room_id";
        }

        sql = "select id,sender_id,recipient_id from t_msg where id>" + Tool::mysql_filter(current_id) 
        	+ " and recipient_id=" + Tool::mysql_filter(recipient_id) 
        	+ " and " + type_id + "=" + Tool::mysql_filter(tid) 
        	+ " and type=" + Tool::mysql_filter(type) + ";";

        LOG_INFO << "sql is: " << sql << endl;

        ret = e.excute(sql);
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
        
            row = mysql_fetch_row(mysql_result);
        }

        message_list->set_is_end(true);
        e.close();
      
        result = GET_FOLLOW_UP_MSG_SUCCESS;
        _set_http_head(result, true, "get follow up message success", http_res);
        http_res->set_allocated_list(message_list);
    } while(0);

    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    memcpy(buf, respon_data.c_str(), respon_data.length());
    send_len = respon_data.length();
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}

/**
 * get previous message
 *  
 * @method get_previous_msg
 * @param {int} current_id current message id
 * @param {int} msgs_num the number of messages wanna get.
 * @param {int} recipient_id recipient_id which is used for marking the recipient.
 * @param {int} tid tid which is used for marking the type id.
 * @param {int} type request type: room or user.
 * @param {string} content content message content. 
 * @return {int} get_previous_msg status.
 */
int get_previous_msg(int current_id, int msgs_num, int recipient_id, int tid, int type, char *buf, int &send_len) {
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result;
    int ret;

    LOG_INFO << "current_id is " << current_id << " msgs_num is " << msgs_num 
    		 << " recipient_id is " << recipient_id << "tid is " << tid 
    		 << "type is " << type << endl;

    do {
        if (current_id <= 0 || msgs_num <= 0 || recipient_id <= 0 || tid <= 0 || type < 0) {
            result = PARAM_ERROR;
            _set_http_head(result, false, "current_id or msgs_num or recipient_id or tid or type is not exist", http_res);
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

        string sql = "", type_id = "";

        if (type == USER_MODULE) {
        	type_id = "sender_id";
        } else if (type == ROOM_MODULE) {
        	type_id = "room_id";
        }

        sql = "select id,sender_id,recipient_id from t_msg where id<=" + Tool::mysql_filter(current_id) 
        	+ " and recipient_id = " + Tool::mysql_filter(recipient_id) 
            + " and " + type_id + "=" + Tool::mysql_filter(tid) 
            + " and type=" + Tool::mysql_filter(type) + " order by id desc limit " + Tool::mysql_filter(msgs_num) + ";";

        LOG_INFO << "sql is: " << sql << endl;

        ret = e.excute(sql);
        if (ret != DB_OK) {
            result = DB_ERROR;
            _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
            break;
        }

        MYSQL mysql;
        mysql = e.get_mysql();

        MYSQL_RES *mysql_result = NULL;
        MYSQL_ROW row = NULL;
        int rowcount = 0;

        mysql_result = mysql_store_result(&mysql);
        row = mysql_fetch_row(mysql_result);
        rowcount = mysql_num_rows(mysql_result);

        LOG_INFO << "rowcount is " << rowcount << endl;

        // follow_list construtor
        Data::List *message_list = new Data::List();
        while(NULL != row) {
            int message_id = Tool::S2I(row[0]);
            int sender_id = Tool::S2I(row[1]);
            int recipient_id = Tool::S2I(row[2]);

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

            row = mysql_fetch_row(mysql_result);
        }
		message_list->set_is_end(rowcount < msgs_num);
        
        e.close();

        result = GET_PREVIOUS_MSG_SUCCESS;
        _set_http_head(result, true, "get previous message success", http_res);
        http_res->set_allocated_list(message_list);
    } while(0);

    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    memcpy(buf, respon_data.c_str(), respon_data.length());
    send_len = respon_data.length();
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}