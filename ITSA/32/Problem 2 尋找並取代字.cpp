#include <iostream>  
#include <string>  
using namespace std;

int main() {
	string str, kStr, rStr;

	//Ū����l�r��B�n�������r��B�s���r��
	getline(cin, str);
	getline(cin, kStr);
	getline(cin, rStr);
	kStr.erase(kStr.size() - 1, 1);// ����ITSA�[�W���A�i��򪩥�����?

	while (1) {
		int kidx = str.find(kStr);//�j�M��l�r�꦳�S���n�������r��
		if (kidx != string::npos) //�p�G���N���N
			str.replace(kidx, kStr.size(), rStr); //��l�r��qkidx�}�l����kStr���ת��r�괫��rStr
		else 
			break;
	}
	cout << str << endl;
	return 0;
}
