#include "message_sock.h"

std::map<int, int> chat_sock;

void insert_sock(int user_id, int sock)
{
    chat_sock[user_id] = sock;
}

int find_sock(int user_id)
{
    std::map<int, int>::iterator iter;
    for (iter = chat_sock.begin(); iter != chat_sock.end(); iter++)
    {
        if (iter->first == user_id)
            return iter->second;
    }
    return -1;
}

void del_sock(int user_id)
{
    std::map<int, int>::iterator iter;
    for (iter = chat_sock.begin(); iter != chat_sock.end(); iter++)
    {
        if (iter->first == user_id)
        {
            chat_sock.erase(iter++);
            break;
        }
    }
}

void del_by_sock(int sock)
{
    std::map<int, int>::iterator iter;
    for (iter = chat_sock.begin(); iter != chat_sock.end(); iter++)
    {
        if (iter->second == sock)
        {
            chat_sock.erase(iter++);
            break;
        }
    }
}

void show_sock()
{
    std::map<int, int>::iterator iter;
    std::cout << "------------------- show_sock" << std::endl;
    for (iter = chat_sock.begin(); iter != chat_sock.end(); iter++)
    {
        std::cout << iter->first << "|" << iter->second << std::endl;
    }
    std::cout << "------------------- end show_sock" << std::endl;
}