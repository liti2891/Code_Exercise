#include<iostream>
using namespace std;
void find_sum_equal_product(int);
int ten_pow(int);

int main()
{
	int n;
	cin >> n;
	find_sum_equal_product(ten_pow(n-1));//�p��ο�X���G
	return 0;
}

int ten_pow(int n) {
	int tenP = 1;
	//�p��10��n����
	for (int i = 0; i < n; i++)tenP *= 10;
	return tenP;
}

void find_sum_equal_product(int end) {
	for (int i = 1; i < end; i++){
		int add = 0;//�[
		int product = 1;//��
		int tmp = i;

		do {
			int digits = tmp % 10;//����U��Ʀr
			add += digits;//�[��
			product *= digits;//����
		} while (tmp /= 10);//�N��e�Ʀr���_���H10��0����

		if (add == product && i % 10 != 0)
			cout << i << endl;//�[���󭼴N�L�X
	}
}