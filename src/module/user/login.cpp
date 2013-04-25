#include "user.h"

/**
 * user login
 *  
 * @method login
 * @param {string} username username which is used for login.
 * @param {string} password password which is used for login.
 * @param {char*} respone data. 
 * @return {int} login status.
 */
int login(string username, string password, string dev_id, char *buf) {
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result;
    int ret;

    do {
        LOG_INFO << "login params: username is " << username << " password is " << password << "dev_id is " << dev_id << endl;
        
        // username or password not be found
        if (Tool::trim(username).empty() || Tool::trim(password).empty() || Tool::trim(dev_id).empty()) {
            result = PARAM_ERROR;
            http_res->set_code(PARAM_ERROR);
            http_res->set_success(0);
            msg = "username or password or dev_id is null";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        // database params
        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));
        bool exist;

        // check whether username and password match is database or not 
        ret = e.is_exist("t_user", "where username = '" + username + "' and password = '" + password + "'", exist);
        // exception
        if (ret != DB_OK) {
            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            http_res->set_success(0);
            msg = "DB ERROR|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }
        // user not exist
        if (!exist) {
            result = USER_NOT_EXIST;
            http_res->set_code(USER_NOT_EXIST);
            http_res->set_success(0);
            msg = "user not exist";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        // set session
        string sid;
        ret = Session::set(username, dev_id, sid);
        LOG_INFO << "sid is: " << sid << endl;
        if (ret == LOGIN_REPLACE) {
            result = LOGIN_REPLACE;
            http_res->set_code(LOGIN_REPLACE);
            msg = "login success and replace session";
        } else {
            result = REGIEST_SUCCESS;
            http_res->set_code(LOGIN_SUCCESS);
            msg = "login success";
        }

        // set HTTPResponse
        http_res->set_success(1);
        LOG_INFO << msg << endl;
        http_res->set_msg(msg);


    #if 0
        UserData::User_Info *de = new UserData::User_Info();

        MYSQL mysql;
        string sql = "select * from t_user where username = '" + username + "';";
        e.excute(sql);
        mysql = e.get_mysql();

        MYSQL_RES *result = NULL;
        MYSQL_FIELD *field = NULL;
        MYSQL_ROW row = NULL;

        result = mysql_store_result(&mysql);
        cout << "result: " << result << endl;

        int fieldcount = mysql_num_fields(result);
        cout << "fieldcount " << fieldcount << endl;

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

        UserResponse::LoginResponse *login_res = new UserResponse::LoginResponse();
        login_res->set_allocated_user_info(user_info);
        login_res->set_sid(sid);

        http_res->set_allocated_login_response(login_res);
    #endif
    } while(0);
	
    http_res->SerializeToString(&respon_data);
    const char *p = respon_data.c_str();
    strncpy(buf, p, strlen(p) + 1);
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}

/**
 * user logout
 *  
 * @method logout
 * @param {string} username username which is used for logout.
 * @param {string} sid sid which is used for logout.
 * @param {char*} buf respone data.
 * @return {int} louout status. 
 */
int logout(string username, string sid, char *buf) {
    string respon_data;
    int result;
    string msg;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();

    LOG_INFO << "username is " << username << " sid is " << sid << endl;

    do {    
        // username or password is not be found
        if (Tool::trim(username).empty() || Tool::trim(sid).empty()) {
            result = PARAM_ERROR;
            http_res->set_code(PARAM_ERROR);
            http_res->set_success(0);
            msg = "username or sid is null";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        // session is not exist
        if (Session::get(sid) == NULL) {
            result = SESSION_NOT_EXIST;
            http_res->set_code(SESSION_NOT_EXIST);
            http_res->set_success(0);
            msg = "session not exist";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        // remove session
        Session::remove(username);
        result = SESSION_OK;
        http_res->set_code(SESSION_OK);
        http_res->set_success(1);
        msg = "remove session success";
        LOG_INFO << msg << endl;
        http_res->set_msg(msg);
    } while(0);

    http_res->SerializeToString(&respon_data);
    const char *p = respon_data.c_str();
    strncpy(buf, p, strlen(p) + 1);
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}