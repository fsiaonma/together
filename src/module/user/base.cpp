#include "user.h"

int _get_user_info(string username, UserData::User_Info *user_info) {
    int uid;
    int count;
    MYSQL mysql;
    
    // database params
    Config *c = Config::get_instance();
    map<string, string> config = c->get_config();
    eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

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
        LOG_DEBUG << field->name << "\t";
        string key = field->name;
        if (key == "id") {
            uid = row[i];
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

    e.count("t_follow", "where follow_id = '" + uid + "';", count);
    user_info->set_follow_num(count);

    e.count("t_follow", "where followed_id = '" + uid + "';", count);
    user_info->set_followed_num(count);

    return 0;
}

int _set_http_head(int code, bool success, string msg, string &result, Response::HTTPResponse *http_res) {
    http_res->set_code(code);
    http_res->set_success(success);
    http_res->set_msg(msg);
    return 0;
}