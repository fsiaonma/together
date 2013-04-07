#include "../../src/lib/session/session.h"

int main() {
	session s("username", "password");
	cout << s.sid << endl;
	return 0;
}