#include "user.h"

/**
 * get follow list
 *  
 * @method get_following_list
 * @param {int} uid uid which is used for mark which user is to depend on
 * @param {int} page_no page_no which is used for get follow list
 * @param {int} page_size page_size which is used for get follow list
 * @param {string} sid sid which is used for mark whether login or not
 * @param {char*} respone data. 
 * @return {int} get_following_list status.
 */
int get_following_list(int uid, int page_no, int page_size, string sid, char *buf, int &send_len) {
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result;
    int ret;
    int total;

    LOG_INFO << " uid is " << uid << " page_no is " << page_no << " page_size is " << page_size << " sid is " << sid << endl;

    do {
        // page_no or page_size or sid is not be found
        if (page_no <= 0 || page_size <= 0 || Tool::trim(sid).empty()) {
            result = PARAM_ERROR;
            _set_http_head(result, false, "page_no or page_size or sid is not be found", http_res);
            break;
        }

        // session is not exist
        if (Session::get(sid) == NULL) {
            result = SESSION_NOT_EXIST;
            _set_http_head(result, false, "session not exist", http_res);
            break;
        }

        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));
        
        if (!e.connet()) {
            result = SQL_CONNECT_FAIL;
            _set_http_head(result, false, "sql connet fail", http_res);
        }

        int begin_pos = (page_no - 1) * page_size;
        ret = e.excute("select followed_id from t_follow where follow_id = " + Tool::mysql_filter(uid) + 
        " order by id desc limit " + Tool::mysql_filter(begin_pos) + "," + Tool::mysql_filter(page_size) + ";");
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
        Data::List *following_list = new Data::List();
        while(NULL != row) {
            UserResponse::DetailResponse *detailResponse = following_list->add_user_detail();
        	
            UserData::User_Info *user_info = new UserData::User_Info();
            ret = _get_user_info(Tool::S2I(row[0]), user_info);
            // exception
            if (ret != DB_OK) {
                result = DB_ERROR;
                _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
                break;
            }
            detailResponse->set_allocated_user_info(user_info);

            bool exist;
            int self_id = Tool::S2I(Session::get(sid)->uid);
            _is_follow(self_id, user_info->uid(), exist);
            detailResponse->set_is_follow(exist);

            row = mysql_fetch_row(mysql_result);
        }
        e.count("t_follow", "where follow_id = " + Tool::mysql_filter(uid) + ";", total);
        if (ret != DB_OK) {
            result = DB_ERROR;
            _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
            break;
        }

        following_list->set_is_end(begin_pos + page_size >= total);

        e.close();

        result = GET_FOLLOWING_LIST_SUCCESS;
        _set_http_head(result, true, "get follow list success", http_res);
        http_res->set_allocated_list(following_list);
    }while(0);

    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    memcpy(buf, respon_data.c_str(), respon_data.length());
    send_len = respon_data.length();
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}

/**
 * get followed list
 *  
 * @method get_followers_list
 * @param {int} uid uid which is used for mark which user is to depend on
 * @param {int} page_no page_no which is used for get followed list
 * @param {int} page_size page_size which is used for get followed list
 * @param {string} sid sid which is used for mark whether login or not
 * @param {char*} respone data. 
 * @return {int} get_followers_list status.
 */
int get_followers_list(int uid, int page_no, int page_size, string sid, char *buf, int &send_len) {
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result;
    int ret;
    int total;

    LOG_INFO << " uid is " << uid << " page_no is " << page_no << " page_size is " << page_size << " sid is " << sid << endl;

    do {
        // page_no or page_size or sid is not be found
        if (page_no <= 0 || page_size <= 0 || Tool::trim(sid).empty()) {
            result = PARAM_ERROR;
            _set_http_head(result, false, "page_no or page_size or sid is not be found", http_res);
            break;
        }

        // session is not exist
        if (Session::get(sid) == NULL) {
            result = SESSION_NOT_EXIST;
            _set_http_head(result, false, "session not exist", http_res);
            break;
        }

        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));
        
        if (!e.connet()) {
            result = SQL_CONNECT_FAIL;
            _set_http_head(result, false, "sql connet fail", http_res);
        }

        int begin_pos = (page_no - 1) * page_size;
        ret = e.excute("select follow_id from t_follow where followed_id = " + Tool::mysql_filter(uid) + 
        " order by id desc limit " + Tool::mysql_filter(begin_pos) + "," + Tool::mysql_filter(page_size) + ";");
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

        // followed_list construtor
        Data::List *followers_list = new Data::List();
        while(NULL != row) {
            UserResponse::DetailResponse *detailResponse = followers_list->add_user_detail();
            
            UserData::User_Info *user_info = new UserData::User_Info();
            ret = _get_user_info(Tool::S2I(row[0]), user_info);
            // exception
            if (ret != DB_OK) {
                result = DB_ERROR;
                _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
                break;
            }
            detailResponse->set_allocated_user_info(user_info);

            bool exist;
            int self_id = Tool::S2I(Session::get(sid)->uid);
            _is_follow(self_id, user_info->uid(), exist);
            detailResponse->set_is_follow(exist);
            
            row = mysql_fetch_row(mysql_result);
        }
        e.count("t_follow", "where followed_id = " + Tool::mysql_filter(uid) + ";", total);
        if (ret != DB_OK) {
            result = DB_ERROR;
            _set_http_head(result, false, "DB ERROR|" + Tool::toString(ret), http_res);
            break;
        }


        followers_list->set_is_end(true);
        cout << "~~~~~~~~" << followers_list->is_end() << endl;
        // followers_list->set_is_end(1);
        e.close();

        result = GET_FOLLOWERS_LIST_SUCCESS;
        _set_http_head(result, true, "get followed list success", http_res);
        http_res->set_allocated_list(followers_list);
    }while(0);

    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    memcpy(buf, respon_data.c_str(), respon_data.length());
    send_len = respon_data.length();
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}