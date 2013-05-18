#include "room.h"

int show_user_room(map<string, string> param, char *buf, int &send_len)
{
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result = SHOW_USER_ROOM_SUCCESS;
    int ret;

    // database params
    Config *c = Config::get_instance();
    map<string, string> config = c->get_config();
    eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

    do
    {
        // param sid not exist
        if (param.count("sid") == 0)
        {
            result = PARAM_ERROR;
            http_res->set_code(PARAM_ERROR);
            msg = "param sid not exist";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        SESSION *ss = Session::get(Tool::trim(param["sid"]));
        // session is not exist
        if (ss == NULL) {
            result = SESSION_NOT_EXIST;
            http_res->set_code(SESSION_NOT_EXIST);
            msg = "session not exist";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        int room_status = Tool::S2I(param["roomStatus"]);
        int show_type = Tool::S2I(param["showType"]);
        int uid = Tool::S2I(ss->uid);
        int page_no = Tool::S2I(param["pageNo"]);
        int page_size = Tool::S2I(param["pageSize"]);

        LOG_INFO << "room_status:" << room_status << "|show_type:" << show_type << "|uid:" << uid << "|" 
        << "page_no:" << page_no << "|page_size:" << page_size << endl;

        if (room_status < 0 || show_type < 0 || uid < 0 || !(show_type == 0 || show_type == 1) || page_no < 0 || page_size < 0)
        {
            result = PARAM_ERROR;
            http_res->set_code(PARAM_ERROR);
            msg = "param error";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }
        int begin_pos = (page_no - 1) * page_size;


        string room_condition_sql;
        if (show_type == 0) {
            room_condition_sql = " (select id from t_room where owner_id = " + ss->uid + ") ";
        } else if (show_type == 1) {
            room_condition_sql = " (select room_id from t_room_user_relation where user_id = " + ss->uid + ") ";
        }
        string sql = 
        "SELECT r.id as room_id, r.title, r.owner_id, u.nickname, r.type, "
        "r.preview_pic_id, r.gender_type, (select count(1) from t_room_user_relation where room_id = r.id) as join_num, "
        "r.limit_person_num, r.record_id, r.create_time, r.begin_time, "
        "a.longitude, a.latitude, a.detail_addr, a.addr_remark "
        "FROM t_room r, t_address a, t_user u where r.id in " + room_condition_sql + 
        "and a.id = r.addr_id and r.owner_id = u.id and r.room_status = " + param["roomStatus"] + 
        " limit " + Tool::toString(begin_pos) + "," + Tool::toString(page_size);

        LOG_DEBUG << sql << endl;

        int count = 0;

        string count_condition_sql = " where r.id in " + room_condition_sql + 
        "and a.id = r.addr_id and r.owner_id = u.id and r.room_status = " + param["roomStatus"];

        ret = e.count(" t_room r, t_address a, t_user u ", count_condition_sql, count);


        // exception
        if (ret != DB_OK) {
            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            msg = "DB ERROR|count room|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            e.close();
            break;
        }
        LOG_INFO << "total user room:" << Tool::toString(count);
        MYSQL mysql;

        // connect fail
        if (!e.connet()) {
            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            msg = "DB ERROR|get user room list|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            e.close();
            break;
        }

        // get page data
        ret = e.excute(sql);

        // exception
        if (ret != DB_OK) {
            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            msg = "DB ERROR|excute sql error|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            e.close();
            break;
        }

        mysql = e.get_mysql();
        MYSQL_RES *rst = NULL;
        MYSQL_FIELD *field = NULL;
        MYSQL_ROW row = NULL;

        rst = mysql_store_result(&mysql);
        int fieldcount = mysql_num_fields(rst);
        row = mysql_fetch_row(rst);

        Data::List *room_list = new Data::List();
        int data_num = begin_pos;
        while(NULL != row) 
        {
            RoomData::RoomInfo *room_info = room_list->add_room_info();
            RoomData::Address *addr = new RoomData::Address();
            for(int i = 0; i < fieldcount; i++) 
            {
                field = mysql_fetch_field_direct(rst, i);
                string key = field->name;
                if (row[i] == NULL)
                    continue;
                if (key == "room_id") {
                    room_info->set_room_id(Tool::fromString<int>(row[i]));
                } else if (key == "title") {
                    room_info->set_title(row[i]);
                } else if (key == "owner_id") {
                    room_info->set_owner_id(Tool::fromString<int>(row[i]));
                } else if (key == "nickname") {
                    room_info->set_owner_nickname(row[i]);
                } else if (key == "type") {
                    room_info->set_type(Tool::fromString<int>(row[i]));
                } else if (key == "preview_pic_id") {
                    room_info->set_pic_id(Tool::fromString<int>(row[i]));
                } else if (key == "gender_type") {
                    room_info->set_gender_type(Tool::fromString<int>(row[i]));
                } else if (key == "join_num") {
                    room_info->set_join_person_count(Tool::fromString<int>(row[i]) + 1);
                } else if (key == "limit_person_num") {
                    room_info->set_limit_person_count(Tool::fromString<int>(row[i]));
                } else if (key == "record_id") {
                    room_info->set_record_id(Tool::fromString<int>(row[i]));
                } else if (key == "create_time") {
                    room_info->set_create_time(row[i]);
                } else if (key == "begin_time") {
                    room_info->set_begin_time(row[i]);
                } else if (key == "latitude") {
                    addr->set_latitude(Tool::fromString<double>(row[i]));
                } else if (key == "longitude") {
                    addr->set_longitude(Tool::fromString<double>(row[i]));
                } else if (key == "detail_addr") {
                    addr->set_detail_addr(row[i]);
                } else if (key == "addr_remark") {
                    addr->set_addr_remark(row[i]);
                }
            }
            row = mysql_fetch_row(rst);
            data_num++;
            room_info->set_allocated_address(addr);
        }
        if (data_num == count) {
            room_list->set_is_end(true);
        }
        http_res->set_allocated_list(room_list);



        // success
        result = SHOW_USER_ROOM_SUCCESS;
        http_res->set_code(SHOW_USER_ROOM_SUCCESS);
        http_res->set_success(true);
        msg = "show user room success";
        LOG_INFO << msg << endl;
        http_res->set_msg(msg);
        e.close();

    } while(0);
    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    memcpy(buf, respon_data.c_str(), respon_data.length());
    send_len = respon_data.length();
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}