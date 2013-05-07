#include "user.h"

int get_follow_list(int uid, char *buf) {
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result;
    int ret;

    do {
        LOG_INFO << "uid is " << uid << endl;
        
        // uid
        if (uid <= 0) {
            result = PARAM_ERROR;
            _set_http_head(result, false, "uid is not found", http_res);
            break;
        }

        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));
        
        e.connet();
        e.excute("select * from t_follow where follow_id = " + Tool::mysql_filter(uid) + ";");
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

    }

    return 0;
}