#include <iostream>
#include <cstdlib>
#include <thread>
#include <highgui.h>
#include <opencv.hpp>

using namespace std;
using namespace cv;

#define NUM 1000		//資料筆數
#define MAXIMUM 200		//資料最大值，最小值為0
#define WIDTH 1			//畫圖資料寬度(pixel)
#define INTERVAL 0		//畫圖資料間距(pixel)
#define DELAY 1			//畫圖時間間隔
//#define WINDOWSIZE	//是否要自動Resize畫布

Mat QuicksortImg;		//快速排序法畫布
Mat MergesortImg;		//合併排序法畫布

void swap(int *, int *);//交換

//快速排序法
void Quicksort(int *, int, int);
int Partition(int *, int, int);

//合併排序法
void Mergesort(int *, int, int);
void Merge(int *, int, int, int);

//畫圖
void QuicksortDraw(int *, int, int, int, int);
void MergesortDraw(int *, int, int, int);

int main() {
	//宣告2組整數陣列，大小為NUM，分別給快速/合併排序使用
	int *QrList = new int[NUM];
	int *MrList = new int[NUM];

	//產生亂數陣列
	srand(0);//固定亂數種子
	printf("initList：\n");
	for (int i = 0; i < NUM; i++) {
		QrList[i] = MrList[i] = rand() % MAXIMUM;//[0,MAXIMUM)
		printf("%d,", QrList[i]);
	}
	printf("\n\n");


#ifdef WINDOWSIZE
	namedWindow("initImg", CV_WINDOW_NORMAL);
#else
	resizeWindow("initImg", Size(NUM*(WIDTH + INTERVAL), MAXIMUM));
#endif

	//顯示初始資料順序
	Mat initImg = Mat::zeros(Size(NUM*(WIDTH + INTERVAL), MAXIMUM), CV_8UC3);
	CvScalar color = CV_RGB(255, 255, 255);
	for (int k = 0; k < NUM; k++)
		rectangle(initImg, Point(k*(INTERVAL + WIDTH), MAXIMUM - QrList[k]), Point(k*(INTERVAL + WIDTH) + WIDTH, MAXIMUM), color, CV_FILLED);
	imshow("initImg", initImg);
	printf("Press ENTER to start.\n");
	cvWaitKey(0);
	destroyWindow("initImg");
	printf("GO!\n");


	//快速/合併排序開始執行
	thread QuickThread(Quicksort, QrList, 0, NUM - 1);
	thread MergeThread(Mergesort, MrList, 0, NUM - 1);

	//等待排序
	MergeThread.join();
	QuickThread.join();

	//顯示排序結果
	printf("Quicksort：\n");
	for (int i = 0; i < NUM; i++) {
		printf("%d,", QrList[i]);
	}
	printf("\nMergesort：\n");
	for (int i = 0; i < NUM; i++) {
		printf("%d,", MrList[i]);
	}
	printf("\n\n");

	delete[] QrList;
	delete[] MrList;
	return 0;
}

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void Quicksort(int *List, int Left, int Right) {
	if (Left < Right) {
		int i = Partition(List, Left, Right);//找出樞紐項索引
		Quicksort(List, Left, i - 1);//左邊排序
		Quicksort(List, i + 1, Right);//右邊排序
	}
}
int Partition(int *List, int L, int R) {
	int pivot = List[R];//選擇陣列最後一項為樞紐項的值
	int i = L - 1;//i從當下最左開始

	for (int j = L; j < R; j++) {
		//如果List[j]小於等於樞紐項則將其擺置樞紐項左方
	//QuicksortDraw(List, L, i, j, R);
		if (pivot >= List[j]) {
			i++;
			swap(&List[i], &List[j]);
		}
	}
	swap(&List[R], &List[i + 1]);//將樞紐項放置於當前分割的中間
	QuicksortDraw(List, L, i, R-1, R);

	return (i + 1);
}

void QuicksortDraw(int *List, int L, int i, int j, int R) {
#ifdef WINDOWSIZE
	namedWindow("Quicksort", CV_WINDOW_NORMAL);
#else
	resizeWindow("Quicksort", Size(NUM*(WIDTH + INTERVAL), MAXIMUM));
#endif
	moveWindow("Quicksort", 10, 10);
	QuicksortImg = Mat::zeros(Size(NUM*(WIDTH + INTERVAL), MAXIMUM), CV_8UC3);

	CvScalar color;
	for (int k = 0; k < NUM; k++) {
		//選擇畫筆顏色
		if (k <= L - 1)
			color = CV_RGB(128, 128, 128);//已經排序完成為灰色
		else if (k <= i)
			color = CV_RGB(0, 0, 255);//快速排序法之i為藍色(樞紐項左方)
		else if (k <= j)
			color = CV_RGB(255, 0, 0);//快速排序法之j為紅色(樞紐項右方)
		else if (k == R)
			color = CV_RGB(0, 255, 0);//樞紐項為綠色
		else
			color = CV_RGB(255, 255, 255);//未使用為白色

		rectangle(QuicksortImg, Point(k*(INTERVAL + WIDTH), MAXIMUM - List[k]), Point(k*(INTERVAL + WIDTH) + WIDTH, MAXIMUM), color, CV_FILLED);//畫圖
	}
	imshow("Quicksort", QuicksortImg);//顯示
	cvWaitKey(DELAY);
}

void Mergesort(int *List, int Left, int Right) {
	if (Left < Right) {
		int Cut = (Left + Right) / 2;//計算當前分割中間
		Mergesort(List, Left, Cut);//合併排序切割左邊
		Mergesort(List, Cut + 1, Right);//合併排序切割右邊
		Merge(List, Left, Right, Cut);//合併排序
		MergesortDraw(List, Left, Right, Cut);

	}
}
void Merge(int *List, int p, int q, int c) {
	int n1 = c - p + 1;//當前切割左邊陣列大小
	int n2 = q - c;//當前切割右邊陣列大小
	int* cL = new int[n1];
	int* cR = new int[n2];

	//複製List資料至左右陣列
	memcpy(cL, &List[p], n1 * sizeof(int));
	memcpy(cR, &List[c + 1], n2 * sizeof(int));

	cL[n1] = MAXIMUM;
	cR[n2] = MAXIMUM;

	int i = 0, j = 0;
	for (int k = p; k <= q; k++) {
		//左陣列第i項小於等於右陣列j項則左陣列i項先放入List，反之亦同
		if (cL[i] <= cR[j]) {
			List[k] = cL[i];
			i++;
		}
		else {
			List[k] = cR[j];
			j++;
		}
		
	//MergesortDraw(List, p, q, c);
	}
}
void MergesortDraw(int *List, int L, int R, int C) {
#ifdef WINDOWSIZE
	namedWindow("Mergesort", CV_WINDOW_NORMAL);
#else
	resizeWindow("Mergesort", Size(NUM*(WIDTH + INTERVAL), MAXIMUM));
#endif
	moveWindow("Mergesort", 10, 50 + MAXIMUM + 5);
	MergesortImg = Mat::zeros(Size(NUM*(WIDTH + INTERVAL), MAXIMUM), CV_8UC3);

	CvScalar color;
	for (int k = 0; k < NUM; k++) {
		//選取畫筆顏色
		if (k >= L && k <= C)
			color = CV_RGB(0, 255, 0);//左陣列為綠色
		else if (k > C && k <= R)
			color = CV_RGB(255, 0, 0);//右陣列為紅色
		else
			color = CV_RGB(255, 255, 255);//未使用為白色

		rectangle(MergesortImg, Point(k*(INTERVAL + WIDTH), MAXIMUM - List[k]), Point(k*(INTERVAL + WIDTH) + WIDTH, MAXIMUM), color, CV_FILLED);
	}
	imshow("Mergesort", MergesortImg);
	cvWaitKey(DELAY);
}