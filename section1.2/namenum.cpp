/*
ID: thustar1
PROG: namenum
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

string phoneMap(const char &c) {
	string tmp;
	switch (c)
	{
		case '2': tmp = "ABC";
		break;
		case '3': tmp = "DEF";
		break;
		case '4': tmp = "GHI";
			break;
		case '5': tmp = "JKL";
			break;
		case '6': tmp = "MNO";
			break;
		case '7': tmp = "PRS";
			break;
		case '8': tmp = "TUV";
			break;
		case '9': tmp = "WXY";
			break;
	default:
		break;
	}
	return tmp;
}

/*
Because 3^12 = 531441, which is not a very large number, we can just use Brute Force algorithm to search all results in dictionary
When data is large, use hash table to judge, that is unordered_set
Using recurrent to get all combinations, however in Test10 length is 10, it consumes too many memory

Therefore, 2nd solution use a reverse direction. Because there is only 5k names, just use these names to match the input number.
Each match operation is O(L), L is the length of the input. Both time and space consumption is reduced to 5kL
*/
void getAllName(const string &input, const string& substr, int pos, vector<string>& result) {
	if (pos == input.size() - 1) {
		string tmp = phoneMap(input[pos]);
		for (int i = 0; i < tmp.size(); i++)
			result.push_back(substr + tmp[i]);
	}
	else {
		string tmp = phoneMap(input[pos]);
		for (int i = 0; i < tmp.size(); i++)
			getAllName(input, substr + tmp[i], pos + 1, result);
	}
}

bool match(const string& input, const string& name) {
	bool result = false;
	if (input.size() == name.size()) {
		int i = 0;
		for (i = 0; i < name.size(); i++) {
			string tmp = phoneMap(input[i]);
			bool exist = false;
			for (int j = 0; j < tmp.size(); j++) {
				if (tmp[j] == name[i]) {
					exist = true;
					break;
				}
			}
			if (!exist)
				break;
		}
		if (i == name.size())
			result = true;
	}
	return result;
}
int main() {
	ofstream fout("namenum.out");
	ifstream fin("namenum.in");
	string input;
	fin >> input;
	// read valid names from file
	ifstream datain("dict.txt");
	string name;
	bool none = true;
	while (datain.good()) {
		getline(datain, name);
		if (match(input, name)) {
			fout << name << endl;
			none = false;
		}
	}
	// old direct solve
	/*vector<string> allNames;
	datain.clear();
	datain.seekg(0, datain.beg);
	unordered_set<string> validNames;
	for (int i = 0; i < num_line; i++) {
		getline(datain, line);
		validNames.emplace(line);
	}
	getAllName(input, "", 0, allNames);
	bool none = true;
	for (int i = 0; i < allNames.size(); i++) {
		if (validNames.find(allNames[i]) != validNames.end()) {
			cout << allNames[i] << endl;
			none = false;
		}
	}*/

	// 2nd sololution: use each name in dictionary to match the input
	if (none)
		fout << "NONE" << endl;
	//fout<< endl;
	return 0;
}