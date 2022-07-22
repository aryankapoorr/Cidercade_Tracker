/******************************************************************************

Aryan Kapoor
NetID: AXK200159

*******************************************************************************/
// Class declarations below
#ifndef BINTREE_H
#define BINTREE_H

#include "Node.h"

// 'T' referring to the templated object the class is based off of
template <typename T>
class BinTree {
private:
	// Class attributes below
	Node<T>* root;

public:
	// Class constructors below, one overloaded for the templated object
	BinTree();
	BinTree(T);

	// Accessor and mutator methods for class attributes
	Node<T>* getRoot() { return root; }
	void setRoot(Node<T>* n) { root = n; }

	// Method to insert into and search through the tree
	void insert(Node<T>*, Node<T>*);
	Node<T>* search(Node<T>*, std::string);

	// Helper method + method to delete a node in the tree
	T del(std::string);
	void delHelper(Node<T>*, Node<T>*);

	// Helper method that retrieves the parent of a particular node
	Node<T>* getParent(Node<T>*, Node<T>*);
};
#endif

/*
* Default constructor, sets the root to a nullptr
*/
template <typename T>
BinTree<T>::BinTree() {
	root = nullptr;
}

/*
* Overloaded constructor, setting a value for the root's templated object
*/
template <typename T>
BinTree<T>::BinTree(T val) {
	root->setObj(val);
}

/*
* Inserts a templated node into the binary search tree,
* @param p the parent node being looked at for tracing purposes
* @param i the node to be inserted into the BST
*/
template <typename T>
void BinTree<T>::insert(Node<T>* p, Node<T>* i) {
	// Inserts the first node of the BST
	if (!root)
		root = i;
	else {
		// Retrieves the parent and insertion objects to compare
		T parentObj = p->getObj();
		T insertObj = i->getObj();

		// Goes to the left subtree if the insertion object is less
		// than the parent
		if (insertObj < parentObj) {
			if (!p->getLeft())
				// Inserts the node
				p->setLeft(i);
			else
				// Recursively calls the method if the current insertion
				// spot is taken up
				insert(p->getLeft(), i);
		}
		// Goes to the right subtree if the insertion object is
		// greater than the parent
		else {
			if (!p->getRight())
				// Inserts the node
				p->setRight(i);
			else
				// Recursively calls the method if the current insertion
				// spot is taken up
				insert(p->getRight(), i);
		}
	}
}

/*
* Searches through the BST to find a specific node recursively,
* returns a nullptr if the node is not a member of the tree
* @param n the parent node of the node being search
* @param val the name value of the object to check
*/
template <typename T>
Node<T>* BinTree<T>::search(Node<T>* n, std::string val) {
	// Creates an object based on the name value in order to make
	// comparisons throughout the tree
	T obj = T(val, 0, "", 0);
	bool found = false;

	// Only iterates if the next node being looked at exists
	if (n) {
		T check = n->getObj();
		// Returns the node if the object matches the search term
		if (obj == check) {
			found = true;
		}
		// Calls the method with the left subtree if the search term is
		// less than the object, calls with the right subtree if otherwise
		else if (obj < check) {
			return search(n->getLeft(), val);
		}
		else {
			return search(n->getRight(), val);
		}
	}
	if (found)
		return n;
	return nullptr;
}

/*
* Searches through the BST to find a node based on the string value
* given, return the deleted node if found, return nullptr if not found
* @param val is the string value of the node intended to be deleted
*/
template <typename T>
T BinTree<T>::del(std::string val) {
	// Retrieves the node to be deleted, as well as the parent of the node
	Node<T>* n = search(root, val);
	T ret = n->getObj();
	Node<T>* p = getParent(root, n);
	// Calls the helper function to recursively find the deleting point
	delHelper(p, n);
	return ret;
}

/*
* Helper method for the delete function, recursively finds the
* point of deletion in the Binary Search Tree
*/
template <typename T>
void BinTree<T>::delHelper(Node<T>* p, Node<T>* n) {
	// Exits if the node intended to be deleted does not exist
	if (n == nullptr)
		return;

	// Case if the node to be deleted has 2 children nodes
	if (n->getLeft() != nullptr && n->getRight() != nullptr) {
		Node<T>* s = n->getRight();
		Node<T>* sParent = n;

		// Sets the parent and node to be used when the helper method
		// gets recursively called
		while (s->getLeft() != nullptr) {
			sParent = s;
			s = s->getLeft();
		}

		n->setObj(s->getObj());
		delHelper(sParent, s);
	}
	// Case if the node to be deleted is the root of the BST
	else if (n == root) {
		if (n->getLeft())
			root = n->getLeft();
		else
			root = n->getRight();
	}
	// Case if the node to be deleted hase a left child
	else if (n->getLeft() != nullptr) {
		if (p->getLeft() == n)
			p->setLeft(n->getLeft());
		else
			p->setRight(n->getLeft());
	}
	// Case if the node to be deleted hase a right child
	else {
		if (p->getLeft() == n)
			p->setLeft(n->getRight());
		else
			p->setRight(n->getRight());
	}
}

/*
* Helper method to determine the prante of a certain node
*/
template <typename T>
Node<T>* BinTree<T>::getParent(Node<T>* p, Node<T>* n) {
	// Case if the subtree's root does not exist
	if (!p)
		return nullptr;

	// Case if the subtree's root is equal to the node being searched for
	if (p->getLeft() == n || p->getRight() == n)
		return p;

	T obj1 = n->getObj();
	T obj2 = p->getObj();

	// Recursively calls the method based on the comparison of the node and the parent
	if (obj1 < obj2)
		return getParent(p->getLeft(), n);
	else
		return getParent(p->getRight(), n);
}