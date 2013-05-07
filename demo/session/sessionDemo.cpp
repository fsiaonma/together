#include "../../src/lib/session/session.h"
#include "../../src/util/tool/tool.h"

int main() {
	SESSION session_A;
	// Session *session = Session::get_instance();

	string str;
	Session::set("1", "99002020202020", str);
	Session::set("1", "99002020202020dawdawd", str);
	Session::set("2", "99002020202020", str);
	Session::set("1", "99002020202020", str);
 	
 	SESSION *session_B;
 	string sid;
	Session::set("kk", "99002020202020", sid);
	session_B = Session::get(sid);
	if (session_B == NULL) {
		cout << "no session" << endl;
	} else {
		cout << "session B sid: "<< (*session_B).sid << endl;
	}

	string test_sidA;
	Session::set("oo", "34324434234", test_sidA);
	SESSION *session_C = Session::get(test_sidA);
	Session::remove((*session_C).uid);

	return 0;
}