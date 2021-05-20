#include<iostream>
using namespace std;
void find_sum_equal_product(int);
int ten_pow(int);

int main()
{
	int n;
	cin >> n;
	find_sum_equal_product(ten_pow(n-1));//計算及輸出結果
	return 0;
}

int ten_pow(int n) {
	int tenP = 1;
	//計算10的n次方
	for (int i = 0; i < n; i++)tenP *= 10;
	return tenP;
}

void find_sum_equal_product(int end) {
	for (int i = 1; i < end; i++){
		int add = 0;//加
		int product = 1;//乘
		int tmp = i;

		do {
			int digits = tmp % 10;//抓取各位數字
			add += digits;//加項
			product *= digits;//乘項
		} while (tmp /= 10);//將當前數字不斷除以10至0為止

		if (add == product && i % 10 != 0)
			cout << i << endl;//加等於乘就印出
	}
}