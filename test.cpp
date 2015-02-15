#include "SplayTree.h"
using namespace std;

int compare(const int &a, const int &b) {
	if (a > b)
		return 1;
	if (a < b)
		return -1;
	return 0;
}
int main() {
	{
		SplayTree<int, int> A(&compare);
		for (int i = 1; i < 8; i++)
			A.Insert(i);
		A.find(1);
		A.print();
	}
	{
		cout << "--------------------------------------" << endl;
		SplayTree<int, int> A(&compare);
		for (int i = 7; i > 0; i--)
			A.Insert(i);
		A.find(7);
		A.print();
	}
	{
		cout << "--------------------------------------" << endl;
		SplayTree<int, int> A(&compare);
		for (int i = 1; i < 5; i++) {
			A.Insert(i);
			A.Insert(8 - i);
		}
		A.print();
		cout << "--------------------------------------" << endl;
		A.find(1);
		A.print();
	}
	system("pause");
}
