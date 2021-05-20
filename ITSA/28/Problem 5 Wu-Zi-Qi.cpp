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

	while (getline(cin, inStr)) {  //�@��Ū�@��
		if (inStr == "(0,0) (0,0)"&&who == 1)break;  //�D�حn�D���}����

		stringstream row(inStr);  //�N��J�r���ର�r��y
		while (row >> step) {  //�N����Ƥ@�Ӥ@��Ū�X��(����cin �ťն��j)
			sscanf_s(step.c_str(), "(%d,%d)", &x, &y);//�r��榡��
			map[x][y] = who;  //�N��쪺��m���X���a�s��
		}

		if (who == 1)who = 2;  //A�����ᴫB
		else {
			who = 1;  //���^A
			who_win();  //�ˬd�ֳӧQ�ÿ�X
			memset(map, 0, sizeof(map));  //map�k�s
		}
	}
	return 0;
}

int cmp(int a, int b) {
	return a > b ? a : b;
}

int find_five(int x, int y, int dx, int dy) {
	int who = map[x][y];
	//��(dx,dy)��V�j�M�A�X�{��who���@�˴N�^��0
	for (int i = 0; i < 5; i++) {
		if (map[x + i * dx][y + i * dy] != who)return 0;
	}
	return who;
}

void who_win() {
	int who = 0;  //�w�]����=0
	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++) {
			if (map[x][y] != 0) {
				if (x <= size - 5)//�������y
					who = cmp(who, find_five(x, y, 1, 0));
				if (y <= size - 5)//�������y
					who = cmp(who, find_five(x, y, 0, 1));
				if (y <= size - 5 && y <= size - 5)//�k�ױ��y
					who = cmp(who, find_five(x, y, 1, 1));
				if (y <= size - 5 && size - y + 1 >= size - 5)//���ױ��y
					who = cmp(who, find_five(x, y, 1, -1));

				if (who != 0)break;  //���Ĺ�a��h�X
			}
		}
	if (who == 0)cout << "None" << endl;
	if (who == 1)cout << "A wins" << endl;
	if (who == 2)cout << "B wins" << endl;
}