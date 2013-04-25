#include <iostream>
#include <fstream>
#include <string>
#include "user.pb.h"
#include <google/protobuf/text_format.h>

using namespace std;

void set(user::LoginResponse *res)
{
  global::ResponseBase *base = new global::ResponseBase();
  base->set_response_code(200);
  base->set_response_msg("test protobuf");
  res->set_allocated_base(base);
  res->set_type(global::USER);
  res->set_result(global::SUCCESS);
}

int main(int argc, char* argv[]) {

  user::UserResponse *uRes = new user::UserResponse();

  user::LoginResponse *res = new user::LoginResponse();

  set(res);

  uRes->set_datatype(user::UserResponse::LOGIN_RESPONSE);
  uRes->set_allocated_loginresponse(res);

    string outString;
    google::protobuf::TextFormat::PrintToString(*uRes ,&outString);
    cout << outString << endl; 

  fstream output("./response.log", ios::out | ios::trunc | ios::binary);   
  
  if (!uRes->SerializeToOstream(&output)) {   
    cerr << "Failed to write msg." << endl;   
    return -1;   
  }

  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
