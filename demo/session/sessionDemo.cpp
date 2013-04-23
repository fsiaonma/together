#include "../../src/lib/session/session.h"
#include "../../src/util/tool/tool.h"

int main() {
	SESSION session_A;
	// Session *session = Session::get_instance();

	string str;
	Session::get_instance()->set("sam", "99002020202020", str);
	Session::get_instance()->set("sam", "99002020202020dawdawd", str);
	// (*session).set("tony", "99002020202020", str);
	// (*session).set("sam", "99002020202020", str);
 	
 // 	SESSION *session_B;
 // 	string sid;
	// (*session).set("kk", "99002020202020", sid);
	// session_B = (*session).get(sid);
	// if (session_B == NULL) {
	// 	cout << "no session" << endl;
	// } else {
	// 	cout << "session B sid: "<< (*session_B).sid << endl;
	// }

	// string test_sidA;
	// (*session).set("oo", "34324434234", test_sidA);
	// SESSION *session_C = (*session).get(test_sidA);
	// (*session).remove((*session_C).username);

	return 0;
}