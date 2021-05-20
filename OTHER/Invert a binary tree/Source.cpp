#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) :val(x), left(NULL), right(NULL) {}
};

class Solution {
	vector<vector<string>> vecTreeMap;
	int maxDigits;
	int max;
public:
	Solution() { maxDigits = -1; max = -1; }
	TreeNode *inverTree(TreeNode* root) {
		if (root == NULL)return NULL;

		TreeNode *temp = root->left;
		root->left = inverTree(root->right);
		root->right = inverTree(temp);
		return root;
	}

	/*   A
		B  C
	   D E F G
	  ...
	節點輸入方式為從左至右從上至下*/
	TreeNode* insertNode(TreeNode* root, TreeNode* node, int layer) {
		if (layer == 0)return NULL;
		//有位子就放
		if (root->left == NULL) {
			if (max < node->val) {
				max = node->val;
				int tmp = max;
				maxDigits = 0;
				while (tmp > 0) {
					tmp /= 10;
					maxDigits++;
				}
			}
			root->left = node;
		}
		else if (root->right == NULL) {
			if (max < node->val) {
				max = node->val;
				int tmp = max;
				maxDigits = 0;
				while (tmp > 0) {
					tmp /= 10;
					maxDigits++;
				}
			}
			root->right = node;
		}
		else {
			TreeNode *flagL, *flagR;
			flagL = insertNode(root->left, node, layer - 1);//先往左下找
			if (flagL == NULL) {
				flagR = insertNode(root->right, node, layer - 1);//再找右下
				if (flagL == NULL && flagR == NULL)return NULL;
			}
		}
		return root;
	}
	int rightLayer(TreeNode *root) {
		if (root->right == NULL)return 1;//掃描右節點深度
		return 1 + rightLayer(root->right);
	}
	int numLayer(TreeNode *root) {
		if (root->left == NULL)return 1;//掃描左節點深度
		return 1 + numLayer(root->left);
	}
	void vecScanTree(TreeNode* root, int layer, int maxLayer) {
		//掃描整棵樹，並根據各層存入vector
		if (layer + 1 == maxLayer) {
			vecTreeMap.clear();
			vecTreeMap = vector<vector<string>>(maxLayer);
		}
		vecTreeMap[layer].push_back(to_string(root->val));
		if (layer == 0)return;
		if (root->left != NULL)vecScanTree(root->left, layer - 1, maxLayer);
		else vecTreeMap[layer - 1].push_back("N");
		if (root->right != NULL)vecScanTree(root->right, layer - 1, maxLayer);
		else vecTreeMap[layer - 1].push_back("N");
		return;
	}
	void showTree(int layer) {
		int *pow2Table;
		pow2Table = new int[layer];
		for (int i = 0; i <= layer; i++)pow2Table[i] = pow(2, i);

		for (int i = layer - 1; i >= 0; i--) {
			for (int k = 0; k < pow2Table[i] - 1; k++)cout << " ";
			for (int k = 0; k < maxDigits; k++)cout << " ";

			for (int j = 0; j < pow2Table[layer - i - 1]; j++) {
				if (vecTreeMap[i][j] != "N") {
					int tmp = stoi(vecTreeMap[i][j]);
					cout << setw(maxDigits) << vecTreeMap[i][j];
					for (int k = 0; k < pow2Table[i + 1] - 1; k++)cout << " ";
				}
				else {
					for (int k = 0; k < maxDigits; k++)cout << " ";
					for (int k = 0; k < pow2Table[i + 1] - 1; k++)cout << " ";
				}
			}
			cout << endl;
		}
	}
};

int main() {
	Solution s;
	TreeNode root(4);//根節點
	int layer;
	int input[] = { 2,7,1,3,6,9 };

	//輸入新的節點
	for (int i = 0; i < 6; i++) {
		int val = input[i];
		layer = s.rightLayer(&root);
		s.insertNode(&root, new TreeNode(val), layer);
	}
	layer = s.numLayer(&root);

	//掃描整棵樹並印出
	s.vecScanTree(&root, layer - 1, layer);
	s.showTree(layer);
	cout << endl;
	//翻轉並掃描樹再印出
	s.inverTree(&root);
	s.vecScanTree(&root, layer - 1, layer);
	s.showTree(layer);

	return 0;
}