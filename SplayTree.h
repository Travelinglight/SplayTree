#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include "TreeNode.h"
using namespace std;

class SplayERR {
public :
	std::string error;
	SplayERR();
	SplayERR(std::string info) {
		error = info;
	}
};

//----------------------------------SplayTree----------------------------------
template<class T1, class T2 = NULLT>
class SplayTree {
private :
	Node<T1, T2> *root;
	int size;
	int(*cmp)(const T1 &a, const T1 &b);

	void printNode(Node<T1, T2> *node) const;
	int calcSize(const Node<T1, T2> * const node) const;
	int judgeCase(Node<T1, T2> *node, const T1 &id) const;
	Node<T1, T2>* findRMN(Node<T1, T2>* const node) const;
	Node<T1, T2>* findLMN(Node<T1, T2>* const node) const;
	Node<T1, T2>* splay(Node<T1, T2> *node, const T1 &id);
public :
	SplayTree();
	SplayTree(int(*compare)(const T1 &a, const T1 &b));
	SplayTree(const Node<T1, T2> &head, int(*compare)(const T1 &a, const T1 &b) = NULL);
	SplayTree(const T1 &rootID, const T2 * const rootRcd = NULL, int(*compare)(const T1 &a, const T1 &b) = NULL);
	SplayTree(const T1 &rootID, const T2 &rootRcd, int(*compare)(const T1 &a, const T1 &b) = NULL);
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
// AUTHOR/DATE: KC 2015-02-13
//							KC 2015-02-13
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
SplayTree<T1, T2>::SplayTree() {
	root = NULL;
	size = 0;
	cmp = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: SplayTree
// DESCRIPTION: Constructor of SplayTree class.
//   ARGUMENTS: int(*compare)(const T1 &a, const T1 &b) = NULL - the compare function
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-13
//							KC 2015-02-13
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
//				int(*compare)(const T1 &a, const T1 &b) = NULL - the compare function
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-13
//							KC 2015-02-13
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
SplayTree<T1, T2>::SplayTree(const Node<T1, T2> &head, int(*compare)(const T1 &a, const T1 &b)) {
	root = new Node<T1, T2>(head);
	size = 1;
	cmp = compare;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: SplayTree
// DESCRIPTION: Constructor of SplayTree class.
//   ARGUMENTS: const T1 &rootID - the ID of the root node
//				const T2 &rootRcd - the initial root record
//				int(*compare)(const T1 &a, const T1 &b) = NULL - the compare function
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-13
//							KC 2015-02-13
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
SplayTree<T1, T2>::SplayTree(const T1 &rootID, const T2 &rootRcd, int(*compare)(const T1 &a, const T1 &b)) {
	root = new Node<T1, T2>(rootID, rootRcd);
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
// AUTHOR/DATE: KC 2015-02-13
//							KC 2015-02-13
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
SplayTree<T1, T2>::SplayTree(const SplayTree<T1, T2> &Old) {
	size = Old.size;
	cmp = Old.cmp;
	root = new Node<T1, T2>;
	root->copy(Old.root);
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: SplayTree
// DESCRIPTION: Destructor of SplayTree class.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
// AUTHOR/DATE: KC 2015-02-13
//							KC 2015-02-13
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
SplayTree<T1, T2>::~SplayTree() {
	cout << "Destructor: ";
	if (root != NULL)
		cout << root->getID();
	cout << endl;
	delete root;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: setCmp
// DESCRIPTION: To assign the compare function to the member function pointer.
//   ARGUMENTS: int(*compare)(const T1 &a, const T1 &b) - the compare function
// USES GLOBAL: none
// MODIFIES GL: cmp
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-13
//							KC 2015-02-13
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
// AUTHOR/DATE: KC 2015-02-13
//							KC 2015-02-13
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool SplayTree<T1, T2>::addRoot(const T1 &id, const T2 * const rcd) {
	if (root != NULL) {
		throw SplayERR("root already exists");
	}
	root = new Node<T1, T2>(id, rcd);
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
// AUTHOR/DATE: KC 2015-02-13
//							KC 2015-02-13
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool SplayTree<T1, T2>::addRoot(const T1 &id, const T2 &rcd) {
	if (root != NULL) {
		throw SplayERR("root already exists");
	}
	root = new Node<T1, T2>(id, rcd);
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
// AUTHOR/DATE: KC 2015-02-13
//							KC 2015-02-13
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool SplayTree<T1, T2>::addRoot(const Node<T1, T2> &New) {
	if (root != NULL) {
		throw SplayERR("root already exists");
	}
	root = new Node<T1, T2>(New);
	size = calcSize(root);
	return true;
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
//        NAME: splay
// DESCRIPTION: To iteratively splay a subtree with the root "node" and ID "id".
//   ARGUMENTS: Node<T1, T2> *N0 - the root of the subtree that is to be splayed
//				const T1 &id - the id of the node that is to be rotated to the top
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-14
//							KC 2015-02-14
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
//        NAME: Insert
// DESCRIPTION: The user interface of inserting a node into the Splay tree.
//   ARGUMENTS: const T1 &id - the id of the new node that is to be inserted
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-13
//							KC 2015-02-13
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool SplayTree<T1, T2>::Insert(const T1 &id) {
	Node<T1, T2> *tmp = root;
	Node<T1, T2> *nxt = root;

	// special case
	if (root == NULL) {
		root = new Node<T1, T2>(id);
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
// DESCRIPTION: The user interface of deleting a node from the Splay tree.
//   ARGUMENTS: const T1 &id - the id of the new node that is to be deleted
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-13
//							KC 2015-02-13
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
//        NAME: empty
// DESCRIPTION: To delete all the nodes in the Splay tree.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: root, size
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-13
//							KC 2015-02-13
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
//        NAME: find
// DESCRIPTION: To find a Node with given id.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: root (possible)
//     RETURNS: T2*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-15
//							KC 2015-02-15
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
T2* SplayTree<T1, T2>::find(const T1 &id) {
	root = splay(root, id);
	if (cmp(id, root->getID()) != 0)
		return NULL;
	else
		return root->getRcd();
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: print
// DESCRIPTION: To print the whole tree inorderly.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-14
//							KC 2015-02-14
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
