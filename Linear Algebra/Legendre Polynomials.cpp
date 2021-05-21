#include <iostream>
#include <iomanip>
using namespace std;

class Arr {
	int m, n;
	double **arr;
public:
	void read() {//輸入1,x,x^2 -1~1取101點 每點間隔0.02
		double x = -1;
		for (int i = 0; i < n; i++, x += 0.02)
			for (int j = 0; j < m; j++)
				arr[i][j] = pow(x, j);
	}
	void show() {//印出結果
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				cout << setw(6) << fixed << setprecision(2) << arr[i][j] << " | ";
			cout << endl;
		}
	}
	void OrthogonalB() {//正交
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
	Arr() :arr(NULL), m(0), n(0) {}//預設建構
	Arr(int mm, int nn) {//配置矩陣大小
		m = mm;
		n = nn;
		arr = new double *[n];
		for (int i = 0; i < n; i++)
			arr[i] = new double[m];
	}
	~Arr() {//解構
		for (int i = 0; i < m; i++)
			delete[] arr[i];
		delete[] arr;
		m = n = 0;
	}
};
int main() {
	Arr u(3, 101);//生成矩陣
	u.read();//輸入u
	cout << "   1   |    x   |   x^2  |" << "輸入" << endl;
	u.show();//印出輸入
	cout << "   1   |    x   | x^2-1/3|" << "結果" << endl;
	u.OrthogonalB();//正交
	u.show();//印出結果


	system("pause");
	return 0;
}