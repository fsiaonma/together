#include "room.h"

int show_room_list(map<string, string> param, char *buf, int &send_len)
{
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result = SHOW_ROOM_LIST_SUCCESS;
    int ret;

    do
    {
        string sql_condition = "";
        // essential
        string room_type = Tool::trim(param["roomType"]);
        string lng = Tool::trim(param["longitude"]);
        string lat = Tool::trim(param["latitude"]);
        int page_no = Tool::S2I(param["pageNo"]);
        int page_size = Tool::S2I(param["pageSize"]);
        string dist = param["range"]; // km

        if (room_type.empty() || !Tool::isNum(lng) || !Tool::isNum(lat) || page_no < 0 || page_size < 0 || !Tool::isNum(param["range"]))
        {
            result = PARAM_ERROR;
            http_res->set_code(PARAM_ERROR);
            msg = "param error";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        LOG_INFO << "room_type:" << room_type << "|" << "longitude:" << lng << "|" << 
        "latitude:" << lat << "|" << "pageNo:" << page_no << "|" << "pageSize:" << page_size << endl;

        if (Tool::S2I(room_type) != 0) {
            sql_condition = sql_condition + " and r.type = " + room_type + " ";
        }
        int begin_pos = (page_no - 1) * page_size;
        
        // inessential
        if (param.count("genderType") > 0 && Tool::isNum(param["genderType"]))
        {
            // TODO:: judge legal?
            sql_condition = sql_condition + " and r.gender_type = " + param["genderType"] + " ";
        }
        if (param.count("roomStatus") > 0 && Tool::isNum(param["roomStatus"]))
        {
            // TODO:: judge legal?
            sql_condition = sql_condition + " and r.room_status = " + param["roomStatus"] + " ";
        }


        string er = "6366.564864";
        string lat_length = "(20003.93/180)";
        string lat_left = lat + "-(" + dist + "/" +  lat_length + ")";
        string lat_right = lat + "+(" + dist + "/" +  lat_length + ")";
        string lng_left = lng + "-" + dist + "/abs(cos(radians(" + lat + "))*" + lat_length + ")";
        string lng_right = lng + "+" + dist + "/abs(cos(radians(" + lat + "))*" + lat_length + ")";

        string dis_sql = "SELECT r.id, r.owner_id, u.nickname, r.title, r.type, r.room_status, "
        "  r.preview_pic_id, r.gender_type,  r.limit_person_num,  r.record_id, r.create_time, r.begin_time, a.latitude, a.longitude, a.detail_addr, a.addr_remark, " + 
        er + "*2*ASIN(SQRT(POWER(SIN((" + lat + " - a.latitude)*pi()/180 / 2), 2)" + 
        " +  COS(" + lat + " * pi()/180) * COS(a.latitude * pi()/180) *  POWER(SIN((" + lng + " - a.longitude) * pi()" + 
        "/180 / 2), 2) )) as dist, "
        "(select count(1) from t_room_user_relation where room_id = r.id) as join_person_num "
        " FROM t_address a, t_room r , t_user u WHERE a.latitude BETWEEN " + lat_left + " AND " + lat_right +
        " AND a.longitude BETWEEN " + lng_left + "AND " + lng_right + " AND r.addr_id = a.id and r.owner_id = u.id  "
         + sql_condition + " having dist < " + dist + " ORDER BY dist limit " + Tool::toString(begin_pos) + "," + Tool::toString(page_size) + ";";

        string dis_sql_total = "select count(1), " + 
        er + "*2*ASIN(SQRT(POWER(SIN((" + lat + " - a.latitude)*pi()/180 / 2), 2)" + 
        " +  COS(" + lat + " * pi()/180) * COS(a.latitude * pi()/180) *  POWER(SIN((" + lng + " - a.longitude) * pi()" + 
        "/180 / 2), 2) )) as dist "
        "from t_address a, t_room r , t_user u WHERE a.latitude BETWEEN "
         + lat_left + " AND " + lat_right + " AND a.longitude BETWEEN " + lng_left + "AND " + lng_right + " AND r.addr_id = a.id and r.owner_id = u.id "
          + sql_condition + " having dist < " + dist + ";";

        LOG_DEBUG << dis_sql << endl;
        LOG_DEBUG << dis_sql_total << endl;

         // get data from database
        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), 
        config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));
        // connect fail
        if (!e.connet()) {
            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            msg = "DB ERROR|get room list info|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            e.close();
            break;
        }

        MYSQL mysql;

        // get total count
        ret = e.excute(dis_sql_total);
        // exception
        if (ret != DB_OK) {
            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            msg = "DB ERROR|excute dis_sql_total|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            e.close();
            break;
        }

        mysql = e.get_mysql();
        MYSQL_RES *count_rst = mysql_store_result(&mysql);
        MYSQL_ROW count_row = mysql_fetch_row(count_rst);
        int total_num;
        if (count_row) {
            total_num = atoi(count_row[0]);
        } else {
            result = SHOW_ROOM_LIST_SUCCESS;
            http_res->set_code(SHOW_ROOM_LIST_SUCCESS);
            http_res->set_success(true);
            msg = "DB ERROR|no data";
            LOG_ERROR << msg << endl;
            Data::List *room_list = new Data::List();
            room_list->set_is_end(true);
            http_res->set_allocated_list(room_list);
            http_res->set_msg(msg);
            e.close();
            break;
        }

        e.close();


        // connect fail
        if (!e.connet()) {
            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            msg = "DB ERROR|get room list info|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            e.close();
            break;
        }

        // get page data
        ret = e.excute(dis_sql);

        // exception
        if (ret != DB_OK) {
            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            msg = "DB ERROR|excute dis_sql error|" + Tool::toString(ret);
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
                if (key == "id") {
                    room_info->set_room_id(Tool::fromString<int>(row[i]));
                } else if (key == "title") {
                    room_info->set_title(row[i]);
                } else if (key == "owner_id") {
                    room_info->set_owner_id(Tool::fromString<int>(row[i]));
                } else if (key == "nickname") {
                    room_info->set_owner_nickname(row[i]);
                } else if (key == "type") {
                    room_info->set_type(Tool::fromString<int>(row[i]));
                } else if (key == "room_status") {
                    room_info->set_status(Tool::fromString<int>(row[i]));
                } else if (key == "preview_pic_id") {
                    room_info->set_pic_id(Tool::fromString<int>(row[i]));
                } else if (key == "gender_type") {
                    room_info->set_gender_type(Tool::fromString<int>(row[i]));
                } else if (key == "dist") {
                    room_info->set_distance(Tool::fromString<double>(row[i]));
                } else if (key == "join_person_num") {
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
        if (data_num == total_num) {
            room_list->set_is_end(true);
        }
        http_res->set_allocated_list(room_list);

        e.close();

        // success
        result = SHOW_ROOM_LIST_SUCCESS;
        http_res->set_code(SHOW_ROOM_LIST_SUCCESS);
        http_res->set_success(true);
        msg = "show room list success";
        LOG_INFO << msg << endl;
        http_res->set_msg(msg);
    } while(0);
    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    memcpy(buf, respon_data.c_str(), respon_data.length());
    send_len = respon_data.length();

    google::protobuf::ShutdownProtobufLibrary();

    return result;
}