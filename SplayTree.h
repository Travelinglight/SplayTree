/*
SplayTree.h

Copyright (C) 2015-2019 Kingston Chan

This source code is provided 'as-is', without any express or implied
warranty. In no event will the author be held liable for any damages
arising from the use of this code.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this source code must not be misrepresented; you must not
claim that you wrote the original source code. If you use this source code
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original source code.

3. This notice may not be removed or altered from any source distribution.

Kingston Chan

*/

#ifndef SplayTREE_H
#define SplayTREE_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class NULLT {};

class NodeERR {	// used to throw out when error occurs
public :
	std::string error;
	NodeERR();
	NodeERR(std::string info) {
		error = info;
	}
};

class SplayERR { // used to throw out when error occurs
public :
	std::string error;
	SplayERR();
	SplayERR(std::string info) {
		error = info;
	}
};

inline int MAX(int a, int b) {
	return a > b ? a : b;
}

template<typename T1>
int dCmp(const T1 &a, const T1 &b) {
	if (a > b)
		return 1;
	if (a < b)
		return -1;
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Tree node/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2 = NULLT>
class Node {

private:
	T1 ID;
	T2 *Rcd;	// record
	Node *Lft, *Rgt;
	int height;

public:
	// constructor and destructor
	Node();
	Node(const T1 &id, const T2 * const rcd = NULL);
	Node(const T1 &id, const T2 &rcd);
	Node(const Node<T1, T2> &New);
	~Node();

	// modify the info of private members
	bool ModifyID(const T1 &tmp);
	bool ModifyHeight(int h);
	bool operator=(const Node<T1, T2> &b);
	bool operator=(const T1 &id);
	bool copy(const Node<T1, T2> * const b);
	bool AddLft(Node<T1, T2> *lft);
	bool AddRgt(Node<T1, T2> *rgt);
	bool AddLft(const T1 &lftID, const T2 * const lftRcd = NULL);
	bool AddRgt(const T1 &rgtID, const T2 * const RgtRcd = NULL);

	// get the info of private members
	Node<T1, T2> *getLft() const { return Lft; }
	Node<T1, T2> *getRgt() const { return Rgt; }
	int getHeight() const { return height; }
	const T1 &getID() const { return ID; }
	T2 *getRcd() const { return Rcd; }
	void print() const;
};

////////////////////////////////////////////////////////////////////////////////
//        NAME: Node
// DESCRIPTION: Constructor of Node class.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: height, Rcd, Lft, Rgt
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-05
//							KC 2015-02-05
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>::Node() {
	height = 0;
	Rcd = new T2;
	if (Rcd == NULL)
		throw NodeERR("Out of space");
	Lft = Rgt = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: Node
// DESCRIPTION: Constructor of Node class.
//   ARGUMENTS: const T1 &id - the ID of the node
//				const T2 * const rcd - the initial record with default value NULL
// USES GLOBAL: none
// MODIFIES GL: ID, Rcd, height, Lft, Rgt
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-09
//							KC 2015-02-09
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>::Node(const T1 &id, const T2 * const rcd) {
	ID = id;
	Rcd = new T2;
	if (Rcd == NULL)
		throw NodeERR("Out of space");
	if (rcd != NULL)
		*Rcd = *rcd;
	Lft = Rgt = NULL;	// no sons at first
	height = 0;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: Node
// DESCRIPTION: Constructor of Node class.
//   ARGUMENTS: const T1 &id - the ID of the node
//				const T2 &rcd - the initial record
// USES GLOBAL: none
// MODIFIES GL: ID, Rcd, height, Lft, Rgt
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-09
//							KC 2015-02-09
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>::Node(const T1 &id, const T2 &rcd) {
	ID = id;
	Rcd = new T2;
	if (Rcd == NULL)
		throw NodeERR("Out of space");
	*Rcd = rcd;
	Lft = Rgt = NULL;	// no sons at first
	height = 0;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: Node
// DESCRIPTION: Copy constructor of Node class.
//   ARGUMENTS: const Node<T1, T2> &New - the Node that is to be copied
// USES GLOBAL: none
// MODIFIES GL: ID, Rcd, height, Lft, Rgt
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-05
//							KC 2015-02-05
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>::Node(const Node<T1, T2> &New) {
	copy(&New);
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: ~Node
// DESCRIPTION: Destructor of Node class.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: ID, Rcd, height, Lft, Rgt
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-05
//							KC 2015-02-05
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>::~Node() {
	if (Rcd != NULL)
		delete Rcd;
	if (Lft != NULL)
		delete Lft;
	if (Rgt != NULL)
		delete Rgt;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: ModifyID
// DESCRIPTION: To modify the ID of a Node.
//   ARGUMENTS: const T1 &tmp - the new ID value
// USES GLOBAL: none
// MODIFIES GL: ID
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-05
//							KC 2015-02-05
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool Node<T1, T2>::ModifyID(const T1 &tmp) {
	ID = tmp;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: ModifyHeight
// DESCRIPTION: To modify the height of a Node.
//   ARGUMENTS: int h - the new height value
// USES GLOBAL: none
// MODIFIES GL: height
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-09
//							KC 2015-02-09
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool Node<T1, T2>::ModifyHeight(int h) {
	height = h;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: copy
// DESCRIPTION: To copy the node and their sons.
//   ARGUMENTS: const Node<T1, T2> * const b - the new node that is to be copied
// USES GLOBAL: none
// MODIFIES GL: ID, Rcd, Lft, Rgt, height
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-08
//							KC 2015-02-08
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool Node<T1, T2>::copy(const Node<T1, T2> * const b) {

	// avoid self copy after deletion
	if (b == this)
		return true;

	// copy ID, record and height
	ID = b->ID;
	if (b->Rcd != NULL) {
		if (Rcd == NULL) {
			Rcd = new T2;
			if (Rcd == NULL) {
				throw NodeERR("Out of space");
				return false;
			}
		}
		*Rcd = *(b->Rcd);
	}
	else {
		if (Rcd != NULL) {
			delete Rcd;
			Rcd = NULL;
		}
	}
	height = b->height;

	// copy the left son
	if (b->Lft != NULL) {
		if (Lft == NULL) {
			Lft = new Node<T1, T2>;
			if (Lft == NULL) {
				throw NodeERR("Out of space");
				return false;
			}
		}
		Lft->copy(b->Lft);
	}
	else {
		if (Lft != NULL) {
			delete Lft;
			Lft = NULL;
		}
	}

	// copy the right son
	if (b->Rgt != NULL) {
		if (Rgt == NULL) {
			Rgt = new Node<T1, T2>;
			if (Rgt == NULL) {
				throw NodeERR("Out of space");
				return false;
			}	
		}
		Rgt->copy(b->Rgt);
	}
	else {
		if (Rgt != NULL) {
			delete Rgt;
			Rgt = NULL;
		}
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: operator=
// DESCRIPTION: copy the content of a Node.
//   ARGUMENTS: const Node<T1, T2> &b - the Node that is to be assigned
// USES GLOBAL: none
// MODIFIES GL: ID, Rcd, height
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-09
//							KC 2015-02-09
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool Node<T1, T2>::operator=(const Node<T1, T2> &b) {
	if (&b == this)
		return true;
	ID = b.getID();
	*Rcd = *(b.getRcd());
	height = b.getHeight();
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: operator=
// DESCRIPTION: Assign the ID of a Node.
//   ARGUMENTS: const T1 &id - the id that is to be assigned
// USES GLOBAL: none
// MODIFIES GL: ID
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool Node<T1, T2>::operator=(const T1 &id) {
	ID = id;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: AddLft
// DESCRIPTION: Concatenate a left son.
//   ARGUMENTS: Node<T1, T2> *lft - the left son that is to be concatenated
// USES GLOBAL: none
// MODIFIES GL: Lft, height
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-05
//							KC 2015-02-05
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool Node<T1, T2>::AddLft(Node<T1, T2> *lft) {

	Lft = lft; // assign the left son

	// update the height
	height = 0;
	if (Lft != NULL)
		height = MAX(height, Lft->height + 1);
	if (Rgt != NULL)
		height = MAX(height, Rgt->height + 1);

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: AddLft
// DESCRIPTION: Concatenate a left son.
//   ARGUMENTS: const T1 &lftID - the ID of the left son that is to be concatenated
//				const T2 * const lftRcd - the record of the left son
// USES GLOBAL: none
// MODIFIES GL: Lft, height
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-05
//							KC 2015-02-05
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool Node<T1, T2>::AddLft(const T1 &lftID, const T2 * const lftRcd) {

	Node *Tmp = new Node(lftID, lftRcd);
	if (Tmp == NULL) {
		throw NodeERR("Out of space");
		return false;
	}
	Lft = Tmp;

	// update the height
	height = 0;
	if (Lft != NULL)
		height = MAX(height, Lft->height + 1);
	if (Rgt != NULL)
		height = MAX(height, Rgt->height + 1);

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: AddRgt
// DESCRIPTION: Concatenate a right son.
//   ARGUMENTS: Node<T1, T2> *rgt - the right son that is to be concatenated
// USES GLOBAL: none
// MODIFIES GL: Rgt, height
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-05
//							KC 2015-02-05
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool Node<T1, T2>::AddRgt(Node<T1, T2> *rgt) {

	Rgt = rgt; // assign the left son

	// update the height
	height = 0;
	if (Lft != NULL)
		height = MAX(height, Lft->height + 1);
	if (Rgt != NULL)
		height = MAX(height, Rgt->height + 1);

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: AddRgt
// DESCRIPTION: Concatenate a right son.
//   ARGUMENTS: const T1 &rgtID - the ID of the right son that is to be concatenated
//				const T2 * const RgtRcd - the record of the right son
// USES GLOBAL: none
// MODIFIES GL: Rgt, height
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-05
//							KC 2015-02-05
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool Node<T1, T2>::AddRgt(const T1 &rgtID, const T2 * const RgtRcd = NULL) {

	Node *Tmp = new Node(rgtID, RgtRcd);
	if (Tmp == NULL) {
		throw NodeERR("Out of space");
		return false;
	}
	Rgt = Tmp;

	// update the height
	height = 0;
	if (Lft != NULL)
		height = MAX(height, Lft->height + 1);
	if (Rgt != NULL)
		height = MAX(height, Rgt->height + 1);

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: print
// DESCRIPTION: To print the Node's ID, height and two sons.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: void
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-11
//							KC 2015-02-11
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
void Node<T1, T2>::print() const{
	cout << ID << ": h-" << height << "  l-";
	if (Lft != NULL)
		cout << '(' << Lft->getID() << ')';
	cout << "  r-";
	if (Rgt != NULL)
		cout << '(' << Rgt->getID() << ')';
	cout << endl;
	if (Lft != NULL)
		Lft->print();
	if (Rgt != NULL)
		Rgt->print();
}

////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////Splay tree/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2 = NULLT>
class SplayTree {

private :
	Node<T1, T2> *root;
	int size;
	int(*cmp)(const T1 &a, const T1 &b);

	int calcSize(const Node<T1, T2> * const node) const;
	int judgeCase(Node<T1, T2> *node, const T1 &id) const;
	Node<T1, T2>* splay(Node<T1, T2> *N0, const T1 &id);
	Node<T1, T2>* findRMN(Node<T1, T2>* const node) const;
	Node<T1, T2>* findLMN(Node<T1, T2>* const node) const;
public :
	// constructors and destructor
	SplayTree();
	SplayTree(int(*compare)(const T1 &a, const T1 &b));
	SplayTree(const Node<T1, T2> &head, int(*compare)(const T1 &a, const T1 &b) = dCmp);
	SplayTree(const T1 &rootID, const T2 * const rootRcd = NULL, int(*compare)(const T1 &a, const T1 &b) = dCmp);
	SplayTree(const T1 &rootID, const T2 &rootRcd, int(*compare)(const T1 &a, const T1 &b) = dCmp);
	SplayTree(const SplayTree<T1, T2> &New);
	~SplayTree();

	bool setCmp(int(*compare)(const T1 &a, const T1 &b));
	bool addRoot(const T1 &id, const T2 * const rcd = NULL);
	bool addRoot(const T1 &id, const T2 &rcd);
	bool addRoot(const Node<T1, T2> &New);

	bool Insert(const T1 &id);
	bool Delete(const T1 &id);
	bool empty();

	int getSize() const { return size; }
	int getHeight() const { return root->getHeight(); }
	T2 *find(const T1 &id);
	T1 rootID() const { return root->getID(); }
	bool print() const;
};

////////////////////////////////////////////////////////////////////////////////
//        NAME: SplayTree
// DESCRIPTION: Constructor of SplayTree class.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
SplayTree<T1, T2>::SplayTree() {
	root = NULL;
	size = 0;
	cmp = dCmp;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: SplayTree
// DESCRIPTION: Constructor of SplayTree class.
//   ARGUMENTS: int(*compare)(const T1 &a, const T1 &b) = dCmp - the compare function
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
SplayTree<T1, T2>::SplayTree(int(*compare)(const T1 &a, const T1 &b)) {
	root = NULL;
	size = 0;
	cmp = compare;
}
////////////////////////////////////////////////////////////////////////////////
//        NAME: SplayTree
// DESCRIPTION: Constructor of SplayTree class.
//   ARGUMENTS: const Node<T1, T2> &head - the root node of the Splay tree
//				int(*compare)(const T1 &a, const T1 &b) = dCmp - the compare function
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
SplayTree<T1, T2>::SplayTree(const Node<T1, T2> &head, int(*compare)(const T1 &a, const T1 &b)) {
	root = new Node<T1, T2>(head.ID, head.Rcd);
	if (root == NULL)
		throw SplayERR("Out of space");
	size = calcSize(root);
	cmp = compare;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: SplayTree
// DESCRIPTION: Constructor of SplayTree class.
//   ARGUMENTS: const T1 &rootID - the ID of the root node
//				const T2 * const rootRcd = dCmp - the initial root record
//				int(*compare)(const T1 &a, const T1 &b) = NULL - the compare function
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
SplayTree<T1, T2>::SplayTree(const T1 &rootID, const T2 * const rootRcd, int(*compare)(const T1 &a, const T1 &b)) {
	root = new Node<T1, T2>(rootID, rootRcd);
	if (root == NULL)
		throw SplayERR("Out of space");
	size = 1;
	cmp = compare;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: SplayTree
// DESCRIPTION: Constructor of SplayTree class.
//   ARGUMENTS: const T1 &rootID - the ID of the root node
//				const T2 &rootRcd - the initial root record
//				int(*compare)(const T1 &a, const T1 &b) = dCmp - the compare function
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
SplayTree<T1, T2>::SplayTree(const T1 &rootID, const T2 &rootRcd, int(*compare)(const T1 &a, const T1 &b)) {
	root = new Node<T1, T2>(rootID, rootRcd);
	if (root == NULL)
		throw SplayERR("Out of space");
	size = 1;
	cmp = compare;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: SplayTree
// DESCRIPTION: Copy constructor of SplayTree class.
//   ARGUMENTS: const SplayTree<T1, T2> &Old - the SplayTree that is to be copied
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
SplayTree<T1, T2>::SplayTree(const SplayTree<T1, T2> &Old) {
	size = Old.size;
	cmp = Old.cmp;
	if (Old.root != NULL) {
		root = new Node<T1, T2>;
		if (root == NULL)
			throw SplayERR("Out of space");
		root->copy(Old.root);
	}
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: SplayTree
// DESCRIPTION: Destructor of SplayTree class.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
SplayTree<T1, T2>::~SplayTree() {
	//cout << "Destructor: ";
	//if (root != NULL)
	//	cout << root->getID();
	//cout << endl;
	delete root;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: calcSize
// DESCRIPTION: To calculate the size of the tree with the root "node".
//   ARGUMENTS: const Node<T1, T2> * const node - the root the of tree
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: int
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
int SplayTree<T1, T2>::calcSize(const Node<T1, T2> * const node) const {
	if (node == NULL)
		return 0;
	else
		return calcSize(node->getLft()) + calcSize(node->getRgt()) + 1;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: setCmp
// DESCRIPTION: To assign the compare function to the member function pointer.
//   ARGUMENTS: int(*compare)(const T1 &a, const T1 &b) - the compare function
// USES GLOBAL: none
// MODIFIES GL: cmp
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool SplayTree<T1, T2>::setCmp(int(*compare)(const T1 &a, const T1 &b)) {
	cmp = compare;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: addRoot
// DESCRIPTION: To add a root for the Splay tree.
//   ARGUMENTS: const T1 &id - the id of the root node
//				const T2 * const rcd - the record of the root node with default value NULL
// USES GLOBAL: none
// MODIFIES GL: root, size
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool SplayTree<T1, T2>::addRoot(const T1 &id, const T2 * const rcd) {
	if (root != NULL) {
		throw SplayERR("root already exists");
	}
	root = new Node<T1, T2>(id, rcd);
	if (root == NULL) {
		throw SplayERR("Out of space");
		return false;
	}
	size = calcSize(root);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: addRoot
// DESCRIPTION: To add a root for the Splay tree.
//   ARGUMENTS: const T1 &id - the id of the root node
//				const T2 &rcd - the record of the root node
// USES GLOBAL: none
// MODIFIES GL: root, size
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool SplayTree<T1, T2>::addRoot(const T1 &id, const T2 &rcd) {
	if (root != NULL) {
		throw SplayERR("root already exists");
	}
	root = new Node<T1, T2>(id, rcd);
	if (root == NULL) {
		throw SplayERR("Out of space");
		return false;
	}
	size = calcSize(root);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: addRoot
// DESCRIPTION: To add a root for the Splay tree.
//   ARGUMENTS: const Node<T1, T2> &New - the copy of the root node
// USES GLOBAL: none
// MODIFIES GL: root, size
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool SplayTree<T1, T2>::addRoot(const Node<T1, T2> &New) {
	if (root != NULL) {
		throw SplayERR("root already exists");
	}
	root = new Node<T1, T2>(New);
	if (root == NULL) {
		throw SplayERR("Out of space");
		return false;
	}
	size = calcSize(root);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: empty
// DESCRIPTION: To delete all the nodes in the Splay tree.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: root, size
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool SplayTree<T1, T2>::empty() {
	if (root == NULL)
		return true;
	delete root;
	root = NULL;
	size = 0;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: judgeCase
// DESCRIPTION: To decide the rotation type for splay function.
//   ARGUMENTS: Node<T1, T2> *node - the root of the subtree that needs rotation
//				const T1 &id - the id that is to find
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: int
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-14
//							KC 2015-02-14
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
int SplayTree<T1, T2>::judgeCase(Node<T1, T2> *node, const T1 &id) const {
	
	// no adjust needed
	if (cmp(id, node->getID()) == 0)
		return 0;
	if ((cmp(id, node->getID()) < 0) && (node->getLft() == NULL))
		return 0;
	if ((cmp(id, node->getID()) > 0) && (node->getRgt() == NULL))
		return 0;
	
	// zig
	if ((cmp(id, node->getID()) < 0) && (cmp(id, node->getLft()->getID()) == 0))
		return 1;
	if ((cmp(id, node->getID()) < 0) && (cmp(id, node->getLft()->getID()) < 0) && (node->getLft()->getLft() == NULL))
		return 1;
	if ((cmp(id, node->getID()) < 0) && (cmp(id, node->getLft()->getID()) > 0) && (node->getLft()->getRgt() == NULL))
		return 1;
	
	// zag
	if ((cmp(id, node->getID()) > 0) && (cmp(id, node->getRgt()->getID()) == 0))
		return 2;
	if ((cmp(id, node->getID()) > 0) && (cmp(id, node->getRgt()->getID()) < 0) && (node->getRgt()->getLft() == NULL))
		return 2;
	if ((cmp(id, node->getID()) > 0) && (cmp(id, node->getRgt()->getID()) > 0) && (node->getRgt()->getRgt() == NULL))
		return 2;

	// zig-zig
	if ((cmp(id, node->getID()) < 0) && (cmp(id, node->getLft()->getID()) < 0))
		return 3;
	
	// zag-zag
	if ((cmp(id, node->getID()) > 0) && (cmp(id, node->getRgt()->getID()) > 0))
		return 4;

	// zig-zag
	if ((cmp(id, node->getID()) < 0) && (cmp(id, node->getLft()->getID()) > 0))
		return 5;
	
	// zag-zig
	if ((cmp(id, node->getID()) > 0) && (cmp(id, node->getRgt()->getID()) < 0))
		return 6;

	return -1;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: findRMN
// DESCRIPTION: To find the right most node in the subtree.
//   ARGUMENTS: Node<T1, T2> *node - the root of the subtree
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-14
//							KC 2015-02-14
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* SplayTree<T1, T2>::findRMN(Node<T1, T2>* const node) const {
	Node<T1, T2>* RMN = &(*node);
	if (RMN == NULL)
		return NULL;
	while (RMN->getRgt() != NULL)
		RMN = RMN->getRgt();
	return RMN;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: findLMN
// DESCRIPTION: To find the left most node in the subtree.
//   ARGUMENTS: Node<T1, T2> *node - the root of the subtree
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-14
//							KC 2015-02-14
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* SplayTree<T1, T2>::findLMN(Node<T1, T2>* const node) const {
	Node<T1, T2>* LMN = &(*node);
	if (LMN == NULL)
		return NULL;
	while (LMN->getLft() != NULL)
		LMN = LMN->getLft();
	return LMN;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: balance
// DESCRIPTION: To balance a subtree whose root is "node".
//   ARGUMENTS: Node<T1, T2> *node - the root of the sub tree
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-12
//							KC 2015-02-12
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* SplayTree<T1, T2>::splay(Node<T1, T2> *N0, const T1 &id) {
	Node<T1, T2> *L = NULL;
	Node<T1, T2> *R = NULL;
	Node<T1, T2> *N1 = NULL;
	Node<T1, T2> *N2 = NULL;
	Node<T1, T2> *RMN = NULL;
	Node<T1, T2> *LMN = NULL;
	int Case = -1;
	if (N0 == NULL)
		return NULL;
	while ((N0 != NULL) && (cmp(id, N0->getID()))) {
		Case = judgeCase(N0, id);
		switch(Case) {
		case 0: // found
			goto Break_While_Loop;

		case 1: // zig
			N1 = N0->getLft();
			N0->AddLft((Node<T1, T2>*)NULL);
			LMN = findLMN(R);
			if (LMN == NULL)
				R = N0;
			else
				LMN->AddLft(N0);
			N0 = N1;
			N1 = NULL;
			break;

		case 2: // zag
			N1 = N0->getRgt();
			N0->AddRgt((Node<T1, T2>*)NULL);
			RMN = findRMN(L);
			if (RMN == NULL)
				L = N0;
			else
				RMN->AddRgt(N0);
			N0 = N1;
			N1 = NULL;
			break;

		case 3: // zig-zig
			N1 = N0->getLft();
			N2 = N1->getLft();
			N0->AddLft(N1->getRgt());
			N1->AddRgt(N0);
			N1->AddLft((Node<T1, T2>*)NULL);
			LMN = findLMN(R);
			if (LMN == NULL)
				R = N1;
			else
				LMN->AddLft(N1);
			N0 = N2;
			N1 = N2 = NULL;
			break;

		case 4: // zag-zag
			N1 = N0->getRgt();
			N2 = N1->getRgt();
			N0->AddRgt(N1->getLft());
			N1->AddLft(N0);
			N1->AddRgt((Node<T1, T2>*)NULL);
			RMN = findRMN(L);
			if (RMN == NULL)
				L = N1;
			else
				RMN->AddRgt(N1);
			N0 = N2;
			N1 = N2 = NULL;
			break;

		case 5: // zig-zag
			N1 = N0->getLft();
			N2 = N1->getRgt();
			N0->AddLft((Node<T1, T2>*)NULL);
			N1->AddRgt((Node<T1, T2>*)NULL);
			LMN = findLMN(R);
			RMN = findRMN(L);
			if (LMN == NULL)
				R = N0;
			else
				LMN->AddLft(N0);
			if (RMN == NULL)
				L = N1;
			else
				RMN->AddRgt(N1);
			N0 = N2;
			N1 = N2 = NULL;
			break;

		case 6: // zag-zig
			N1 = N0->getRgt();
			N2 = N1->getLft();
			N0->AddRgt((Node<T1, T2>*)NULL);
			N1->AddLft((Node<T1, T2>*)NULL);
			LMN = findLMN(R);
			RMN = findRMN(L);
			if (LMN == NULL)
				R = N1;
			else
				LMN->AddLft(N1);
			if (RMN == NULL)
				L = N0;
			else
				RMN->AddRgt(N0);
			N0 = N2;
			N1 = N2 = NULL;
			break;

		default:
			throw SplayERR("Case out of range");
			return NULL;
		}
	}

Break_While_Loop : // reassembly
	LMN = findLMN(R);
	RMN = findRMN(L);
	if (LMN == NULL)
		R = N0->getRgt();
	else
		LMN->AddLft(N0->getRgt());
	if (RMN == NULL)
		L = N0->getLft();
	else
		RMN->AddRgt(N0->getLft());
	N0->AddLft(L);
	N0->AddRgt(R);
	return N0;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: find
// DESCRIPTION: To find a node of a certain ID in Splay tree.
//   ARGUMENTS: const T1 &id - the ID of the node that we want to find
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: T2*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
T2 *SplayTree<T1, T2>::find(const T1 &id) {
	root = splay(root, id);
	if (cmp(id, root->getID()) != 0)
		return NULL;
	else
		return root->getRcd();
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: Insert
// DESCRIPTION: The user interface of inserting a node into the Splay tree.
//   ARGUMENTS: const T1 &id - the id of the new node that is to be inserted
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool SplayTree<T1, T2>::Insert(const T1 &id) {
	Node<T1, T2> *tmp = root;
	Node<T1, T2> *nxt = root;

	// special case
	if (root == NULL) {
		root = new Node<T1, T2>(id);
		if (root == NULL) {
			throw SplayERR("Out of space");
			return false;
		}
		return true;
	}

	// find the position to insert
	do {
		tmp = nxt;
		if (cmp(id, tmp->getID()) < 0)
			nxt = tmp->getLft();
		else if (cmp(id, tmp->getID()) > 0)
			nxt = tmp->getRgt();
		else
			break;
	} while (nxt != NULL);
	
	// insert
	if (cmp(id, tmp->getID()) == 0)
		return true;
	if (cmp(id, tmp->getID()) < 0)
		tmp->AddLft(id);
	else if (cmp(id, tmp->getID()) > 0)
		tmp->AddRgt(id);

	// splay
	root = splay(root, id);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: Delete
// DESCRIPTION: The user interface of deleting a node into the Splay tree.
//   ARGUMENTS: const T1 &id - the id of the new node that is to be deleted
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool SplayTree<T1, T2>::Delete(const T1 &id) {
	Node<T1, T2>* tmp;

	// the tree is empty
	if (root == NULL)
		return true;

	root = splay(root, id);
	if (cmp(id, root->getID()) != 0)
		return true;
	if (root->getLft() == NULL)
		tmp = root->getRgt();
	else {
		tmp = root->getLft();
		tmp = splay(tmp, id);
		tmp->AddRgt(root->getRgt());
	}
	root = tmp;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: print
// DESCRIPTION: print a tree with inorder traversal.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-11
//							KC 2015-02-11
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool SplayTree<T1, T2>::print() const {
	if (root != NULL) {
		root->print();
		return true;
	}
	else
		return false;
}

#endif
