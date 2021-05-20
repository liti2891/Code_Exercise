#include <stdio.h>
#include <iostream>
#include <string>
#include<sstream> 
#include <map>
using namespace std;

int main()
{
	//使用string，避免超大整數問題
	string iRow;
	string n;
	int total = 0;
	map<string, int> nCount;
	map<string, int>::iterator iter;

	while (getline(cin, iRow)) {//讀入一整行
		stringstream i(iRow);//用來分割各整數
		while (i >> n) {
			total++;//每次總數+1

			//查詢map是否存在n，存在就計數+1，不存在則加入n並設為1
			iter = nCount.find(n);
			if (iter != nCount.end()) nCount[n]++;
			else nCount[n] = 1;
		}
		bool bOver = false;
		string num;
		//掃描map，如果有元素大於總數1/2則輸出該數值，否則輸出NO
		for (iter = nCount.begin(); iter != nCount.end(); iter++) {
			if (iter->second > total / 2) {
				bOver = true;
				num = iter->first;
				cout << num << endl;
				break;
			}
		}
		if (!bOver)	cout << "NO" << endl;
		nCount.clear();//清空map
		total = 0;
	}
	return 0;
}
