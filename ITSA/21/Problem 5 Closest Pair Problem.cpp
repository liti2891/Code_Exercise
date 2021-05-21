#include <iostream>
#include <math.h>
using namespace std;

class Point {
public:
	double x;
	double y;

	void Set(int i,int j) {		//設定(x,y)
		x = i;
		y = j;
	}

	double Distance(Point other) {		//計算兩點距離
		double d;
		d = pow((x - other.x), 2) + pow((y - other.y), 2);
		return sqrt(d);
	}
};

int main() {
	Point input[101];
	int n;
	double min=DBL_MAX;		//宣告min為double最大值

	cin >> n;		//輸入n個點
	for (int i = 0; i < n; i++) {		//輸入各點點座標
		int x, y;
		cin >> x >> y;
		input[i].Set(x, y);
	}
	
	for (int i = 0; i < n; i++)		
		for (int j = i + 1; j < n; j++) {
			double tmp = input[i].Distance(input[j]);	//算各點距離
			if (min > tmp &&i != j)		//將min換為最小距離
				min = tmp;
		}
	printf("%.4f\n", min);		//輸出距離取到小數第4位

	system("pause");
	return 0;
}