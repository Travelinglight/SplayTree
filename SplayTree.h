#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include "TreeNode.h"

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
	T2 *find(const T1 &id) const;
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

}

template<class T1, class T2>
bool SplayTree<T1, T2>::Delete(const T1 &id) {
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

#endif
