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

std::string getKoreanDiscardString() // 폐지 문자열을 UTF-8형식으로 저장한 파일
{
	std::ifstream discardFile("discard.txt");
	char str[100];
	discardFile.getline(str, sizeof(str));
	std::string strDiscard = str;
	discardFile.close();
	return strDiscard;
}

int main()
{
	std::string strDiscard = getKoreanDiscardString();
	std::ifstream file("법정동코드 전체자료.txt");
	std::locale::global(std::locale("ko_KR.UTF-8")); // UTF-8 CONSOLE
	if (file.is_open()) {
		map<int, string> maps;
		char str[100];
		while (file.getline(str, sizeof(str))) {
			std::string line = str;
			if (line.find(strDiscard) != string::npos) continue;;
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
