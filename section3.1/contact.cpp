/*
ID: thustar1
PROG: contact
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

struct Data
{
	int len; // length
	int hash; // hash value
	int count; // count number
};

int cmp(const void* a, const void* b) {
	Data* aa = (Data*)a;
	Data* bb = (Data*)b;
	if (aa->count != bb->count)
		return bb->count - aa->count;
	else {
		if (aa->len != bb->len)
			return aa->len - bb->len;
		else {
			return aa->hash - bb->hash;
		}
	}
}

int main() {
	ofstream fout("contact.out");
	ifstream fin("contact.in");
	int a, b, n;
	fin >> a >> b >> n;
	int bit[200000];
	int len = 0;
	char tmp[81];
	fin.getline(tmp, 81);// read \n
	//cout << "tmp=" << tmp << endl;
	while (true) {
		fin.getline(tmp, 81);
		//cout << "tmp=" << tmp << endl;
		string t = tmp;
		if (t.size() == 0)
			break;
		for (int i = 0; i < t.size(); i++) {
			bit[len] = t[i] - '0';
			len++;
		}
	}
	/*cout << "length of bit=" << len << endl;
	for (int i = 0; i < len; i++)
		cout << bit[i];
	cout << endl;*/


	// Use Hash Table
	// 1<=a<=b<=12
	const int MAXVALUE = 4096;//2^12=4096
	int table[12 * MAXVALUE];
	for (int i = 0; i < 12 * MAXVALUE; i++)
		table[i] = 0;
	for (int i = 0; i < len; i++) {
		int tmp = 0;
		for (int j = 0; j < a-1; j++)
			tmp = 2 * tmp + bit[i + j];
		for (int j = a-1; j < b; j++) {
			if (i + j < len) {
				tmp = 2 * tmp + bit[i + j];
				table[j*MAXVALUE + tmp]++; // count
			}
		}
	}
	vector<Data> data;
	for (int i = (a - 1)*MAXVALUE; i < b*MAXVALUE; i++) {
		if (table[i] > 0) {
			Data tmp;
			tmp.len = i / MAXVALUE + 1;
			tmp.hash = i%MAXVALUE;
			tmp.count = table[i];
			data.push_back(tmp);
		}
	}
	qsort(&data[0], data.size(), sizeof(Data), cmp);
	vector<Data> res[50];
	int nres = 0, prevcount = 0;
	for (int i = 0; i < data.size(); i++) {
		/*char pattern[13];
		pattern[data[i].len] = '\0';
		int tmp = data[i].hash;
		for (int j = 0; j < data[i].len; j++) {
			pattern[data[i].len - 1 - j] = '0' + tmp % 2;
			tmp /= 2;
		}
		cout << "count = " << data[i].count << ", pattern = " << pattern << endl;*/
		if (prevcount != data[i].count) {
			nres++;
			prevcount = data[i].count;
			res[nres - 1].push_back(data[i]);
		}
		else {
			res[nres - 1].push_back(data[i]);
		}
		if (nres > n)
			break;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < res[i].size(); j++) {
			char pattern[13];
			pattern[res[i][j].len] = '\0';
			int tmp = res[i][j].hash;
			for (int k = 0; k < res[i][j].len; k++) {
			pattern[res[i][j].len - 1 - k] = '0' + tmp % 2;
			tmp /= 2;
			}
			if (j == 0) {
				fout << res[i][j].count << endl 
					<< pattern;
			}else if (j % 6 == 0) {
				fout << endl 
					<< pattern;
			}
			else {
				fout << " " << pattern;
			}
		}
		if(res[i].size()>0)
			fout << endl;
	}
	return 0;
}