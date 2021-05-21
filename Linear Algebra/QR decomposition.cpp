#include <iostream>
#include <iomanip>
using namespace std;

class Arr {
	int m, n;
	double **arr;
public:
	void read() {//��J�U�Ӱ�
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				cin >> arr[i][j];
	}
	void show() {//�L�X���G
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				cout << setw(6) << fixed << setprecision(3) << arr[i][j] << " | ";
			cout << endl;
		}
	}
	void UtoV(Arr &other) {//u�ƻs��v
		for (int i = 0; i < n; i++) 
			for (int j = 0; j < m; j++)
				arr[i][j] = other.arr[i][j];
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
	void OrthonormalB() {//���h
		for (int i = 0; i < m; i++) {
			double Vn = 0;
			for (int j = 0; j < n; j++)// ||V||^2
				Vn += arr[j][i] * arr[j][i];
			for (int j = 0; j < n; j++)
				arr[j][i] /= sqrt(Vn);// Vn/||Vn||
		}
	}
	void QR_R(Arr &otherU, Arr &otherQ) {//QR����-R�x�}
		for (int i = 0; i < m; i++) 
			for (int j = 0; j < n; j++) {
			double tmp = 0;
				if (j <= i) 
					for (int k = 0; k < n; k++)// tmp=<u,q>
						tmp += otherU.arr[k][i] * otherQ.arr[k][j];
					arr[j][i] = tmp;				
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
	int m, n;
	cin >> m >> n;//��Jm, n�j�p
	Arr u(m, n), v(m, n);//�ͦ�u,v�x�}
	u.read();//��Ju
	cout << "��J�x�}" << endl;
	u.show();//�L�X��J
	v.UtoV(u);//U�ƻs��V
	v.OrthogonalB();//����
	v.OrthonormalB();//���h
	Arr R(m, n);//�ͦ�R�x�}
	R.QR_R(u, v);//��U,V���XR�x�}
	cout << endl << "Q�x�}" << endl;
	v.show();//�L�X���G
	cout << endl << "R�x�}" << endl;
	R.show();
	system("pause");
	return 0;
}