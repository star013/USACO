/*
ID: thustar1
PROG: ttwo
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

class Cow {
private:
	int x;
	int y;
	int direction; // 0 north, 1 east, 2 south, 3 west
public:
	Cow() { x = 0; y = 0; direction = 0; }
	Cow(int x, int y, int direction = 0) { this->x = x; this->y = y; this->direction = direction; }
	int getX() { return x; }
	int getY() { return y; }
	int getDirection() { return direction;}
	void move() {
		switch (direction)
		{
		case 0:x--; break;
		case 1:y++; break;
		case 2:x++; break;
		case 3:y--; break;
		default:
			break;
		}
	}
	void turnRound() {
		direction = (direction + 1) % 4;
	}
};

bool detectBound(Cow& c, char g[10][10]) {
	if (c.getX() == 0 && c.getDirection() == 0) // upper border
		return true;
	if (c.getX() == 9 && c.getDirection() == 2) // lower border
		return true;
	if (c.getY() == 0 && c.getDirection() == 3) // left border
		return true;
	if (c.getY() == 9 && c.getDirection() == 1) // right border
		return true;
	switch (c.getDirection())
	{
	case 0:if (g[c.getX() - 1][c.getY()] == '*')
		return true;
		   else
			   break;
	case 1:if (g[c.getX()][c.getY() + 1] == '*')
		return true;
		   else
			   break;
	case 2:if (g[c.getX() + 1][c.getY()] == '*')
		return true;
		   else
			   break;
	case 3:if (g[c.getX()][c.getY() - 1] == '*')
		return true;
		   else
			   break;
	default:
		break;
	}
	return false;
}

int main() {
	ofstream fout("ttwo.out");
	ifstream fin("ttwo.in");
	char g[10][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			fin >> g[i][j];
		}
	}

	/*cout << "test input" << endl;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << g[i][j];
		}
		cout << endl;
	}*/

	Cow f,c;// f==farmer, c==cow
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (g[i][j] == 'F')
				f = Cow(i, j);
			if (g[i][j] == 'C')
				c = Cow(i, j);
		}
	}
	/*cout << "farmer initial position = (" << f.getX() << "," << f.getY() << ") direction=" << f.getDirection() << endl;
	cout << "cow initial position = (" << c.getX() << "," << c.getY() << ") direction=" << c.getDirection() << endl;
	*/
	int minute = 1, MAX_MINUTE = 1000000; // there are at most 400*400 states for farmer and cow, 400 is from 100*4, 100 is 10*10 positions, 4 is 4 directioins
	while (minute < MAX_MINUTE) {
		// simulate each minute
		if (detectBound(f, g)) {
			f.turnRound();
			/*cout << "minute " << minute << " farmer turn round at (" << f.getX() << "," << f.getY() << ") direction=" << f.getDirection() << endl;
*/
		}
		else {
			g[f.getX()][f.getY()] = '.';
			f.move();
			g[f.getX()][f.getY()] = 'F';
			/*cout << "minute " << minute << " farmer move to (" << f.getX() << "," << f.getY() << ") direction=" << f.getDirection() << endl;
*/
		}
		if (detectBound(c, g)) {
			c.turnRound();
			/*cout << "minute " << minute << " cow turn round at (" << c.getX() << "," << c.getY() << ") direction=" << c.getDirection() << endl;
*/
		}
		else {
			g[c.getX()][c.getY()] = '.';
			c.move();
			g[c.getX()][c.getY()] = 'C';
			/*cout << "minute " << minute << " cow move to (" << c.getX() << "," << c.getY() << ") direction=" << c.getDirection() << endl;
*/
		}
		if (f.getX() == c.getX() && f.getY() == c.getY())
			break;
		minute++;
		/*for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				cout << g[i][j];
			}
			cout << endl;
		}*/
	}
	if (minute == MAX_MINUTE) // never encounter
		minute = 0;
	fout << minute << endl;
	return 0;
}