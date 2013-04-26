#include "room.h"

int create_room(map<string, string> param, char *buf)
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
            http_res->set_success(0);
            msg = "param sid not exist";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        // session is not exist
        if (Session::get(Tool::trim(param["sid"])) == NULL) {
            result = SESSION_NOT_EXIST;
            http_res->set_code(SESSION_NOT_EXIST);
            http_res->set_success(0);
            msg = "session not exist";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        LOG_INFO << "title:" << param["title"] << "|type:" << param["type"] << "|beginTime:" << param["beginTime"] << '|endTime:' << param["endTime"]
        << "|userId:" << param["userId"] << "|nickName:" << param["nickName"] << "|limitPersonNum:" << param["limitPersonNum"] << "|genderType:" << param["genderType"]
        << "|longitude:" << param["longitude"] << "|latitude:" << param["latitude"] << "|detailAddr:" << param["detailAddr"] << "|roomDescribe:" << param["roomDescribe"]
        << "|addrRemark:" << param["addrRemark"] << "|picId:" << param["picId"] << "|recordId:" << param["recordId"] << endl;

        string title = param["title"];
        int type = Tool::S2I(param["type"]);
        string begin_time = param["beginTime"];
        string end_time = param["endTime"];
        int user_id = Tool::S2I(param["userId"]);
        string nick_name = param["nickName"];
        string limit_person_num = param["limitPersonNum"];
        int gender_type = Tool::S2I(param["genderType"]);
        long longitude = Tool::fromString<long>(param["longitude"]);
        long latitude = Tool::fromString<long>(param["latitude"]);
        string detail_addr = param["detailAddr"];
        string room_describe = param["roomDescribe"];
        string addr_remark = param["addrRemark"];
        int pic_id = Tool::S2I(param["picId"]);
        int record_id = Tool::S2I(param["recordId"]);

        if (Tool::trim(title).empty() || type < 0 || Tool::trim(begin_time).empty() || Tool::trim(end_time).empty() || user_id < 0
            || Tool::trim(nick_name).empty() || Tool::trim(limit_person_num).empty() || gender_type < 0 || longitude < 0
            || latitude < 0 || Tool::trim(detail_addr).empty() || Tool::trim(room_describe).empty() || Tool::trim(addr_remark).empty() || pic_id < 0 || record_id < 0)
        {
            result = PARAM_ERROR;
            http_res->set_code(PARAM_ERROR);
            http_res->set_success(0);
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
        insert_addr_params["addr_type"] = Tool::mysql_filter(1);
        insert_addr_params["longitude"] = Tool::mysql_filter(longitude);
        insert_addr_params["latitude"] = Tool::mysql_filter(latitude);
        insert_addr_params["detail_addr"] = Tool::mysql_filter(detail_addr);
        insert_addr_params["addr_remark"] = Tool::mysql_filter(addr_remark);

        int addr_insert_id = -1;
        ret = e.insert("t_address", insert_addr_params, addr_insert_id);
        // exception
        if (ret != DB_OK) {
            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            http_res->set_success(0);
            msg = "DB ERROR|insert into t_address|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
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
        insert_room_params["room_describe"] = Tool::mysql_filter(room_describe);
        insert_room_params["begin_time"] = Tool::mysql_filter(begin_time);
        insert_room_params["end_time"] = Tool::mysql_filter(end_time);
        insert_room_params["create_time"] = Tool::mysql_filter(20010101010101);

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
                        http_res->set_success(0);
                        msg = "DB ERROR|delete address|" + Tool::toString(ret);
                        LOG_ERROR << msg << endl;
                        http_res->set_msg(msg);
                        break;
                    }
                }
            }

            result = DB_ERROR;
            http_res->set_code(DB_ERROR);
            http_res->set_success(0);
            msg = "DB ERROR|insert into room|" + Tool::toString(ret);
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        // success
        result = CREATE_ROOM_SUCCESS;
        http_res->set_code(CREATE_ROOM_SUCCESS);
        http_res->set_success(1);
        msg = "insert room success";
        LOG_INFO << msg << endl;
        http_res->set_msg(msg);

    } while(0);
    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    const char *p = respon_data.c_str();
    strncpy(buf, p, strlen(p) + 1);
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}