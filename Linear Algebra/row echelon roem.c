#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void one(int, int);
void elimination(int, int);
int change(int, int);
int swap(int *, int *);

int row, column;
float **matrix;
int	Value, item = 0;

void one(int x, int y) {		//���ͫe�ɳ�
	int i;
	item++;
	for (i = 0; i < column; i++) {
		matrix[x][i] /= y;
	}
}
void elimination(int x, int y) {		//�ϫe�ɳ��W�U���s
	int i, j, tmp;
	for (i = x + 1; i < row; i++) {		//�U�b��
		tmp = matrix[i][y];
		for (j = y; j < column; j++) {
			matrix[i][j] -= matrix[x][j] * tmp;
		}
	}
	for (i = x - 1; i >= 0; i--) {		//�W�b��
		tmp = matrix[i][y];
		for (j = y; j < column; j++) {
			matrix[i][j] -= matrix[x][j] * tmp;
		}
	}
}

int swap(int *x, int*y) {		//�洫��}
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

int change(int x, int y) {		//��D0�C�洫
	int i;
	for (i = x; i < row; i++) {
		if (matrix[i][y] != 0) {
			swap(&matrix[x], &matrix[i]);
			i--;
			break;
		}
	}
	return i;
}

int main() {
	int i, j, check = 0;

	scanf("%d*%d", &row, &column);			//��J�C*��
	scanf("%d", &Value);					//��J�����ᦳ�X��

	matrix = (float **)malloc(row * sizeof(float *));		//�t�mrow*column�x�}�j�p
	for (i = 0; i < column; i++) {
		matrix[i] = (float *)malloc(column * sizeof(float));
	}

	for (i = 0; i < row; i++) {			//��J�U��U�C�Y��
		for (j = 0; j < column; j++) {
			scanf("%f", &matrix[i][j]);
		}
	}

	for (i = 0; i < row; i++) {			//��X�ӷ�	
		for (j = 0; j < column; j++) {
			if (column - Value == j)printf("|");
			printf("%5.1f ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	i = 0; j = 0;

	while (i < row) {
		if (column - Value == item)break;		//�����ᤣ�p��

		if (matrix[i][j] != 0) {			//�ˬd(i,j)�O�_��0
			one(i, matrix[i][j]);			//���ͫe�ɳ�
			elimination(i, j);				//�ϫe�ɳ��W�U��0
			i++; j++;
		}
		else {
			check = change(i, j);		//(i,j)��0�V�U��D0�C�洫
		}

		if (check >= row)			//(i,j)�U��L�D0�C(i,j+1)
			j++;
	}

	for (i = 0; i < row; i++) {			//��X���G
		for (j = 0; j < column; j++) {
			if (column - Value == j)printf("|");
			printf("%5.1f ", matrix[i][j]);
		}
		printf("\n");
	}

	system("pause");
	return 0;
}