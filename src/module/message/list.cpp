#include "message.h"

/**
 * get messages
 *  
 * @method get_msgs
 * @param {int} current_id current message id
 * @param {int} msgs_num the number of messages wanna get.
 * @param {int} recipient_id recipient_id which is used for marking the recipient.
 * @param {int} room_id room_id the id of room.
 * @param {int} type request type: room or user.
 * @param {int} get_type get type, get previous or 
 * @param {string} content content message content. 
 * @return {int} get_msgs status.
 */
int get_msgs(map<string, string> param, char *buf, int &send_len) {
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result;
    int ret;

    int current_id = Tool::S2I(param["current_id"]);
    int msgs_num = Tool::S2I(param["msgs_num"]);
    int recipient_id = Tool::S2I(param["recipient_id"]);
    int room_id = Tool::S2I(param["room_id"]);
    int type = Tool::S2I(param["type"]);
    int get_type = Tool::S2I(param["get_type"]);

    LOG_INFO << "current_id is " << current_id << " msgs_num is " << msgs_num 
             << " recipient_id is " << recipient_id << " room_id is " << room_id 
             << " type is " << type << " get_type is " << get_type << endl;

    do {
        if (current_id < 0 || msgs_num <= 0 || recipient_id <= 0 || room_id <= 0 || type < 0 || get_type < -1) {
            result = PARAM_ERROR;
            _set_http_head(result, false, "current_id or msgs_num or recipient_id or room_id or type or get_type is not exist", http_res);
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

        string sql = "";

        if (get_type == GET_LATEST) {
            sql = "select id,sender_id,recipient_id from t_msg where recipient_id = " + Tool::mysql_filter(recipient_id) 
                + " and room_id=" + Tool::mysql_filter(room_id) 
                + " and type=" + Tool::mysql_filter(type) 
                + " order by id desc limit " + Tool::mysql_filter(msgs_num) + ";";
        } else if (get_type == GET_FOLLOW) {
            sql = "select id,sender_id,recipient_id from t_msg where id>" + Tool::mysql_filter(current_id) 
                + " and recipient_id = " + Tool::mysql_filter(recipient_id) 
                + " and room_id=" + Tool::mysql_filter(room_id) 
                + " and type=" + Tool::mysql_filter(type) 
                + " order by id asc;";
        } else if (get_type == GET_PREVIOUS) {
            sql = "select id,sender_id,recipient_id from t_msg where id<" + Tool::mysql_filter(current_id) 
                + " and recipient_id = " + Tool::mysql_filter(recipient_id) 
                + " and room_id=" + Tool::mysql_filter(room_id) 
                + " and type=" + Tool::mysql_filter(type) 
                + " order by id desc limit " + Tool::mysql_filter(msgs_num) + ";";
        }

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

        Data::List *message_list = new Data::List();
        LOG_INFO << "------------ show msg ------------" << endl;
        while(NULL != row) {
            int message_id = Tool::S2I(row[0]);
            int sender_id = Tool::S2I(row[1]);
            int recipient_id = Tool::S2I(row[2]);

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

            LOG_INFO << "sender_id:" << sender_id << "|" << "content:" << message_info->content() << endl;

            row = mysql_fetch_row(mysql_result);
        }
        LOG_INFO << "------------ show msg end ------------" << endl;
        message_list->set_is_end(rowcount < msgs_num);
        
        e.close();

        result = GET_MSG_SUCCESS;
        _set_http_head(result, true, "get messages success", http_res);
        http_res->set_allocated_list(message_list);
    } while(0);

    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    memcpy(buf, respon_data.c_str(), respon_data.length());
    send_len = respon_data.length();
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}