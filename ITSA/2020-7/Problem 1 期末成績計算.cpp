#include <iostream>
#include <iomanip>
#include <stdio.h>
using namespace std;

int main()
{
	int n;
	cin >> n;
	long sumEng = 0, sumMat = 0, sumCal = 0, sumPro = 0, sumAlg = 0;
	//��J�å[�`�U�즨�Z
	for (int i = 0; i < n; i++) {
		long eng, mat, cal, pro, alg;
		cin >> eng >> mat >> cal >> pro >> alg;
		sumEng += eng;
		sumMat += mat;
		sumCal += cal;
		sumPro += pro;
		sumAlg += alg;
	}

	double eps = 1e-9;
	//�p��U�쥭���A�å[�W�@���v�T�ƭ�(���p)���ƨӸѨM�B�I�ƻ~�t
	double aveAll = (sumEng + sumMat + sumCal + sumPro + sumAlg) / double(n * 5) + eps;
	double aveEng = sumEng / double(n) + eps;
	double aveMat = sumMat / double(n) + eps;
	double aveCal = sumCal / double(n) + eps;
	double avePro = sumPro / double(n) + eps;
	double aveAlg = sumAlg / double(n) + eps;
#define METHOD2
#if defined METHOD2
	// printf �B�z Rounding
	printf("%.1lf %.1lf %.1lf %.1lf %.1lf %.1lf\n", aveAll, aveEng, aveMat, aveCal, avePro, aveAlg);
#elif defined METHOD3
	// cout �B�z Rounding
	cout << fixed << setprecision(1) << aveAll << " ";
	cout << aveEng << " ";
	cout << aveMat << " ";
	cout << aveCal << " ";
	cout << avePro << " ";
	cout << aveAlg << endl;
#endif
	return 0;
}

