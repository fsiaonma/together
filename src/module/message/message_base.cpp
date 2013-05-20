#include "message_base.h"
#include "message_sock.h"

/**
 * get message info by message's id
 *  
 * @method _get_message_info (private)
 * @param {int} message_id message_id which is used for getting message info.
 * @param {MessageData::message_info*} message_info respone data.
 * @return {int} _get_message_info status. 
 */
int _get_message_info(int message_id, MessageData::Message_Info *message_info) {
    MYSQL mysql;

    // database params
    Config *c = Config::get_instance();
    map<string, string> config = c->get_config();
    eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

    e.connet();
    
    e.excute("select * from t_msg where id = " + Tool::mysql_filter(message_id) + ";");
    mysql = e.get_mysql();

    MYSQL_RES *result = NULL;
    MYSQL_FIELD *field = NULL;
    MYSQL_ROW row = NULL;

    result = mysql_store_result(&mysql);
    int fieldcount = mysql_num_fields(result);
    row = mysql_fetch_row(result);

    for(int i = 0; i < fieldcount; i++) {
        field = mysql_fetch_field_direct(result, i);
        string key = field->name;

        if (row[i] == NULL) {
            continue;
        }

        if (key == "id") {
            message_info->set_message_id(message_id);
        } else if (key == "sender_id") {
            message_info->set_sender_id(Tool::S2I(row[i]));
        } else if (key == "recipient_id") {
            message_info->set_recipient_id(Tool::S2I(row[i]));
        } else if (key == "type") {
            message_info->set_type(Tool::S2I(row[i]));
        } else if (key == "content") {
            message_info->set_content(row[i]);
        } else if (key == "title") {
            message_info->set_title(row[i]);
        } else if (key == "file_id") {
            message_info->set_file_id(Tool::S2I(row[i]));
        } else if (key == "room_id") {
            message_info->set_room_id(Tool::S2I(row[i]));
        } else if (key == "time") {
        	message_info->set_time(row[i]);
        } else if (key == "status") {
            message_info->set_status(row[i]);
        }
    }

    e.close();

    print_proto(message_info);

    return 0;
}

int _bind_user_chat(int sock, map<string, string> param, list<int> &send_sock_list, char *buf)
{
    char c_rst[10];
    int result = BIND_USER_CHAT_SUCCESS;
    send_sock_list.push_back(sock);
    do
    {
        if (param.count("userId") == 0)
        {
            result = PARAM_ERROR;
            break;
        }

        int user_id = Tool::S2I(param["userId"]);
        if (user_id < 0)
        {
            result = PARAM_ERROR;
            break;
        }

        // database params
        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

        bool exist = false;
        result = e.is_exist("t_user", "where id = " + Tool::mysql_filter(user_id) + ";", exist);

        if (result != DB_OK)
        {
            result = DB_ERROR;
            break;
        }
        LOG_DEBUG << "user exist|" << exist << endl;
        if (!exist)
        {
            result = BIND_USER_CHAT_USER_NOTEXIST;
            break;
        }
        result = BIND_USER_CHAT_SUCCESS;
        insert_sock(user_id, sock);
    } while(0);
    sprintf(c_rst, "%d", result);
    strncpy(buf, c_rst, strlen(c_rst) + 1);
    return result;
}