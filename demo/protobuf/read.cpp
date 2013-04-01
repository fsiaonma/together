#include <iostream>
#include <fstream>
#include <string>
#include "user.pb.h"
using namespace std;

void getLoginResponse(user::LoginResponse *res)
{
  global::ResponseBase *base = new global::ResponseBase();
  base = res->mutable_base();
  cout << "response_code:" << base->response_code() << endl;
  cout << "response_msg:" << base->response_msg() << endl;
  switch (res->type())
  {
    case global::USER:
    {
      cout << "user module" << endl;
      break;
    }
    case global::ROOM:
    {
      cout << "room module" << endl;
      break;
    }
    default:
    break;
  }
  switch (res->result())
  {
    case global::SUCCESS:
    {
      cout << "result:success" << endl;
      break;
    }
    case global::FAIL:
    {
      cout << "result:fail" << endl;
      break;
    }
    default:
    break;
  }
}

void get(user::UserResponse *uRes)
{
  cout << "-----------------------" << endl;
  cout << "show UserResponse" << endl;
  switch (uRes->datatype())
  {
    case user::UserResponse::LOGIN_RESPONSE:
    {
      cout << "dataType:LOGIN_RESPONSE" << endl;
      user::LoginResponse *res = uRes->mutable_loginresponse();
      getLoginResponse(res);
      break;
    }
    default:
      break;
  }
  cout << "-----------------------" << endl;
}

int main(int argc, char* argv[]) {

  user::UserResponse *uRes = new user::UserResponse();
  { 
    fstream input("./response.log", ios::in | ios::binary); 
    if (!uRes->ParseFromIstream(&input)) { 
      cerr << "Failed to parse address book." << endl; 
      return -1; 
    } 
  } 
  get(uRes);
  

  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
