#include <iostream>
#include <string>
using namespace std;

#define strN 100
string str1, str2;
int c[strN][strN] = { 0 };//�l�ǦC����
int b[strN][strN] = { 0 };//���ʤ�V

void print_lcs(int, int);
int lcs();

int main() {
	cin >> str1 >> str2;
	if (lcs() > 0)//���l�ǦC�N�L�X�̤j���G
		print_lcs(str1.length(), str2.length());
	else {
		cout << "none";
	}
	cout << endl;

	return 0;
}

void print_lcs(int m, int n) {
	if (m == 0 || n == 0)return;
	if (b[m][n] == 1) {
		print_lcs(m - 1, n - 1);
		cout << str1[m - 1];
	}
	else if (b[m][n] == 2)print_lcs(m - 1, n);
	else print_lcs(m, n - 1);
}

int lcs() {
	int m, n;
	m = str1.length();
	n = str2.length();

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (str1[i - 1] == str2[j - 1]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 1;//���W
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
				b[i][j] = 2;//�W
			}
			else {
				c[i][j] = c[i][j - 1];
				b[i][j] = 3;//��
			}
		}
	}
	return c[m][n];
}