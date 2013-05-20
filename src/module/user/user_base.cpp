#include "./user_base.h"

/**
 * get user info
 *  
 * @method _get_user_info (private)
 * @param {int} uid uid which is used for getting user info.
 * @param {UserData::User_Info*} user_info respone data.
 * @return {int} _get_user_info status. 
 */
int _get_user_info(int uid, UserData::User_Info *user_info) {
    int count;
    int ret = 0;
    MYSQL mysql;

    do {
        // database params
        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

        if (!e.connet()) {
            ret = SQL_CONNECT_FAIL;
        }

        ret = e.excute("select * from t_user where id=" + Tool::mysql_filter(uid) + ";");
        if (ret != DB_OK) { break; }

        mysql = e.get_mysql();
        MYSQL_RES *result = NULL;
        MYSQL_FIELD *field = NULL;
        MYSQL_ROW row = NULL;

        result = mysql_store_result(&mysql);

        int rowcount = mysql_num_rows(result);
        if (rowcount == 0) {
            ret = DB_NO_DATA;
            break;
        }

        int fieldcount = mysql_num_fields(result);
        row = mysql_fetch_row(result);

        for(int i = 0; i < fieldcount; i++) {
            field = mysql_fetch_field_direct(result, i);
            string key = field->name;

            if (row[i] == NULL) {
                continue;
            }

            if (key == "id") {
                user_info->set_uid(uid);
            } else if (key == "username") {
                user_info->set_username(row[i]);
            } else if (key == "nickname") {
                user_info->set_nick_name(row[i]);
            } else if (key == "birthday") {
                user_info->set_birthday(row[i]);
            } else if (key == "signature_text") {
                user_info->set_signature_text(row[i]);
            } else if (key == "signature_record_id") {
                user_info->set_signature_record_id(Tool::S2I(row[i]));
            } else if (key == "praise_num") {
                user_info->set_praise_num(Tool::S2I(row[i]));
            } else if (key == "visit_num") {
                user_info->set_visit_num(Tool::S2I(row[i]));
            } else if (key == "pic_id") {
                user_info->set_pic_id(Tool::S2I(row[i]));
            } else if (key == "sex") {
                user_info->set_sex(Tool::S2I(row[i]));
            }
        }

        e.close();

        e.count("t_follow", "where follow_id = " + Tool::mysql_filter(uid) + ";", count);
        if (ret != DB_OK) { break; }
        user_info->set_follow_num(count);
        
        e.count("t_follow", "where followed_id = " + Tool::mysql_filter(uid) + ";", count);
        if (ret != DB_OK) { break; }
        user_info->set_followed_num(count);  
    } while (0);
    
    // print_proto(user_info);

    return ret;
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

/**
 * get uid by username
 *  
 * @method _get_uid (private)
 * @param {string} username username which is used for getting user id.
 * @param {int} uid uid which is getting for.
 * @return {int} _get_uid status. 
 */
int _get_uid(string username, int &uid) {
    MYSQL mysql;
    Config *c = Config::get_instance();
    map<string, string> config = c->get_config();
    eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

    e.connet();

    e.excute("select id from t_user where username = '" + username + "';");
    
    mysql = e.get_mysql();
    MYSQL_RES *result = NULL;
    MYSQL_ROW row = NULL;

    result = mysql_store_result(&mysql);

    row = mysql_fetch_row(result);
    uid = Tool::S2I(row[0]);

    e.close();
    
    return 1;
}

int _is_follow(int following_id, int follower_id, bool &exist) {
    Config *c = Config::get_instance();
    map<string, string> config = c->get_config();
    eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));
    e.is_exist("t_follow", 
        "where follow_id = " + Tool::mysql_filter(following_id) + " and followed_id = " + Tool::mysql_filter(follower_id) + ";", 
        exist);
    return 1;
}
