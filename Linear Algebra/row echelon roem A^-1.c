#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

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
	for (i = 0; i < column*2; i++) {
		matrix[x][i] /= y;
	}
}
void elimination(int x, int y) {		//�ϫe�ɳ��W�U���s
	int i, j, tmp;
	for (i = x + 1; i < row; i++) {		//�U�b��
		tmp = matrix[i][y];
		for (j = y; j < column*2; j++) {
			matrix[i][j] -= matrix[x][j] * tmp;
		}
	}
	for (i = x - 1; i >= 0; i--) {		//�W�b��
		tmp = matrix[i][y];
		for (j = y; j < column*2; j++) {
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
	int i, j, check = 0,n;
	scanf("%d", &n);
	row = n; column = n;Value = n;

	matrix = (float **)malloc(row * sizeof(float *));		//�t�mrow*column�x�}�j�p
	for (i = 0; i < column+n; i++) {
		matrix[i] = (float *)malloc(column+n * sizeof(float));
	}
	for (i = 0; i < row; i++)			//�}�C��l��
		for (j = 0; j < column + n; j++)
			matrix[i][j] = 0;
	for (i = 0; i < row; i++) {			//��J�U��U�C�Y��
		for (j = 0; j < column; j++) {
			scanf("%f", &matrix[i][j]);
		}
	}
	for (i = 0; i < row; i++) {
		matrix[i][i + 4] = 1;
	}

	printf("��J�ӷ�\n");
	for (i = 0; i < row; i++) {			//��X�ӷ�	
		for (j = 0; j < column; j++) {
			printf("%7.1f ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	i = 0; j = 0;

	while (i < row) {
		if (column+n - Value == item)break;		//�����ᤣ�p��

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

	printf("��J���ϯx�}(�|�ˤ��J�p���I��T��)\n");
	for (i = 0; i < row; i++) {			//��X���G
		for (j = n; j < column+n; j++) {
			printf("%7.3f ", matrix[i][j]);
		}
		printf("\n");
	}

	system("pause");
	return 0;
}