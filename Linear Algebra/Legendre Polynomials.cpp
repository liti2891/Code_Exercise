#include <iostream>
#include <iomanip>
using namespace std;

class Arr {
	int m, n;
	double **arr;
public:
	void read() {//��J1,x,x^2 -1~1��101�I �C�I���j0.02
		double x = -1;
		for (int i = 0; i < n; i++, x += 0.02)
			for (int j = 0; j < m; j++)
				arr[i][j] = pow(x, j);
	}
	void show() {//�L�X���G
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				cout << setw(6) << fixed << setprecision(2) << arr[i][j] << " | ";
			cout << endl;
		}
	}
	void OrthogonalB() {//����
		for (int i = 1; i < m; i++)
			for (int j = 0; j < i; j++) {
				double mol = 0, den = 0;
				for (int k = 0; k < n; k++) {
					mol += arr[k][i] * arr[k][j];// <U,V>
					den += arr[k][j] * arr[k][j];// ||V||^2
				}
				double mul = mol / den;
				for (int k = 0; k < n; k++) //U-projwU
					arr[k][i] -= arr[k][j] * mul;
			}
	}
	Arr() :arr(NULL), m(0), n(0) {}//�w�]�غc
	Arr(int mm, int nn) {//�t�m�x�}�j�p
		m = mm;
		n = nn;
		arr = new double *[n];
		for (int i = 0; i < n; i++)
			arr[i] = new double[m];
	}
	~Arr() {//�Ѻc
		for (int i = 0; i < m; i++)
			delete[] arr[i];
		delete[] arr;
		m = n = 0;
	}
};
int main() {
	Arr u(3, 101);//�ͦ��x�}
	u.read();//��Ju
	cout << "   1   |    x   |   x^2  |" << "��J" << endl;
	u.show();//�L�X��J
	cout << "   1   |    x   | x^2-1/3|" << "���G" << endl;
	u.OrthogonalB();//����
	u.show();//�L�X���G


	system("pause");
	return 0;
}