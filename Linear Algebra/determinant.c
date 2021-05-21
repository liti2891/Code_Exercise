#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

void one(int, int);
void elimination(int, int);
int change(int, int);
int swap(int *, int *);

int row, column;
float **matrix;
float determinant=1;
int	Value, item = 0;

void one(int x, int y) {		//���X����
	item++;
	determinant *= y;
	for (int i = 0; i < column; i++) {
		matrix[x][i] /= y;
	}
}

void elimination(int x, int y) {		//���C�B��
	float tmp;
	for (int i = x + 1; i < row; i++) {		
		tmp = matrix[i][y];
		for (int j = y; j < column; j++) {
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
	determinant *= -1;
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

	matrix = (float **)malloc(row * sizeof(float *));		//�t�mrow*column�x�}�j�p
	for (i = 0; i < column; i++) {
		matrix[i] = (float *)malloc(column * sizeof(float));
	}

	for (i = 0; i < row; i++) {			//��J�U��U�C�Y��
		for (j = 0; j < column; j++) {
			scanf("%f", &matrix[i][j]);
		}
	}

	i = 0; j = 0;
	while (i < row) {
		if (column - Value == item)break;		//�����ᤣ�p��

		if (matrix[i][j] != 0) {			//�ˬd(i,j)�O�_��0
			one(i, matrix[i][j]);			//���X����
			elimination(i, j);				//���C�B��
			i++; j++;
		}
		else {
			check = change(i, j);		//(i,j)��0�V�U��D0�C�洫
		}

		if (check >= row)			//(i,j)�U��L�D0�C(i,j+1)
			j++;
	}

	printf("%f", determinant);

	system("pause");
	return 0;
}