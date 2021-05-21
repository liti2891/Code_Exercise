#include <iostream>
#include <iomanip>
using namespace std;

class Arr {
	int m, n;
	double **arr;
public:
	void read() {//輸入各個基底
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				cin >> arr[i][j];
	}
	void show() {//印出結果
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				cout << setw(6) << fixed << setprecision(3) << arr[i][j] << " | ";
			cout << endl;
		}
	}
	void UtoV(Arr &other) {//u複製到v
		for (int i = 0; i < n; i++) 
			for (int j = 0; j < m; j++)
				arr[i][j] = other.arr[i][j];
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
	void OrthonormalB() {//正則
		for (int i = 0; i < m; i++) {
			double Vn = 0;
			for (int j = 0; j < n; j++)// ||V||^2
				Vn += arr[j][i] * arr[j][i];
			for (int j = 0; j < n; j++)
				arr[j][i] /= sqrt(Vn);// Vn/||Vn||
		}
	}
	void QR_R(Arr &otherU, Arr &otherQ) {//QR分解-R矩陣
		for (int i = 0; i < m; i++) 
			for (int j = 0; j < n; j++) {
			double tmp = 0;
				if (j <= i) 
					for (int k = 0; k < n; k++)// tmp=<u,q>
						tmp += otherU.arr[k][i] * otherQ.arr[k][j];
					arr[j][i] = tmp;				
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
	int m, n;
	cin >> m >> n;//輸入m, n大小
	Arr u(m, n), v(m, n);//生成u,v矩陣
	u.read();//輸入u
	cout << "輸入矩陣" << endl;
	u.show();//印出輸入
	v.UtoV(u);//U複製到V
	v.OrthogonalB();//正交
	v.OrthonormalB();//正則
	Arr R(m, n);//生成R矩陣
	R.QR_R(u, v);//用U,V做出R矩陣
	cout << endl << "Q矩陣" << endl;
	v.show();//印出結果
	cout << endl << "R矩陣" << endl;
	R.show();
	system("pause");
	return 0;
}