#include <iostream>
using namespace std;

int find_step(int N) {
	if (N == 1)return 0;//�p�G�I��1�N�^��0��
	if (N % 2 == 0)return find_step(N / 2) + 1;//�C���I�sfind_step���榸��+1
	else {
		int addN = find_step(N + 1) + 1;
		int decN = find_step(N - 1) + 1;
		return addN < decN ? addN : decN;//���N+1��N-1�����ƽ֤֨ÿ�X
	}
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int N;
		//��JN�ο�X�B�J��
		cin >> N;
		cout << find_step(N) << endl;
	}

	return 0;
}