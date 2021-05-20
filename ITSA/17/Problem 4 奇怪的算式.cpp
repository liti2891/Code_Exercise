#include <iostream>
#include <cstring>
#include <iomanip>
#include <string>
#include <stack>
using namespace std;

class CExp {
public:
	bool isTypeNum;
	string exp;
	CExp() :isTypeNum(true) {}
};

double Calculate(double n1, CExp op, double n2) {
	double ans;
	if (op.exp == "+") {
		ans = n1 + n2;
	}
	else if (op.exp == "-") {
		ans = n1 - n2;
	}
	else if (op.exp == "*") {
		ans = n1 * n2;
	}
	else if (op.exp == "/") {
		ans = n1 / n2;
	}
	return ans;
}

int main() {
	int n;
	cin >> n;
	cin.ignore();
	for (int i = 0; i < n; i++) {
		stack<CExp> stackExp;
		stack<double> stackNum;
		string str;
		while (cin >> str) {
			if (str == "+" || str == "-" || str == "*" || str == "/") {
				CExp itemNow;
				itemNow.exp = str;
				itemNow.isTypeNum = false;
				stackExp.push(itemNow);
			}
			else {
				double N2 = stoi(str);
			NUM_PROC:
				CExp itemTop = stackExp.top();
				if (itemTop.isTypeNum == true) {
					double N1 = stackNum.top();
					stackNum.pop();
					CExp itemN1;
					itemN1 = stackExp.top();
					stackExp.pop();

					CExp itemOP = stackExp.top();
					stackExp.pop();

					double ans = Calculate(N1, itemOP, N2);
					str = "(" + itemN1.exp + itemOP.exp + str + ")";
					if (stackExp.size() > 0 && stackExp.top().isTypeNum == true) {
						N2 = ans;
						goto NUM_PROC;
					}
					else {
						CExp itemAns;
						itemAns.exp = str;
						stackNum.push(ans);
						stackExp.push(itemAns);
					}
				}
				else {
					CExp itemNow;
					itemNow.exp = str;
					stackExp.push(itemNow);
					stackNum.push((double)stoi(str));
				}
			}
			if (cin.peek() == '\n' || cin.peek() == '\r') {
				//cout << stackExp.top().exp << "=" << stackNum.top() << endl;
				string outFormula = stackExp.top().exp;
				//§R°£¦h¾lªº¬A©·
				outFormula.erase(0, 1);
				outFormula.erase(outFormula.size() - 1, 1);
				cout << outFormula << "=" << fixed << setprecision(2) << stackNum.top() << endl;
				cin.ignore();
				break;
			}
		}
	}
	return 0;
}