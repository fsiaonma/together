#include "room.h"

int show_room_list(map<string, string> param, char *buf)
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
            http_res->set_success(0);
            msg = "param error";
            LOG_ERROR << msg << endl;
            http_res->set_msg(msg);
            break;
        }

        LOG_INFO << "room_type:" << room_type << "|" << "longitude:" << lng << "|" << 
        "latitude:" << lat << "|" << "pageNo:" << page_no << "|" << "pageSize:" << page_size << endl;

        sql_condition = sql_condition + " and r.type = " + room_type + " ";
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
        "  r.preview_pic_id, r.gender_type, count(rel.id) as join_person_num, r.limit_person_num,  r.record_id, r.create_time, r.begin_time, a.latitude, a.longitude," + 
        er + "*2*ASIN(SQRT(POWER(SIN((" + lat + " - a.latitude)*pi()/180 / 2), 2)" + 
        " +  COS(" + lat + " * pi()/180) * COS(a.latitude * pi()/180) *  POWER(SIN((" + lng + " - a.longitude) * pi()" + 
        "/180 / 2), 2) )) as dist FROM t_address a, t_room r left join t_room_user_relation rel on (r.id = rel.room_id), t_user u WHERE a.latitude BETWEEN " + lat_left + " AND " + lat_right +
        " AND a.longitude BETWEEN " + lng_left + "AND " + lng_right + " AND r.addr_id = a.id and r.owner_id = u.id  "
         + sql_condition + " having dist < " + dist + " ORDER BY dist limit " + Tool::toString(begin_pos) + "," + Tool::toString(page_size) + ";";

         LOG_DEBUG << dis_sql << endl;

    } while(0);
    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    const char *p = respon_data.c_str();
    strncpy(buf, p, strlen(p) + 1);
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}