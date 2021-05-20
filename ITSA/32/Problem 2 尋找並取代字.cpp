#include <iostream>  
#include <string>  
using namespace std;

int main() {
	string str, kStr, rStr;

	//讀取原始字串、要替換的字串、新的字串
	getline(cin, str);
	getline(cin, kStr);
	getline(cin, rStr);
	kStr.erase(kStr.size() - 1, 1);// 提交ITSA加上的，可能跟版本有關?

	while (1) {
		int kidx = str.find(kStr);//搜尋原始字串有沒有要替換的字串
		if (kidx != string::npos) //如果有就取代
			str.replace(kidx, kStr.size(), rStr); //原始字串從kidx開始往後kStr長度的字串換成rStr
		else 
			break;
	}
	cout << str << endl;
	return 0;
}
