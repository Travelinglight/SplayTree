#include "SplayTree.h"
using namespace std;

class A {
public :
	int x;
	A(int id = 0) { x = id; }
	friend ostream &operator<<(ostream &out, A a);
};

ostream &operator<<(ostream &out, A a) {
	cout << a.x;
	return out;
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
		A a(3), b(4);
		SplayTree<A> AT1;
		//SplayTree<int> AT2(2);
		SplayTree<A> AT3(a, &cmp);
		SplayTree<A, int> AT4(4, 2, &cmp);
		// Made the (*cmp) public
		//cout << AT3.cmp(a, b) << endl;
		//cout << AT4.cmp(b, a) << endl;
		SplayTree<A, int> AT5(AT4);
		//cout << AT5.cmp(a, a) << endl

		AT1.addRoot(1);
		SplayTree<A, int> AT6;
		AT6.addRoot(6, 8);
		AT6.setCmp(&cmp);
		cout << *(AT6.find(6)) << endl;
		AT6.empty();
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
		cout << "--------------------------------------" << endl;
		ST.find(1);
		ST.print();
		/*ST.Delete(1);
		cout << "--------------------------------------" << endl;
		ST.print();*/
		ST.Delete(2);
		cout << "--------------------------------------" << endl;
		ST.print();
	}
	system("pause");
}
