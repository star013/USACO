/*
ID: thustar1
PROG: milk2
LANG: C++
*/
#include <fstream>
#include <iostream>
using namespace std;

class Time {
private:
	int begin;
	int end;
public:
	Time() { begin = 0; end = 0; }
	Time(int begin, int end) {
		this->begin = begin;
		this->end = end;
	}
	Time(Time& t) {
		this->begin = t.getBegin();
		this->end = t.getEnd();
	}
	bool operator < (Time& t) {
		return this->begin < t.getBegin();
	}

	bool operator > (Time& t) {
		return this->begin > t.getBegin();
	}

	bool operator <= (Time& t) {
		return this->begin <= t.getBegin();
	}

	bool operator >= (Time& t) {
		return this->begin >= t.getBegin();
	}

	void set(int begin, int end) { this->begin = begin; this->end = end; }
	int getBegin() { return begin; }
	int getEnd() { return end; }
	void print() { cout << begin << " " << end << endl; }
};

void swap(Time& a, Time& b) {
	Time c = a;
	a = b;
	b = c;
}

int sortIndex(Time*t, int mid, int beg, int end) {
    // 1. define a function before it is used, or you should declare the function before it is used. Or it will tell you the function is not an identifier
	int left = beg;
	int right = end - 1;
	swap(t[mid], t[end]);
	while (left < right) {
		while (t[left] <= t[end])
			left++;
		while (t[right] >= t[end])
			right--;
        // 2. Pay attention to one condition: left == right-2, if you want to use left++ and right--, then left and right would point to the same position. At this time, WHILE loop stops. if t[left]<t[end], it will produce an error
		if (left < right) {
			swap(t[left], t[right]);
		}
	}
	swap(t[end], t[left]);
	return left;
}

void qSort(Time* t, int beg, int end) {
	if (end - beg < 1)
		return;
	int mid = (beg + end) / 2;
	// select a middle one
	if (t[beg] > t[end])
		swap(t[beg], t[end]);
	if (t[beg] > t[mid])
		swap(t[beg], t[mid]);
	if (t[mid] > t[end])
		swap(t[end], t[mid]);
	// stop when it is narrow
	if (end - beg < 3)
		return;
	int idx = 0;
	idx = sortIndex(t, mid, beg, end);
	qSort(t, beg, idx - 1);
	qSort(t, idx + 1, end);

}



void solve(int newBegin, int newEnd, int& prevBegin, int& prevEnd, int& conti, int& idle) {
	if (newBegin > prevEnd) {
		// get a new idle
		int newIdle = newBegin - prevEnd;
		if (idle < newIdle)
			idle = newIdle;
		prevBegin = newBegin;
		prevEnd = newEnd;
	}
	else {
		// get a new conti
		if (prevEnd < newEnd) {
			prevEnd = newEnd;
		}
	}
	int newConti = prevEnd - prevBegin;
	if (conti < newConti) {
		conti = newConti;
	}
}

int main() {
	int yrs;
	ofstream fout("milk2.out");
	ifstream fin("milk2.in");
	int n;
	fin >> n;
	int prevBegin = 0, prevEnd = 0, conti = 0, idle = 0;
	int newBegin, newEnd;
	Time* t = new Time[n];

	for (int i = 0; i < n; i++) {
		fin >> newBegin >> newEnd;
		t[i].set(newBegin, newEnd);
	}
	// sort
	qSort(t, 0, n - 1);
	//cout << "#####################################" << endl << endl << endl;
	int begin = t[0].getBegin();
	//for (int i = 0; i < n; i++) {
	//	//cout << "No. " << i << endl;
	//	t[i].print();
	//}

	for (int i = 0; i < n; i++) {
		solve(t[i].getBegin()-begin, t[i].getEnd()-begin, prevBegin, prevEnd, conti, idle);
	}
	fout << conti << " " << idle;
	fout << endl;
	return 0;
}