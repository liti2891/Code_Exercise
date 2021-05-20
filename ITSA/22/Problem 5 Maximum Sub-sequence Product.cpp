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
		bool zero = false;//�P�_�ѤJ���S��0
		int posRow[100] = { 0 }, navRow[100] = { 0 };//����ƻP�t��Ƥ��}�s��
		int pn = 0, nn = 0;//���t��ƭp��

		int num;
		while (cin >> num) {
			if (num == -999999)break;
			//����ƻP�t��Ƥ��}�s��
			else if (num > 0)posRow[pn++] = num;
			else if (num < 0)navRow[nn++] = num;
			else zero = true;//��J��0�h��true
		}

		//�P�_��J������
		char nxtC = cin.peek();
		while (nxtC == ' ') {
			cin.ignore();
			nxtC = cin.peek();
		}
		if (nxtC == EOF)
			break;

		//�N���t��ư}�C�Ƨ�
		sort(posRow, posRow + pn);
		sort(navRow, navRow + nn);

		//�p�G�S������ơA��J��0�h��X0�A��J�S��0�h��X�̤j�t���
		if (pn == 0) {
			if (!zero)cout << navRow[nn - 1] << endl;
			else cout << 0 << endl;
			continue;
		}

		string product = "1";
		//���������
		for (int i = 0; i < pn; i++)
			product = multiply(product, to_string(posRow[i]));
		//�p�G�t��Ʀ��Ƭ��_�ơA�h�֭��̤j�t���(�t�t�o��)
		if (nn % 2 != 0)nn--;
		for (int i = 0; i < nn; i++)
			product = multiply(product, to_string(navRow[i]));

		cout << product << endl;//�L�X���G
	}
	return 0;
}

string multiply(string num1, string num2) {
	//�P�_���t�A���h���t����K����p��Anum1��num2�P�ɬ��t�h�t�t�o��
	bool nav = false;
	if (num1[0] == '-') { nav = !nav; num1.erase(0, 1); }
	if (num2[0] == '-') { nav = !nav; num2.erase(0, 1); }

	int len1 = num1.length();
	int len2 = num2.length();
	int max_pos = len1 + len2 - 1;//�ۭ���̤j��Ƭ���Ʀ�Ƭۥ[
	vector<int> res(max_pos + 1, 0);//�}�@�Ө����j��vector�x�s�Ʀr
	string m_res;

	//�q�Ӧ�ƶ}�l���y
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
