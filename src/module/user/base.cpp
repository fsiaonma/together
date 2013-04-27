#include "user.h"

int _get_user_info(string username, UserData::User_Info *user_info) {
    MYSQL mysql;
    string sql = "select * from t_user where username = '" + username + "';";
    e.excute(sql);
    mysql = e.get_mysql();

    MYSQL_RES *result = NULL;
    MYSQL_FIELD *field = NULL;
    MYSQL_ROW row = NULL;

    result = mysql_store_result(&mysql);
    int fieldcount = mysql_num_fields(result);
    row = mysql_fetch_row(result);

    for(int i = 0; i < fieldcount; i++) {
        field = mysql_fetch_field_direct(result, i);
        cout << field->name << "\t";
        string key = field->name;
        if (key == "username") {
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
        } else if (key == "followed_num") {
            user_info->set_followed_num(Tool::S2I(row[i]));
        } else if (key == "follow_num") {
            user_info->set_follow_num(Tool::S2I(row[i]));
        }
    }

    return 0;
}