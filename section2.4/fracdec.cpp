/*
ID: thustar1
PROG: fracdec
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int main() {
	ofstream fout("fracdec.out");
	ifstream fin("fracdec.in");
	int n, d;//n=nominator, d=denominator
	fin >> n >> d; // 1 <= N,D <= 100000
	
	int table[10][100000]; // a better way is just to consider the remainder, if the remainder repeats, it means digits are repeating
	// table[i][j] == position of number i with remain j when N is divided by D
	// like a hash table
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < d; j++)
			table[i][j] = 0;
	
	int integar = n / d;
	int remain = 10 * (n - integar*d);
	string res = to_string(integar) + '.';
	
	string decimal = "";
	int pos = 1, tmp = 0;// pos == position of current digit after ".", e.g. pos==1 means the position of "1" in "0.123"
	while (remain > 0) {
		tmp = remain / d;
		remain -= tmp*d;
		if (table[tmp][remain] == 0) {
			table[tmp][remain] = pos;
			decimal += (char)(tmp + '0');
		}
		else {
			break;
		}
		pos++;
		remain *= 10; // remain should be enlarged to calculate the next position
	}
	if (remain > 0) {
		// repeated decimal representation
		for (int i = 0; i < table[tmp][remain] - 1; i++)
			res += decimal[i];
		res += '(';
		for (int i = table[tmp][remain] - 1; i < decimal.size(); i++)
			res += decimal[i];
		res += ')';
	}
	else {
		// remain==0
		if (decimal.size() == 0) // nominator is the multiple of denominator
			res += '0';
		else{
			for (int i = 0; i < decimal.size(); i++)
				res += decimal[i];
		}
	}
	// If the expansion exceeds 76 characters in length, print it on multiple lines with 76 characters per line.
	for (int i = 0; i < res.size(); i++) {
		if (i % 76 == 0&&i>0)
			fout << endl;
		fout << res[i];
	}
	fout << endl;
	return 0;
}