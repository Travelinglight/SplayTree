/*
TreeNode.h

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
#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

class NULLT {};

inline int MAX(int a, int b) {
	return a > b ? a : b;
}

//------------------------------------Tree node-----------------------------------------
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
		if (Rcd == NULL)
			Rcd = new T2;
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
		if (Lft == NULL)
			Lft = new Node<T1, T2>;
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
		if (Rgt == NULL)
			Rgt = new Node<T1, T2>;
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

#endif