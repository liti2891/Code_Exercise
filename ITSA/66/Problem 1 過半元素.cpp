#include <stdio.h>
#include <iostream>
#include <string>
#include<sstream> 
#include <map>
using namespace std;

int main()
{
	//�ϥ�string�A�קK�W�j��ư��D
	string iRow;
	string n;
	int total = 0;
	map<string, int> nCount;
	map<string, int>::iterator iter;

	while (getline(cin, iRow)) {//Ū�J�@���
		stringstream i(iRow);//�ΨӤ��ΦU���
		while (i >> n) {
			total++;//�C���`��+1

			//�d��map�O�_�s�bn�A�s�b�N�p��+1�A���s�b�h�[�Jn�ó]��1
			iter = nCount.find(n);
			if (iter != nCount.end()) nCount[n]++;
			else nCount[n] = 1;
		}
		bool bOver = false;
		string num;
		//���ymap�A�p�G�������j���`��1/2�h��X�ӼƭȡA�_�h��XNO
		for (iter = nCount.begin(); iter != nCount.end(); iter++) {
			if (iter->second > total / 2) {
				bOver = true;
				num = iter->first;
				cout << num << endl;
				break;
			}
		}
		if (!bOver)	cout << "NO" << endl;
		nCount.clear();//�M��map
		total = 0;
	}
	return 0;
}
