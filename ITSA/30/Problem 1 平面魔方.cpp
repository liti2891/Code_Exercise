#include <iostream>
#include <string>
using namespace std;

#define size 10
void init(int);
void rotate90(int, bool);
void flip(int);

int matrix[size][size];
int main() {
	int m;
	cin >> m;

	int n;
	string steps;
	while (m--) {
		cin >> n;
		cin >> steps;
		init(n);//初始化陣列

		//將陣列對每個步驟做處理
		for (int i = 0; i < steps.length(); i++) {
			char s = steps[i];
			if (s == 'R')rotate90(n, true);
			else if (s == 'L')rotate90(n, false);
			else if (s == 'N')flip(n);
		}

		//印出結果
		for (int y = 0; y < n; y++) 
			for (int x = 0; x < n; x++) {
				cout << matrix[y][x];
				if (x == n - 1)cout << endl;
				else cout << ' ';
			}
		if (m > 0)	cout << endl;
	}

	return 0;
}

void init(int n) {
	//初始化陣列
	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++) {
			matrix[y][x] = (x + 1) + n * y;
		}
	return;
}

void rotate90(int n, bool clockwise) {
	int dstMatrix[size][size];
	int sin90 = clockwise ? 1 : -1;	//sin(90°)=1，sin(-90°)=-1
	int cos90 = 0;//cos(+-90°)=0

	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++) {
			//旋轉矩陣
			//[x']   [cos -sin offset][x]
			//[y'] = [sin  cos offset][y]
			//[ 1]   [ 0    0     1  ][1]
			int dstX = (int)(cos90*x - sin90 * y) + (clockwise ? n - 1 : 0);
			int dstY = (int)(sin90*x + cos90 * y) + (clockwise ? 0 : n - 1);
			dstMatrix[dstY][dstX] = matrix[y][x];
		}
	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++) {
			matrix[y][x] = dstMatrix[y][x];
		}

}

void flip(int n) {
	//翻轉
	int dstMatrix[size][size];
	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++) {
			dstMatrix[n - y - 1][x] = matrix[y][x];
		}
	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++) {
			matrix[y][x] = dstMatrix[y][x];
		}
}