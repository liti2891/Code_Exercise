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
	void UtoV(int r, Arr &other) {//u�ƻs��v
		for (int i = 0; i < n; i++) {
			arr[i][r] = other.arr[i][r];
		}
	}
	void DelProjW(int r, int w) {//�����e����������
		double mul, mol = 0, den = 0;
		for (int i = 0; i < n; i++) {
			mol += arr[i][r] * arr[i][w];// <Ur,Vw>
			den += arr[i][w] * arr[i][w];// ||Vw||^2
		}
		mul = mol / den;
		for (int i = 0; i < n; i++) {
			arr[i][r] -= arr[i][w] * mul;
		}
	}
	Arr() :arr(NULL), m(0), n(0) {}//�w�]�غc
	Arr(int mm, int nn) {//�t�m�x�}�j�p
		m = mm;
		n = nn;
		arr = new double *[n];
		for (int i = 0; i < n; i++) {
			arr[i] = new double[m];
		}
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
	cout << "�ݥ��椧�V�q" << endl;
	u.show();//�L�X��J
	cout << endl << "�H���椧�V�q" << endl;
	v.UtoV(0, u);//V1=U1
	for (int i = 1; i < m; i++) {
		v.UtoV(i, u);
		for (int j = 0; j < i; j++) {
			v.DelProjW(i, j);
		}
	}
	v.show();//�L�X���G
	system("pause");
	return 0;
}
//��V��J
/*
#include <iostream>
using namespace std;

class Arr {
int m, n;
double **arr;
public:
void read() {//��J�U�Ӱ�
for (int i = 0; i < m; i++)
for (int j = 0; j < n; j++)
cin >> arr[i][j];
}
void show() {//�L�X���G
for (int i = 0; i < m; i++) {
for (int j = 0; j < n; j++)
cout << arr[i][j] << ' ';
cout << endl;
}
}
void UtoV(int r, Arr &other) {//u�ƻs��v
for (int i = 0; i < n; i++) {
arr[r][i] = other.arr[r][i];
}
}
void DelProjW(int r, int w) {//�����e����������
double mul, mol = 0, den = 0;
for (int i = 0; i < n; i++) {
mol += arr[r][i] * arr[w][i];// <Ur,Vw>
den += arr[w][i] * arr[w][i];// ||Vw||^2
}
mul = mol / den;
for (int i = 0; i < n; i++) {
arr[r][i] -= arr[w][i] * mul;
}
}
Arr() :arr(NULL), m(0), n(0) {}//�w�]�غc
Arr(int mm, int nn) {//�t�m�x�}�j�p
m = mm;
n = nn;
arr = new double *[m];
for (int i = 0; i < m; i++) {
arr[i] = new double[n];
}
}
~Arr() {//�Ѻc
for (int i = 0; i < n; i++)
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
v.UtoV(0, u);//V1=U1
for (int i = 1; i < m; i++) {
v.UtoV(i, u);
for (int j = 0; j < i; j++) {
v.DelProjW(i, j);
}
}
v.show();
system("pause");
return 0;
}*/