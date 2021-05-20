#include <iostream>
using namespace std;

//x階層
int factorial(int x) {
	if (x == 1)return x;
	return x * factorial(x - 1);
}
//組合C_n取m
int C_n_m(int n, int m) {
	return factorial(n) / (factorial(n - m)*factorial(m));
}
//重複組合H_n取m
int H_n_m(int n, int m) {
	return C_n_m(n + m - 1, n - 1);
}
int main() {
	int n;
	int num;
	int count = 0;

	cin >> n;
	while (cin >> num)
	{
		n -= num + 1;//減去用掉的格子(num+1空格)
		count++;//計數輸入的次數
	}
	//可隨意移動的格子有n+1個，可以放的位子有count+1個
	//所以計算重複組合H(count + 1, n + 1)
	cout << H_n_m(count + 1, n + 1) << endl;
	return 0;
}