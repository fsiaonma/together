#include "./user_base.h"

/**
 * get user info
 *  
 * @method _get_user_info (private)
 * @param {string} username username which is used for getting user info.
 * @param {UserData::User_Info*} user_info respone data.
 * @return {int} _get_user_info status. 
 */
int _get_user_info(string username, UserData::User_Info *user_info) {
    int uid;
    int count;
    MYSQL mysql;

    // database params
    Config *c = Config::get_instance();
    map<string, string> config = c->get_config();
    eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

    e.connet();
    e.excute("select * from t_user where username = '" + username + "';");
    mysql = e.get_mysql();

    MYSQL_RES *result = NULL;
    MYSQL_FIELD *field = NULL;
    MYSQL_ROW row = NULL;

    result = mysql_store_result(&mysql);
    int fieldcount = mysql_num_fields(result);
    row = mysql_fetch_row(result);

    for(int i = 0; i < fieldcount; i++) {
        field = mysql_fetch_field_direct(result, i);
        LOG_INFO << field->name << endl;
        string key = field->name;

        if (row[i] == NULL) {
            continue;
        }
        
        if (key == "id") {
            uid = Tool::S2I(row[i]);
            user_info->set_uid(uid);
        } else if (key == "username") {
            user_info->set_username(row[i]);
        } else if (key == "nick_name") {
            user_info->set_nick_name(row[i]);
        } else if (key == "birthday") {
            user_info->set_birthday(Tool::S2I(row[i]));
        } else if (key == "signature_text") {
            user_info->set_signature_text(row[i]);
        } else if (key == "signature_record_id") {
            user_info->set_signature_record_id(Tool::S2I(row[i]));
        } else if (key == "praise_num") {
            user_info->set_praise_num(Tool::S2I(row[i]));
        } else if (key == "visit_num") {
            user_info->set_visit_num(Tool::S2I(row[i]));
        }
    }

    e.close();

    e.count("t_follow", "where follow_id = " + Tool::mysql_filter(uid) + ";", count);
    user_info->set_follow_num(count);

    e.count("t_follow", "where followed_id = " + Tool::mysql_filter(uid) + ";", count);
    user_info->set_followed_num(count);

    print_proto(user_info);

    return 0;
}

/**
 * set http head
 *  
 * @method _set_http_head (private)
 * @param {int} code code which is used for setting http head.
 * @param {bool} success success which is used for setting http head.
 * @param {string} msg msg which is used for setting http head.
 * @param {Response::HTTPResponse*} http_res respone data.
 * @return {int} _set_http_head status. 
 */
int _set_http_head(int code, bool success, string msg, Response::HTTPResponse *http_res) {
    http_res->set_code(code);
    http_res->set_success(success);
    http_res->set_msg(msg);
    return 0;
}