/*
ID: thustar1
PROG: string utility
LANG: C++11
*/

int s2i(string s) { // convert string s to an integar
	if (s.size() == 0)
		return 0;
	int res = 0;
	for (int i = 0; i < s.size(); i++)
		res = res * 10 + s[i] - '0';
	return res;
}
// convert int to string
// just use to_string(s)

//example
string tmp = "";// You can NOT initialize a string like
// tmp=""+s[a.size()];
tmp+=s[a.size()];
int init = s2i(tmp);