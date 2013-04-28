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
        string room_type = Tool::trim(param["roomType"]);
        string longitude = Tool::trim(param["longitude"]);
        string latitude = Tool::trim(param["latitude"]);
        int page_size = Tool::S2I(param["pageSize"]);
        int page_no = Tool::S2I(param["pageNo"]);
        int order_by = Tool::S2I(param["orderBy"]);

        

    } while(0);
    print_proto(http_res);

    http_res->SerializeToString(&respon_data);
    const char *p = respon_data.c_str();
    strncpy(buf, p, strlen(p) + 1);
    google::protobuf::ShutdownProtobufLibrary();

    return result;
}