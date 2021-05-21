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

void one(int x, int y) {		//產生前導壹
	int i;
	item++;
	for (i = 0; i < column; i++) {
		matrix[x][i] /= y;
	}
}
void elimination(int x, int y) {		//使前導壹上下為零
	int i, j, tmp;
	for (i = x + 1; i < row; i++) {		//下半部
		tmp = matrix[i][y];
		for (j = y; j < column; j++) {
			matrix[i][j] -= matrix[x][j] * tmp;
		}
	}
	for (i = x - 1; i >= 0; i--) {		//上半部
		tmp = matrix[i][y];
		for (j = y; j < column; j++) {
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
	scanf("%d", &Value);					//輸入等號後有幾行

	matrix = (float **)malloc(row * sizeof(float *));		//配置row*column矩陣大小
	for (i = 0; i < column; i++) {
		matrix[i] = (float *)malloc(column * sizeof(float));
	}

	for (i = 0; i < row; i++) {			//輸入各行各列係數
		for (j = 0; j < column; j++) {
			scanf("%f", &matrix[i][j]);
		}
	}

	for (i = 0; i < row; i++) {			//輸出來源	
		for (j = 0; j < column; j++) {
			if (column - Value == j)printf("|");
			printf("%5.1f ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	i = 0; j = 0;

	while (i < row) {
		if (column - Value == item)break;		//等號後不計算

		if (matrix[i][j] != 0) {			//檢查(i,j)是否為0
			one(i, matrix[i][j]);			//產生前導壹
			elimination(i, j);				//使前導壹上下為0
			i++; j++;
		}
		else {
			check = change(i, j);		//(i,j)為0向下找非0列交換
		}

		if (check >= row)			//(i,j)下方無非0列(i,j+1)
			j++;
	}

	for (i = 0; i < row; i++) {			//輸出結果
		for (j = 0; j < column; j++) {
			if (column - Value == j)printf("|");
			printf("%5.1f ", matrix[i][j]);
		}
		printf("\n");
	}

	system("pause");
	return 0;
}