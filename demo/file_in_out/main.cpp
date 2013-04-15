#include <iostream>
#include <fstream>
using namespace std;

int main() {
	const char filename[] = "mysql_cache";
	ofstream o_file;
	ifstream i_file;
	string out_text;

	// 写
	o_file.open(filename);
	for (int i = 1; i <= 10; ++i) {
		o_file << "第" << i << "行\n"; // 将内容写入到文本文件中
	}
	o_file.close();

	// 读
	ifstream out;
    string str = "mysql_cache";
    out.open(str.c_str(), ios::in);
    string line;
    while(!out.eof()){
        std::getline(out,line);
        if (line == "") {
        	cout << 'a' << endl;
        }
        // cout <<line<<endl;
    }
    out.close();


	return 0;
}