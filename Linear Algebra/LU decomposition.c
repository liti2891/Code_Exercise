#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

int nByn;
float **matrix;
float **matI;

int change(int, int);
int swap(int *, int *);
void LU(int);

int swap(int *x, int*y) {		//交換位址
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

int change(int x, int y) {		//找非0列交換
	int i;
	for (i = x; i < nByn; i++) {
		if (matrix[i][y] != 0) {
			swap(&matrix[x], &matrix[i]);
			i--;
			break;
		}
	}
	return i;
}

void LU(int cou) {		//LU分解
	int check=0;
	if (cou < nByn) {
		if (matrix[cou][cou] != 0) {		//產生領導壹
			float exp = matrix[cou][cou];
			for (int i = 0; i < nByn; i++)
				matrix[cou][i] /= exp;

			float *mat = (float *)malloc(cou * sizeof(float));
			for (int i = cou + 1, k = cou; i < nByn; i++, k++) {		//做列運算將其他列弄為0
				mat[k] = matrix[i][cou];
				for (int j = 0; j < nByn; j++)
					matrix[i][j] -= matrix[cou][j] * mat[k];
			}
			LU(cou + 1);		//重複前面動作直到完成上三角矩陣

			if (check)swap(matI[cou], matI[check]);
			for (int i = nByn - 1, k = nByn - 2; i > cou; i--, k--) {		//對單位矩陣做反向列運算
				for (int j = 0; j < nByn; j++)
					matI[i][j] += matI[cou][j] * mat[k];
			}
			for (int i = 0; i <= cou; i++)		//對單位矩陣乘上exp
				matI[cou][i] *= exp;
		}
		else {
			check = change(cou, cou);	//遇到0列就交換
			LU(cou);
		}
	}
}

int main() {
	
	scanf("%d", &nByn);	//輸入矩陣大小
	
	matrix = (float **)malloc(nByn * sizeof(float *));
	matI = (float **)malloc(nByn * sizeof(float *));
	for (int i = 0; i < nByn; i++) {
		matrix[i] = (float *)malloc(nByn * sizeof(float));
		matI[i] = (float *)malloc(nByn * sizeof(float));
	}

	for(int i=0;i<nByn;i++)		//輸入矩陣及產生單位矩陣
		for (int j = 0; j < nByn; j++) {
			scanf("%f", &matrix[i][j]);
			matI[i][j] = 0;
			if (i == j)matI[i][j] = 1;
		}
	LU(0);		//LU分解
	
	for (int i = 0; i < nByn; i++) {		//輸出
		for (int j = 0; j < nByn; j++)
			printf("%6.1f", matI[i][j]);
		printf(" | ");
		for (int j = 0; j < nByn; j++)
			printf("%6.1f", matrix[i][j]);
		printf("\n");
	}
	
	system("pause");
	return 0;
}