/******************************************************************************

Aryan Kapoor
NetID: AXK200159

*******************************************************************************/
// Class definitions/imports below
#ifndef NODE_H
#define NODE_H

#include <iostream>

// 'T' referring to the template the class is based off of
template <typename T>
class Node {
	// Private class members, left/right nodes to create the BST, 
	// as well as a templated object
	private:
		Node* left;
		Node* right;
		T obj;

	public:
		// Class constructors
		Node();
		Node(T);

		// Mutator and accessor methods for the nodes and templated object
		Node* getLeft() { return left; }
		Node* getRight() { return right; }
		void setLeft(Node* n) { left = n; }
		void setRight(Node* n) { right = n; }
		T getObj() { return obj; }
		void setObj(T o) { obj = o; }

		// Class overloaded operators
		bool operator<(Node&);
		bool operator>(Node&);
		bool operator==(Node&);
		friend std::ostream& operator<<(std::ostream&, const Node<T>&);
};
#endif

/*
* Default constructor, sets the child nodes to null
*/
template <typename T>
Node<T>::Node() {
	left = nullptr;
	right = nullptr;
}

/*
* Overloaded constructor, sets child nodes to null and passes
* in the value of the templated object
*/
template <typename T>
Node<T>::Node(T o) {
	left = nullptr;
	right = nullptr;
	obj = o;
}

/*
* Overloaded less than operator, compares the values of the templated objects
*/
template <typename T>
bool Node<T>::operator<(Node& n) {
	if (obj < n.obj)
		return true;
	else
		return false;
}

/*
* Overloaded greater than operator, compares the values of the templated objects
*/
template <typename T>
bool Node<T>::operator>(Node& n) {
	if (obj > n.obj)
		return true;
	else
		return false;
}

/*
* Overloaded equals operator, checks if the value of the templated object in the 
* nodes are equivalent
*/
template <typename T>
bool Node<T>::operator==(Node& n) {
	if (obj == n.obj)
		return true;
	else
		return false;
}

/*
* Overloaded insertion operator, prints out the contents of the object
*/
template <typename T>
std::ostream& operator<<(std::ostream& os, const Node<T>& n)
{
	os << n.obj << std::endl;
	return os;
}