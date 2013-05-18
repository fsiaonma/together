#ifndef _MESSAGE_CHAT_H_
#define _MESSAGE_CHAT_H_

#include <iostream>
#include <map>

// map<user_id, sock>
extern std::map<int, int> chat_sock;

void insert_sock(int user_id, int sock);

int find_sock(int user_id);

void del_sock(int user_id);

void del_by_sock(int sock);

void show_sock();

#endif
