#include "room.h"

int create_room(map<string, string> param, char *buf, int &send_len)
{
    string respon_data;
    Response::HTTPResponse *http_res = new Response::HTTPResponse();
    string msg;
    int result = CREATE_ROOM_SUCCESS;
    int ret;

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
        if (Session::get(Tool::trim(param["sid"])) == NULL) {
            result = SESSION_NOT_EXIST;
            http_res->set_code(SESSION_NOT_EXIST);
            msg = "session not exist";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        LOG_INFO << "title:" << param["title"] << "|type:" << param["type"] << endl;
        LOG_INFO << "beginTime:" << param["beginTime"] << "|endTime:" << param["endTime"] << endl;
        LOG_INFO << "userId:" << param["userId"] << "|nickName:" << param["nickName"] << endl;
        LOG_INFO << "limitPersonNum:" << param["limitPersonNum"] << "|genderType:" << param["genderType"] << endl;
        LOG_INFO << "longitude:" << param["longitude"] << "|latitude:" << param["latitude"] << endl;
        LOG_INFO << "detailAddr:" << param["detailAddr"] << "|addrRemark:" << param["addrRemark"] << endl;
        LOG_INFO << "picId:" << param["picId"] << "|recordId:" << param["recordId"] << endl;

        string title = param["title"];
        int type = Tool::S2I(param["type"]);
        string begin_time = param["beginTime"];
        int user_id = Tool::S2I(param["userId"]);
        string nick_name = param["nickName"];
        string limit_person_num = param["limitPersonNum"];
        int gender_type = Tool::S2I(param["genderType"]);
        string detail_addr = param["detailAddr"];
        // string addr_remark = param["addrRemark"];
        int pic_id = Tool::S2I(param["picId"]);
        int record_id = Tool::S2I(param["recordId"]);

        if (Tool::trim(title).empty() || type < 0 || Tool::trim(begin_time).empty() ||  user_id < 0
            || Tool::trim(nick_name).empty() || Tool::trim(limit_person_num).empty() || gender_type < 0 || 
            // longitude < 0 || latitude < 0 || 
            Tool::trim(detail_addr).empty() || 
            // Tool::trim(addr_remark).empty() || 
            pic_id < 0 || record_id < 0
            || !(gender_type >= 0 && gender_type < GENDERTYPE_NUM))
        {
            result = PARAM_ERROR;
            http_res->set_code(PARAM_ERROR);
            msg = "param error";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        // database params
        Config *c = Config::get_instance();
        map<string, string> config = c->get_config();
        eagleMysql e(config["DOMAIN"].c_str(), config["USER_NAME"].c_str(), config["PASSWORD"].c_str(), config["DATABASE"].c_str(), Tool::S2I(config["PORT"], 3306));

        // save the address info to database
        map<string, string> insert_addr_params;
        insert_addr_params["addr_type"] = Tool::mysql_filter(type);
        insert_addr_params["longitude"] = param["longitude"];
        insert_addr_params["latitude"] = param["latitude"];
        insert_addr_params["detail_addr"] = Tool::mysql_filter(detail_addr);
        // insert_addr_params["addr_remark"] = Tool::mysql_filter(addr_remark);


        int addr_insert_id = -1;
        ret = e.insert("t_address", insert_addr_params, addr_insert_id);
        // exception
        if (ret != DB_OK) {
            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            msg = "DB ERROR|insert into t_address|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            e.close();
            break;
        }

        // save the room info to database
        map<string, string> insert_room_params;
        insert_room_params["owner_id"] = Tool::mysql_filter(user_id);
        insert_room_params["title"] = Tool::mysql_filter(title);
        insert_room_params["type"] = Tool::mysql_filter(type);
        insert_room_params["gender_type"] = Tool::mysql_filter(gender_type);
        insert_room_params["limit_person_num"] = Tool::mysql_filter(limit_person_num);
        insert_room_params["preview_pic_id"] = Tool::mysql_filter(pic_id);
        insert_room_params["addr_id"] = Tool::mysql_filter(addr_insert_id);
        insert_room_params["record_id"] = Tool::mysql_filter(record_id);
        insert_room_params["begin_time"] = begin_time;
        insert_room_params["create_time"] = Tool::now_time();
        insert_room_params["room_status"] = "0";

        int room_insert_id = -1;
        ret = e.insert("t_room", insert_room_params, room_insert_id);
        // exception
        if (ret != DB_OK) {
            // delete addr data
            {
                ret = e.remove("t_address", "where id = " + Tool::toString(addr_insert_id));
                if (ret != DB_OK)
                {
                    ret = e.remove("t_address", "where id = " + Tool::toString(addr_insert_id));
                    if (ret != DB_OK)
                    {
                        result = DB_ERROR;
                        http_res->set_code(DB_ERROR);
                        msg = "DB ERROR|delete address|" + Tool::toString(ret);
                        LOG_ERROR << msg << endl;
                        http_res->set_msg(msg);
                        e.close();
                        break;
                    }
                }
            }

            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            msg = "DB ERROR|insert into room|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            e.close();
            break;
        }

        // success
        result = CREATE_ROOM_SUCCESS;
        http_res->set_code(CREATE_ROOM_SUCCESS);
        http_res->set_success(true);


        RoomData::Address *addr = new RoomData::Address();
        addr->set_addr_type(type);
        addr->set_longitude(Tool::fromString<double>(param["longitude"]));
        addr->set_latitude(Tool::fromString<double>(param["latitude"]));
        addr->set_detail_addr(detail_addr);

        RoomResponse::CreateRoomResponse *cr_res = new RoomResponse::CreateRoomResponse();
        RoomData::RoomInfo *room_info = new RoomData::RoomInfo();
        room_info->set_room_id(room_insert_id);
        room_info->set_owner_id(user_id);
        room_info->set_title(title);
        room_info->set_type(type);
        room_info->set_gender_type(gender_type);
        room_info->set_join_person_count(1);
        room_info->set_limit_person_count(Tool::S2I(limit_person_num));
        room_info->set_pic_id(pic_id);
        room_info->set_record_id(record_id);
        room_info->set_begin_time(param["beginTime"]);
        room_info->set_create_time(Tool::now_time());
        room_info->set_status(0);
        room_info->set_allocated_address(addr);
        cr_res->set_allocated_room_info(room_info);
        http_res->set_allocated_create_room_response(cr_res);


        msg = "insert room success";
        LOG_INFO << msg << endl;
        http_res->set_msg(msg);
        http_res->set_server_time(Tool::now_time());
        e.close();

    } while(0);
    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    memcpy(buf, respon_data.c_str(), respon_data.length());
    send_len = respon_data.length();
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}