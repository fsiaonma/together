#include "../../src/lib/session/session.h"

int main() {
	session s;
	SESSION session_A;
	session_A = s.set("3", "sam", "029889");
	cout << session_A.username << endl;
	SESSION *session_B;
	session_B = s.get(session_A.sid);
	if (session_B == NULL) {
		cout << "no session" << endl;
	} else {
		cout << (*session_B).sid << endl;
	}
	return 0;
}