#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
using namespace std;

int main()
{
	std::ifstream file("법정동코드 전체자료.txt");
	std::locale::global(std::locale("ko_KR.UTF-8")); // UTF-8 CONSOLE
	if (file.is_open()) {
		map<int, string> maps;
		std::string line;
		while (getline(file, line)) {
			if (line.find("\xED\x8F\x90\xEC\xA7\x80") != string::npos) continue; // 폐지 코드 제거
			size_t pos; // 모든 탭을 공백으로
			while ((pos = line.find("\t")) != std::string::npos) line.replace(pos, 1, " ");
			istringstream iss(line); // 공백을 기준으로 문자열 배열로
			vector<string> strs;
			//string result;
			while (getline(iss, line, ' ')) strs.push_back(line);
			try {
				int num = std::stoi(strs[0].substr(0, 4));
				maps.insert({ num,strs[(num % 100 == 0) ? 1 : 2] });
			}
			catch (...) {
				continue;
			}
		}
		file.close();
		for (auto iter : maps) cout << iter.first << "," << iter.second << endl;
	}
	return 0;
}
