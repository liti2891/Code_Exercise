#include <stdio.h>
#include <iostream>
using namespace std;

void min_heapify(int, int);
void build_min_heap(int);
int A[1000] = { -1 };

int main() {
	int size = 0;
	int num;
	char cmd;
	while (cin >> cmd) {
		if (cmd == 'a') {//輸入新的元素並重新建立heap
			cin >> num;
			A[++size] = num;
			build_min_heap(size);
			printf("The min-heap is of size %d and the current minimum is %d.\n", size, A[1]);
		}
		else if (cmd == 'b') {//刪除最小元素並重新建立heap
			A[1] = A[size];
			A[size] = -1;
			--size;
			build_min_heap(size);
			printf("The min-heap is of size %d and the current minimum is %d.\n", size, A[1]);
		}
		else if (cmd == 'c') {//印出陣列
			for (int i = 1; i <= size; i++) {
				if (i != size)cout << A[i] << " ";
				else cout << A[i] << endl;
			}
		}
		else if (cmd == 'd') {//結束輸入
			break;
		}
	}
	return 0;
}

void min_heapify(int i, int size) {
	int left = 2 * i;
	int right = 2 * i + 1;
	int smallest;

	if (left <= size && A[left] < A[i])
		smallest = left;
	else
		smallest = i;

	if (right <= size && A[right] < A[smallest])
		smallest = right;

	if (smallest != i) {
		swap(A[smallest], A[i]);
		min_heapify(smallest, size);
	}
}

void build_min_heap(int size) {
	for (int i = size / 2; i >= 1; i--)
		min_heapify(i, size);
}