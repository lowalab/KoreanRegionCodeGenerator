#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
using namespace std;

vector<string> split(string str, char Delimiter) {
	istringstream iss(str);
	string buffer;
	vector<string> result;
	while (getline(iss, buffer, Delimiter)) result.push_back(buffer);
	return result;
}

int main()
{
	std::ifstream file("법정동코드 전체자료.txt");
	std::locale::global(std::locale("ko_KR.UTF-8")); // UTF-8 CONSOLE
	if (file.is_open()) {
		map<int, string> maps;
		char str[100];
		while (file.getline(str, sizeof(str))) {
			std::string line = str;
			if (line.find("\xED\x8F\x90\xEC\xA7\x80") != string::npos) continue; // 폐지 코드 제거
			line.replace(line.find("\t"), 1, " ");
			line.replace(line.find("\t"), 1, " ");
			vector<string> strs = split(line, ' ');
			int num = -1;
			try {
				int num = std::stoi(strs[0].substr(0, 4));
				if (num % 100 == 0)
					maps.insert({ num,strs[1] });
				else
					maps.insert({ num,strs[2] });
			}
			catch (...) {
				continue;
			}
		}
		file.close();
		for (auto iter : maps) {
			cout << iter.first << "," << iter.second << endl;
		}
	}
	return 0;
}
