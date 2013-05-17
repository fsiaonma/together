#include "message.h"

int save_msg(int sock, map<string, string> param, list<int> &send_sock_list, char *buf)
{
    char c_rst[10];
    int result = SAVE_MSG_SUCCESS;
    send_sock_list.push_back(sock);
    do
    {
        
    } while(0);
    sprintf(c_rst, "%d", result);
    strncpy(buf, c_rst, strlen(c_rst) + 1);
    return result;
}