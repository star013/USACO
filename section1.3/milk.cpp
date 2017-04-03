/*
ID: thustar1
PROG: milk
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Farmer {
private:int price;
		int num;
public:
	Farmer() { price = 0; num = 0; }
	Farmer(int price, int num) { this->price=price; this->num=num; }
	Farmer(Farmer& f) { this->price = f.getPrice(); this->num = f.getNum(); }
	void setPrice(int price, int num){ this->price = price; this->num = num; }
	int getPrice() { return price; }
	int getNum() { return num; }
	bool operator < (Farmer& f) { return price < f.getPrice(); }
	bool operator <= (Farmer& f) { return price <= f.getPrice(); }
	bool operator > (Farmer& f) { return price > f.getPrice(); }
	bool operator >= (Farmer& f) { return price >= f.getPrice(); }
	bool operator == (Farmer& f) { return price == f.getPrice(); }
};

void myswap(Farmer& a, Farmer& b) {
	Farmer c = a;
	a = b;
	b = c;
}

int myidx(Farmer* f, int beg, int end) {
	int left = beg, right = end - 1;
	while (left < right) {
		while (f[left] <= f[end]&&left<end) // if only all elements are equal
			left++;
		if (left == end)
			if (f[left - 1] == f[left])
				return left - 1;
			else
				return left;
		while (f[right] >= f[end]&&right>0)
			right--;
		if (left < right) 
			myswap(f[left], f[right]);
	}
	myswap(f[left], f[end]);
	return left;
}
void quickSort(Farmer* f, int beg, int end) {
	if (beg < end) {
		int mid = (beg + end) / 2;
		if (f[beg] > f[mid]) myswap(f[beg], f[mid]);
		if (f[beg] > f[end]) myswap(f[beg], f[end]);
		if (f[mid] > f[end]) myswap(f[mid], f[end]);
		if (end - beg > 2) {
			myswap(f[mid], f[end]);
			int idx = myidx(f, beg, end);
			quickSort(f, beg, idx - 1);
			quickSort(f, idx + 1, end);
		}
	}
}
int main() {
	ofstream fout("milk.out");
	ifstream fin("milk.in");
	int n, people;
	fin >> n >> people;
	int money = 0, rest = n;
	int price = 0, num = 0;
	Farmer* farmers = new Farmer[people];
	for (int i = 0; i < people; i++) {
		fin >> price >> num;
		farmers[i].setPrice(price, num);
	}
	quickSort(farmers, 0, people - 1);
	/*for (int i = 0; i < people; i++) {
		cout << farmers[i].getPrice() << " " << farmers[i].getNum() << endl;
	}*/
	int i = 0;
	while (rest > 0) {
		if (farmers[i].getNum() <= rest) {
			rest -= farmers[i].getNum();
			money += farmers[i].getNum()*farmers[i].getPrice();
			i++;
		}
		else {
			money += rest*farmers[i].getPrice();
			rest = 0;
		}
	}
	fout << money << endl;
	return 0;
}