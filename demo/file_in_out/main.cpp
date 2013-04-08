#include <iostream>
#include <fstream>
using namespace std;

int main() {
	const char filename[] = "mysql_cache.txt";
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
	i_file.open(filename);
	if (i_file.is_open()) {
		while (i_file.good()) {
			i_file >> out_text; // 将读取的内容存储到变量 out_text 中
			cout << out_text << endl; // 在控制台输出读取的内容。为什么最后一行的内容会出现两次
		}
	} else {
		cout << "打开文件：" << filename << " 时出错！";
	}
	i_file.close();
	
	return 0;
}