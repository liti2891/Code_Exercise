#include <iostream>
using namespace std;

int find_step(int N) {
	if (N == 1)return 0;//如果碰到1就回傳0次
	if (N % 2 == 0)return find_step(N / 2) + 1;//每次呼叫find_step執行次數+1
	else {
		int addN = find_step(N + 1) + 1;
		int decN = find_step(N - 1) + 1;
		return addN < decN ? addN : decN;//比較N+1及N-1的次數誰少並輸出
	}
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int N;
		//輸入N及輸出步驟數
		cin >> N;
		cout << find_step(N) << endl;
	}

	return 0;
}