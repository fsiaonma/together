#include "../../src/lib/session/session.h"

int main() {
	session s("username", "password");
	cout << s.get_sid() << endl;
	s.set("username", "sam");
	cout << s.get("username") << endl;

	session_list sl;
	string str = s.get_sid();
	sl.set_session(s);
	cout << sl.get_session(str).get_sid() << endl;
	return 0;
}