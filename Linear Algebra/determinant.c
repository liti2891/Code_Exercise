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

void one(int x, int y) {		//提出倍數
	item++;
	determinant *= y;
	for (int i = 0; i < column; i++) {
		matrix[x][i] /= y;
	}
}

void elimination(int x, int y) {		//做列運算
	float tmp;
	for (int i = x + 1; i < row; i++) {		
		tmp = matrix[i][y];
		for (int j = y; j < column; j++) {
			matrix[i][j] -= matrix[x][j] * tmp;
		}
	}
}

int swap(int *x, int*y) {		//交換位址
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

int change(int x, int y) {		//找非0列交換
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

	scanf("%d*%d", &row, &column);			//輸入列*行

	matrix = (float **)malloc(row * sizeof(float *));		//配置row*column矩陣大小
	for (i = 0; i < column; i++) {
		matrix[i] = (float *)malloc(column * sizeof(float));
	}

	for (i = 0; i < row; i++) {			//輸入各行各列係數
		for (j = 0; j < column; j++) {
			scanf("%f", &matrix[i][j]);
		}
	}

	i = 0; j = 0;
	while (i < row) {
		if (column - Value == item)break;		//等號後不計算

		if (matrix[i][j] != 0) {			//檢查(i,j)是否為0
			one(i, matrix[i][j]);			//提出倍數
			elimination(i, j);				//做列運算
			i++; j++;
		}
		else {
			check = change(i, j);		//(i,j)為0向下找非0列交換
		}

		if (check >= row)			//(i,j)下方無非0列(i,j+1)
			j++;
	}

	printf("%f", determinant);

	system("pause");
	return 0;
}