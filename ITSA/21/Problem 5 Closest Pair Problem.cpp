#include <iostream>
#include <math.h>
using namespace std;

class Point {
public:
	double x;
	double y;

	void Set(int i,int j) {		//�]�w(x,y)
		x = i;
		y = j;
	}

	double Distance(Point other) {		//�p����I�Z��
		double d;
		d = pow((x - other.x), 2) + pow((y - other.y), 2);
		return sqrt(d);
	}
};

int main() {
	Point input[101];
	int n;
	double min=DBL_MAX;		//�ŧimin��double�̤j��

	cin >> n;		//��Jn���I
	for (int i = 0; i < n; i++) {		//��J�U�I�I�y��
		int x, y;
		cin >> x >> y;
		input[i].Set(x, y);
	}
	
	for (int i = 0; i < n; i++)		
		for (int j = i + 1; j < n; j++) {
			double tmp = input[i].Distance(input[j]);	//��U�I�Z��
			if (min > tmp &&i != j)		//�Nmin�����̤p�Z��
				min = tmp;
		}
	printf("%.4f\n", min);		//��X�Z������p�Ʋ�4��

	system("pause");
	return 0;
}