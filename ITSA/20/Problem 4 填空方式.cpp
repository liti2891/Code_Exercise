#include <iostream>
using namespace std;

//x���h
int factorial(int x) {
	if (x == 1)return x;
	return x * factorial(x - 1);
}
//�զXC_n��m
int C_n_m(int n, int m) {
	return factorial(n) / (factorial(n - m)*factorial(m));
}
//���ƲզXH_n��m
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
		n -= num + 1;//��h�α�����l(num+1�Ů�)
		count++;//�p�ƿ�J������
	}
	//�i�H�N���ʪ���l��n+1�ӡA�i�H�񪺦�l��count+1��
	//�ҥH�p�⭫�ƲզXH(count + 1, n + 1)
	cout << H_n_m(count + 1, n + 1) << endl;
	return 0;
}