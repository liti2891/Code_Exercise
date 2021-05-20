#include <iostream>
#include <cstdlib>
#include <thread>
#include <highgui.h>
#include <opencv.hpp>

using namespace std;
using namespace cv;

#define NUM 1000		//��Ƶ���
#define MAXIMUM 200		//��Ƴ̤j�ȡA�̤p�Ȭ�0
#define WIDTH 1			//�e�ϸ�Ƽe��(pixel)
#define INTERVAL 0		//�e�ϸ�ƶ��Z(pixel)
#define DELAY 1			//�e�Ϯɶ����j
//#define WINDOWSIZE	//�O�_�n�۰�Resize�e��

Mat QuicksortImg;		//�ֳt�ƧǪk�e��
Mat MergesortImg;		//�X�ֱƧǪk�e��

void swap(int *, int *);//�洫

//�ֳt�ƧǪk
void Quicksort(int *, int, int);
int Partition(int *, int, int);

//�X�ֱƧǪk
void Mergesort(int *, int, int);
void Merge(int *, int, int, int);

//�e��
void QuicksortDraw(int *, int, int, int, int);
void MergesortDraw(int *, int, int, int);

int main() {
	//�ŧi2�վ�ư}�C�A�j�p��NUM�A���O���ֳt/�X�ֱƧǨϥ�
	int *QrList = new int[NUM];
	int *MrList = new int[NUM];

	//���Ͷüư}�C
	srand(0);//�T�w�üƺؤl
	printf("initList�G\n");
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

	//��ܪ�l��ƶ���
	Mat initImg = Mat::zeros(Size(NUM*(WIDTH + INTERVAL), MAXIMUM), CV_8UC3);
	CvScalar color = CV_RGB(255, 255, 255);
	for (int k = 0; k < NUM; k++)
		rectangle(initImg, Point(k*(INTERVAL + WIDTH), MAXIMUM - QrList[k]), Point(k*(INTERVAL + WIDTH) + WIDTH, MAXIMUM), color, CV_FILLED);
	imshow("initImg", initImg);
	printf("Press ENTER to start.\n");
	cvWaitKey(0);
	destroyWindow("initImg");
	printf("GO!\n");


	//�ֳt/�X�ֱƧǶ}�l����
	thread QuickThread(Quicksort, QrList, 0, NUM - 1);
	thread MergeThread(Mergesort, MrList, 0, NUM - 1);

	//���ݱƧ�
	MergeThread.join();
	QuickThread.join();

	//��ܱƧǵ��G
	printf("Quicksort�G\n");
	for (int i = 0; i < NUM; i++) {
		printf("%d,", QrList[i]);
	}
	printf("\nMergesort�G\n");
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
		int i = Partition(List, Left, Right);//��X�ϯö�����
		Quicksort(List, Left, i - 1);//����Ƨ�
		Quicksort(List, i + 1, Right);//�k��Ƨ�
	}
}
int Partition(int *List, int L, int R) {
	int pivot = List[R];//��ܰ}�C�̫�@�����ϯö�����
	int i = L - 1;//i�q��U�̥��}�l

	for (int j = L; j < R; j++) {
		//�p�GList[j]�p�󵥩�ϯö��h�N���\�m�ϯö�����
	//QuicksortDraw(List, L, i, j, R);
		if (pivot >= List[j]) {
			i++;
			swap(&List[i], &List[j]);
		}
	}
	swap(&List[R], &List[i + 1]);//�N�ϯö���m���e���Ϊ�����
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
		//��ܵe���C��
		if (k <= L - 1)
			color = CV_RGB(128, 128, 128);//�w�g�Ƨǧ������Ǧ�
		else if (k <= i)
			color = CV_RGB(0, 0, 255);//�ֳt�ƧǪk��i���Ŧ�(�ϯö�����)
		else if (k <= j)
			color = CV_RGB(255, 0, 0);//�ֳt�ƧǪk��j������(�ϯö��k��)
		else if (k == R)
			color = CV_RGB(0, 255, 0);//�ϯö������
		else
			color = CV_RGB(255, 255, 255);//���ϥά��զ�

		rectangle(QuicksortImg, Point(k*(INTERVAL + WIDTH), MAXIMUM - List[k]), Point(k*(INTERVAL + WIDTH) + WIDTH, MAXIMUM), color, CV_FILLED);//�e��
	}
	imshow("Quicksort", QuicksortImg);//���
	cvWaitKey(DELAY);
}

void Mergesort(int *List, int Left, int Right) {
	if (Left < Right) {
		int Cut = (Left + Right) / 2;//�p���e���Τ���
		Mergesort(List, Left, Cut);//�X�ֱƧǤ��Υ���
		Mergesort(List, Cut + 1, Right);//�X�ֱƧǤ��Υk��
		Merge(List, Left, Right, Cut);//�X�ֱƧ�
		MergesortDraw(List, Left, Right, Cut);

	}
}
void Merge(int *List, int p, int q, int c) {
	int n1 = c - p + 1;//��e���Υ���}�C�j�p
	int n2 = q - c;//��e���Υk��}�C�j�p
	int* cL = new int[n1];
	int* cR = new int[n2];

	//�ƻsList��Ʀܥ��k�}�C
	memcpy(cL, &List[p], n1 * sizeof(int));
	memcpy(cR, &List[c + 1], n2 * sizeof(int));

	cL[n1] = MAXIMUM;
	cR[n2] = MAXIMUM;

	int i = 0, j = 0;
	for (int k = p; k <= q; k++) {
		//���}�C��i���p�󵥩�k�}�Cj���h���}�Ci������JList�A�Ϥ���P
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
		//����e���C��
		if (k >= L && k <= C)
			color = CV_RGB(0, 255, 0);//���}�C�����
		else if (k > C && k <= R)
			color = CV_RGB(255, 0, 0);//�k�}�C������
		else
			color = CV_RGB(255, 255, 255);//���ϥά��զ�

		rectangle(MergesortImg, Point(k*(INTERVAL + WIDTH), MAXIMUM - List[k]), Point(k*(INTERVAL + WIDTH) + WIDTH, MAXIMUM), color, CV_FILLED);
	}
	imshow("Mergesort", MergesortImg);
	cvWaitKey(DELAY);
}