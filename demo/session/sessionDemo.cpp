#include "../../src/lib/session/session.h"
#include "../../src/util/tool/tool.h"

int main() {
	SESSION session_A;
	session s;

	s.set("4", "sam", "99002020202020");
	s.set("5", "egg", "99002020202020dawdawd");
	s.set("6", "tony", "99002020202020");
	s.set("7", "sam", "99002020202020");
 	
 	SESSION *session_B;
	string sid = s.set("8", "kk", "99002020202020");
	session_B = s.get(sid);
	if (session_B == NULL) {
		cout << "no session" << endl;
	} else {
		cout << (*session_B).sid << endl;
	}

	string test_sidA = s.set("9", "oo", "34324434234");
	SESSION *session_C = s.get(test_sidA);
	s.remove((*session_C).username);

	return 0;
}