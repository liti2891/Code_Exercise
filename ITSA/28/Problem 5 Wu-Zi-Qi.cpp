#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;

#define size 20
int map[size][size] = { 0 };

int cmp(int, int);
int find_five(int, int, int, int);
void who_win();

int main() {
	string inStr;
	string step;
	int who = 1;//A=1, B=2
	int x, y;

	while (getline(cin, inStr)) {  //一次讀一行
		if (inStr == "(0,0) (0,0)"&&who == 1)break;  //題目要求離開條件

		stringstream row(inStr);  //將輸入字串轉為字串流
		while (row >> step) {  //將整行資料一個一個讀出來(類似cin 空白間隔)
			sscanf_s(step.c_str(), "(%d,%d)", &x, &y);//字串格式化
			map[x][y] = who;  //將找到的位置給出玩家編號
		}

		if (who == 1)who = 2;  //A結束後換B
		else {
			who = 1;  //換回A
			who_win();  //檢查誰勝利並輸出
			memset(map, 0, sizeof(map));  //map歸零
		}
	}
	return 0;
}

int cmp(int a, int b) {
	return a > b ? a : b;
}

int find_five(int x, int y, int dx, int dy) {
	int who = map[x][y];
	//往(dx,dy)方向搜尋，出現跟who不一樣就回傳0
	for (int i = 0; i < 5; i++) {
		if (map[x + i * dx][y + i * dy] != who)return 0;
	}
	return who;
}

void who_win() {
	int who = 0;  //預設平手=0
	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++) {
			if (map[x][y] != 0) {
				if (x <= size - 5)//垂直掃描
					who = cmp(who, find_five(x, y, 1, 0));
				if (y <= size - 5)//水平掃描
					who = cmp(who, find_five(x, y, 0, 1));
				if (y <= size - 5 && y <= size - 5)//右斜掃描
					who = cmp(who, find_five(x, y, 1, 1));
				if (y <= size - 5 && size - y + 1 >= size - 5)//左斜掃描
					who = cmp(who, find_five(x, y, 1, -1));

				if (who != 0)break;  //找到贏家後退出
			}
		}
	if (who == 0)cout << "None" << endl;
	if (who == 1)cout << "A wins" << endl;
	if (who == 2)cout << "B wins" << endl;
}