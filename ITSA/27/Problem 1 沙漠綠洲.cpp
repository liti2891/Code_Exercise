#include <iostream>
using namespace std;

bool splitf(int t, int *num, int k, int split) {
	for (int i = 0; i < k; i++) {
		int t_next = t - num[i];
		if (t_next == 0)return true;
		else if (t_next > 0 && split > 1)
			if (splitf(t_next, num, k, split - 1))
				return true;
	}
	return false;
}

int main() {
	int n, k, t;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> k;
		int *num = new int[k];
		for (int j = 0; j < k; j++) {
			cin >> num[j];
		}
		cin >> t;
		bool a;
		for (int split = 1; split <= t; split++) {
			a = splitf(t, num, k, split);
			if (a) {
				cout << split << endl;
				break;
			}
		}
		if (!a)cout << 0 << endl;
	}
}