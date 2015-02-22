#include "SplayTree.h"
#include <string>
using namespace std;

class A {
public :
	int x;
	A(int id = 0) { x = id; }
	friend ostream &operator<<(ostream &out, A a);
	friend bool operator<(const A &a, const A &b);
	friend bool operator>(const A &a, const A &b);
};

ostream &operator<<(ostream &out, A a) {
	cout << a.x;
	return out;
}

bool operator<(const A &a, const A &b) {
	return (a.x < b.x);
}

bool operator>(const A &a, const A &b) {
	return (a.x > b.x);
}

int cmp(const A &a, const A &b) {
	if (a.x > b.x)
		return 1;
	if (a.x < b.x)
		return -1;
	return 0;
}

int main() {
	{
		SplayTree<int> ST1;
		for (int i = 1; i < 8; i++)
			ST1.Insert(i);
		ST1.print();
	}
	{
		A a(3), b(4);
		SplayTree<A> ST1;
		SplayTree<int> ST2(2);
		SplayTree<A> ST3(a, NULL, cmp);
		SplayTree<A, int> ST4(4, 2, cmp);
		// Made the (*cmp) public
		//cout << ST3.cmp(a, b) << endl;
		//cout << ST4.cmp(b, a) << endl;
		SplayTree<A, int> ST5(ST4);
		//cout << ST5.cmp(a, a) << endl

		ST1.addRoot(1);
		SplayTree<A, int> ST6;
		ST6.addRoot(6, 8);
		ST6.setCmp(cmp);
		cout << *(ST6.find(6)) << endl;
		ST6.empty();
	}
	{
		SplayTree<A> ST(cmp);
		for (int i = 1; i < 8; i++)
			ST.Insert(i);
		ST.find(1);
		ST.print();
		ST.Delete(3);
		cout << "--------------------------------------" << endl;
		ST.print();
	}
	{
		cout << "--------------------------------------" << endl;
		SplayTree<A> ST(cmp);
		for (int i = 7; i > 0; i--)
			ST.Insert(i);
		ST.find(7);
		ST.print();
		ST.Delete(5);
		cout << "--------------------------------------" << endl;
		ST.print();
	}
	{
		cout << "--------------------------------------" << endl;
		SplayTree<A> ST(cmp);
		for (int i = 1; i < 5; i++) {
			ST.Insert(i);
			ST.Insert(8 - i);
		}
		ST.print();
		//ST.find(1);
		//cout << "--------------------------------------" << endl;
		//ST.print();
		//ST.Delete(1);
		//cout << "--------------------------------------" << endl;
		//ST.print();
		ST.Delete(2);
		cout << "--------------------------------------" << endl;
		ST.print();
	}
	system("pause");
}
