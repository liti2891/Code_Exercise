#include <iostream>
using namespace std;

double fln(double);
double fexp(double);
double fabs(double);

int main() {
	double x;
	double n;
	cout << "求出 x 的 n 次根號" << endl;
	while (true)
	{
		cout << "輸入'x n'" << endl;
		cin >> x >> n;
		cout << fexp(1.0 / n * fln(x)) << endl;//x^1/n = exp(1/n*ln(x))
	}
	return 0;
}

double fln(double x) {
	//ln(x)=ln((1+y)/(1-y))
	double y = (x - 1) / (x + 1)*1.0;
	double checkAns;
	double ans = y;

	double i = 1, iy = y;
	do {
		checkAns = ans;
		iy *= y * y;
		i += 2;
		ans += iy / i;//sigma_n(0 to infty){y^(1+n*2)/(1+n*2)}

	} while (fabs(ans - checkAns) > 1e-9);//檢查答案是否收斂

	return ans * 2.0;
}

double fexp(double x) {
	double checkAns;
	double ans = 1;

	double i = 0, ix = 1, fac = 1;
	do {
		checkAns = ans;
		i++;
		ix *= x;
		fac *= i;
		ans += ix / fac;//sigma_n(0 to infty){x^n/n!}
	} while (fabs(ans - checkAns) > 1e-9);//檢查答案是否收斂
	return ans;
}

double fabs(double x) {
	return x > 0 ? x : -x;//取絕對值
}