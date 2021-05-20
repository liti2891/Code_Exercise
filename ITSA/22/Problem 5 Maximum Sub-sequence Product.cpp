#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

string multiply(string, string);
string smax(string, string);
int main() {
	while (1) {
		/*int inRow[100];
		int num;
		int n = 0;
		while (cin >> num) {
			if (num == -999999)break;
			inRow[n++] = num;
		}

		string product;
		string ans = "-999999";
		for (int i = 0; i < n; i++) {
			product = "1";
			for (int k = i; k < n; k++)
				product = multiply(product, to_string(inRow[k]));
			ans = smax(ans, product);
		}
		cout << ans << endl;*/
		bool zero = false;//判斷書入有沒有0
		int posRow[100] = { 0 }, navRow[100] = { 0 };//正整數與負整數分開存放
		int pn = 0, nn = 0;//正負整數計數

		int num;
		while (cin >> num) {
			if (num == -999999)break;
			//正整數與負整數分開存放
			else if (num > 0)posRow[pn++] = num;
			else if (num < 0)navRow[nn++] = num;
			else zero = true;//輸入有0則為true
		}

		//判斷輸入結束用
		char nxtC = cin.peek();
		while (nxtC == ' ') {
			cin.ignore();
			nxtC = cin.peek();
		}
		if (nxtC == EOF)
			break;

		//將正負整數陣列排序
		sort(posRow, posRow + pn);
		sort(navRow, navRow + nn);

		//如果沒有正整數，輸入有0則輸出0，輸入沒有0則輸出最大負整數
		if (pn == 0) {
			if (!zero)cout << navRow[nn - 1] << endl;
			else cout << 0 << endl;
			continue;
		}

		string product = "1";
		//先乘正整數
		for (int i = 0; i < pn; i++)
			product = multiply(product, to_string(posRow[i]));
		//如果負整數次數為奇數，則少乘最大負整數(負負得正)
		if (nn % 2 != 0)nn--;
		for (int i = 0; i < nn; i++)
			product = multiply(product, to_string(navRow[i]));

		cout << product << endl;//印出結果
	}
	return 0;
}

string multiply(string num1, string num2) {
	//判斷正負，先去除負號方便後續計算，num1及num2同時為負則負負得正
	bool nav = false;
	if (num1[0] == '-') { nav = !nav; num1.erase(0, 1); }
	if (num2[0] == '-') { nav = !nav; num2.erase(0, 1); }

	int len1 = num1.length();
	int len2 = num2.length();
	int max_pos = len1 + len2 - 1;//相乘後最大位數為兩數位數相加
	vector<int> res(max_pos + 1, 0);//開一個足夠大的vector儲存數字
	string m_res;

	//從個位數開始掃描
	for (int i = len2 - 1; i > -1; i--) {
		for (int j = len1 - 1; j > -1; j--) {
			int pos_low = i + j + 1;
			int pos_high = i + j;

			int m = (num2[i] - '0') * (num1[j] - '0') + res[pos_high] * 10 + res[pos_low];
			res[pos_high] = m / 10;
			res[pos_low] = m % 10;

			if (pos_high < max_pos && res[pos_high] != 0) max_pos = pos_high;
			else if (pos_low < max_pos && res[pos_low] != 0) max_pos = pos_low;
		}
	}

	for (int k = max_pos; k < (int)res.size(); k++) {
		m_res.push_back(res[k] + '0');
	}
	string navStr = "-";

	if (nav) {
		navStr.append(m_res);
		return navStr;
	}
	return m_res;
}

string smax(string num1, string num2) {
	bool nav;
	int len1 = num1.length();
	int len2 = num2.length();
	if (num1[0] != '-'&&num2[0] != '-') nav = false;
	else if (num1[0] == '-'&&num2[0] == '-') nav = true;
	else if (num1[0] != '-'&&num2[0] == '-') return num1;
	else if (num1[0] == '-'&&num2[0] != '-') return num2;

	if (len1 > len2)return !nav ? num1 : num2;
	else if (len1 < len2)return !nav ? num2 : num1;
	else {
		int start = 1 * nav;
		for (int i = start; i < len1; i++) {
			if (num1[i] > num2[i])return !nav ? num1 : num2;
			else if (num1[i] < num2[i])return !nav ? num2 : num1;
		}
	}
	return num1;
}
