#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

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
	for (i = 0; i < column*2; i++) {
		matrix[x][i] /= y;
	}
}
void elimination(int x, int y) {		//使前導壹上下為零
	int i, j, tmp;
	for (i = x + 1; i < row; i++) {		//下半部
		tmp = matrix[i][y];
		for (j = y; j < column*2; j++) {
			matrix[i][j] -= matrix[x][j] * tmp;
		}
	}
	for (i = x - 1; i >= 0; i--) {		//上半部
		tmp = matrix[i][y];
		for (j = y; j < column*2; j++) {
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
	int i, j, check = 0,n;
	scanf("%d", &n);
	row = n; column = n;Value = n;

	matrix = (float **)malloc(row * sizeof(float *));		//配置row*column矩陣大小
	for (i = 0; i < column+n; i++) {
		matrix[i] = (float *)malloc(column+n * sizeof(float));
	}
	for (i = 0; i < row; i++)			//陣列初始化
		for (j = 0; j < column + n; j++)
			matrix[i][j] = 0;
	for (i = 0; i < row; i++) {			//輸入各行各列係數
		for (j = 0; j < column; j++) {
			scanf("%f", &matrix[i][j]);
		}
	}
	for (i = 0; i < row; i++) {
		matrix[i][i + 4] = 1;
	}

	printf("輸入來源\n");
	for (i = 0; i < row; i++) {			//輸出來源	
		for (j = 0; j < column; j++) {
			printf("%7.1f ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	i = 0; j = 0;

	while (i < row) {
		if (column+n - Value == item)break;		//等號後不計算

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

	printf("輸入之反矩陣(四捨五入小數點後三位)\n");
	for (i = 0; i < row; i++) {			//輸出結果
		for (j = n; j < column+n; j++) {
			printf("%7.3f ", matrix[i][j]);
		}
		printf("\n");
	}

	system("pause");
	return 0;
}