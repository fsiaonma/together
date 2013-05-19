#include "room.h"

int show_room_info(map<string, string> param, char *buf, int &send_len)
{
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result;
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

        // session is not exist
        SESSION *s = Session::get(Tool::trim(param["sid"]));
        if (s == NULL) {
            result = SESSION_NOT_EXIST;
            http_res->set_code(SESSION_NOT_EXIST);
            msg = "session not exist";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }
        int user_id = Tool::S2I(s->uid);
        LOG_INFO << "user id :" << user_id << endl;
        
        int room_id = Tool::S2I(param["roomId"]);

        if (room_id < 0)
        {
            result = PARAM_ERROR;
            http_res->set_code(PARAM_ERROR);
            msg = "param error";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        MYSQL mysql;

        // connect fail
        if (!e.connet()) {
            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            msg = "DB ERROR|join room|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            e.close();
            break;
        }

        string sql = "select r.id as room_id, r.title, r.owner_id, u.nickname, r.type, r.room_status, "
        "(select count(1) from t_room_user_relation where room_id = r.id and user_id = " + Tool::mysql_filter(user_id) + ") as is_join, "
        " (select count(1) from t_follow where followed_id = r.owner_id and follow_id = " + s->uid + ") as is_follow, "
        "r.preview_pic_id as pic_id, r.gender_type, (select count(1) from t_room_user_relation where room_id = r.id) as join_person_num,  "
        "r.limit_person_num, r.record_id, r.create_time, r.begin_time, a.longitude, a.latitude, a.detail_addr, a.addr_remark "
        "from t_room r, t_address a, t_user u where a.id = r.addr_id and u.id = r.owner_id and r.id = " + param["roomId"];

        LOG_INFO << sql << endl;

        ret = e.excute(sql);
        // exception
        if (ret != DB_OK) {
            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            msg = "DB ERROR| |" + Tool::toString(ret);
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
        int rowcount = mysql_num_rows(rst);
        int fieldcount = mysql_num_fields(rst);
        row = mysql_fetch_row(rst);

        if (rowcount == 1)
        {
            RoomResponse::RoomInfoResponse *room_info_res = new RoomResponse::RoomInfoResponse();
            RoomData::RoomInfo *room_info = new RoomData::RoomInfo();
            RoomData::Address *addr = new RoomData::Address();
            int owner_id;
            int is_join;
            int is_follow;
            for(int i = 0; i < fieldcount; i++) {
                if (row[i] != NULL) {
                    field = mysql_fetch_field_direct(rst, i);
                    string key = field->name;
                    if (key == "room_id") {
                        room_info->set_room_id(Tool::S2I(row[i]));
                    } else if (key == "title") {
                        room_info->set_title(row[i]);
                    } else if (key == "owner_id") {
                        owner_id = Tool::S2I(row[i]);
                        room_info->set_owner_id(Tool::S2I(row[i]));
                    } else if (key == "nickname") {
                        room_info->set_owner_nickname(row[i]);
                    } else if (key == "type") {
                        room_info->set_type(Tool::S2I(row[i]));
                    } else if (key == "room_status") {
                        room_info->set_status(Tool::S2I(row[i]));
                    } else if (key == "pic_id") {
                        room_info->set_pic_id(Tool::S2I(row[i]));
                    } else if (key == "gender_type") {
                        room_info->set_gender_type(Tool::S2I(row[i]));
                    } else if (key == "join_person_num") {
                        room_info->set_join_person_count(Tool::S2I(row[i]) + 1);
                    } else if (key == "limit_person_num") {
                        room_info->set_limit_person_count(Tool::S2I(row[i]));
                    } else if (key == "record_id") {
                        room_info->set_record_id(Tool::S2I(row[i]));
                    } else if (key == "create_time") {
                        room_info->set_create_time(row[i]);
                    } else if (key == "begin_time") {
                        room_info->set_begin_time(row[i]);
                    } else if (key == "longitude") {
                        addr->set_longitude(Tool::fromString<double>(row[i]));
                    } else if (key == "latitude") {
                        addr->set_latitude(Tool::fromString<double>(row[i]));
                    } else if (key == "detail_addr") {
                        addr->set_detail_addr(row[i]);
                    } else if (key == "addr_remark") {
                        addr->set_addr_remark(row[i]);
                    } else if (key == "is_join") {
                        is_join = Tool::S2I(row[i]);
                    } else if (key == "is_follow") {
                    is_follow = Tool::S2I(row[i]);
                    }
                }
            }

            LOG_INFO << "owner_id:" << owner_id << "|" << "is_join:" << is_join << endl;
            if (owner_id == user_id) {
                room_info->set_join_status(2);
                room_info_res->set_relation(UserData::OWN);
            } else {
                if (is_join > 0)
                    room_info->set_join_status(1);
                else
                    room_info->set_join_status(0);
                is_follow > 0 ? room_info_res->set_relation(UserData::FOLLOW): room_info_res->set_relation(UserData::NORELATION);
            }
            room_info->set_allocated_address(addr);
            room_info_res->set_allocated_room_info(room_info);
            // is_follow > 0 ? room_info_res->set_is_follow(true): room_info_res->set_is_follow(false);
            http_res->set_allocated_room_info_response(room_info_res);
            http_res->set_server_time(Tool::now_time());
            e.close();
        } else {
            result = SHOW_ROOM_INFO_ROOM_NOTEXIST;
            http_res->set_code(SHOW_ROOM_INFO_ROOM_NOTEXIST);
            msg = "room not exist";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            e.close();
            break;
        }

        // success
        result = SHOW_ROOM_INFO_SUCCESS;
        http_res->set_code(SHOW_ROOM_INFO_SUCCESS);
        http_res->set_success(true);
        msg = "show room info success";
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