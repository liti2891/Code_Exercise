#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

int nByn;
float **matrix;
float **matI;

int change(int, int);
int swap(int *, int *);
void LU(int);

int swap(int *x, int*y) {		//�洫��}
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

int change(int x, int y) {		//��D0�C�洫
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

void LU(int cou) {		//LU����
	int check=0;
	if (cou < nByn) {
		if (matrix[cou][cou] != 0) {		//���ͻ�ɳ�
			float exp = matrix[cou][cou];
			for (int i = 0; i < nByn; i++)
				matrix[cou][i] /= exp;

			float *mat = (float *)malloc(cou * sizeof(float));
			for (int i = cou + 1, k = cou; i < nByn; i++, k++) {		//���C�B��N��L�C�ˬ�0
				mat[k] = matrix[i][cou];
				for (int j = 0; j < nByn; j++)
					matrix[i][j] -= matrix[cou][j] * mat[k];
			}
			LU(cou + 1);		//���ƫe���ʧ@���짹���W�T���x�}

			if (check)swap(matI[cou], matI[check]);
			for (int i = nByn - 1, k = nByn - 2; i > cou; i--, k--) {		//����x�}���ϦV�C�B��
				for (int j = 0; j < nByn; j++)
					matI[i][j] += matI[cou][j] * mat[k];
			}
			for (int i = 0; i <= cou; i++)		//����x�}���Wexp
				matI[cou][i] *= exp;
		}
		else {
			check = change(cou, cou);	//�J��0�C�N�洫
			LU(cou);
		}
	}
}

int main() {
	
	scanf("%d", &nByn);	//��J�x�}�j�p
	
	matrix = (float **)malloc(nByn * sizeof(float *));
	matI = (float **)malloc(nByn * sizeof(float *));
	for (int i = 0; i < nByn; i++) {
		matrix[i] = (float *)malloc(nByn * sizeof(float));
		matI[i] = (float *)malloc(nByn * sizeof(float));
	}

	for(int i=0;i<nByn;i++)		//��J�x�}�β��ͳ��x�}
		for (int j = 0; j < nByn; j++) {
			scanf("%f", &matrix[i][j]);
			matI[i][j] = 0;
			if (i == j)matI[i][j] = 1;
		}
	LU(0);		//LU����
	
	for (int i = 0; i < nByn; i++) {		//��X
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