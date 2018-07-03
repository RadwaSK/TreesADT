#pragma once
#include "BinaryTree.h"
#include "..\Helper ADT's\LinkedStack.cpp"
#include <climits>
#include <cmath>

//------------------------------------------------------------
// Protected Utility Methods Section:
// Recursive helper methods for the public methods.
//------------------------------------------------------------
template<class DataType>
int BinaryTree<DataType>::getHeightHelper(BinaryNode<DataType>* subTreePtr) const {
	if (subTreePtr){
		int rightCount, leftCount;
		leftCount = getHeightHelper(subTreePtr->getLeftChildPtr());
		rightCount = getHeightHelper(subTreePtr->getRightChildPtr());
		int max = (leftCount > rightCount) ? leftCount : rightCount;
		return 1 + max;
	}
	return 0;

}

template<class DataType>
int BinaryTree<DataType>::getNumberOfNodesHelper(BinaryNode<DataType>* subTreePtr) const {
	if (subTreePtr){
		return 1 + getNumberOfNodesHelper(subTreePtr->getRightChildPtr()) + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr());
	}
	return 0;
}


template<class DataType>
bool BinaryTree<DataType>::isBSTHelper(BinaryNode<DataType>* subTreePtr, int min, int max) const {
	if (!subTreePtr)
		return true;

	if (subTreePtr->getItem() >= min && subTreePtr->getItem() < max &&
		isBSTHelper(subTreePtr->getLeftChildPtr(), min, subTreePtr->getItem()) &&
		isBSTHelper(subTreePtr->getRightChildPtr(), subTreePtr->getItem(), max))
		return true;

	return false;
}

template<class DataType>
bool BinaryTree<DataType>::isFullHelper(BinaryNode<DataType> * subTreePtr) const {
	if (pow(2, getHeightHelper(subTreePtr)) -1 == getNumberOfNodesHelper(subTreePtr))
		return true;
	return false;
}

template<class DataType>
bool BinaryTree<DataType>::isCompleteHelper(BinaryNode<DataType> * root) const {
	if (root){

		//if it has right child only
		if ( !root->getLeftChildPtr() && root->getRightChildPtr() )
			return false;

		//if root is NOT Balanced or H-left > H-right
		int diff = getHeightHelper( root->getLeftChildPtr() ) - getHeightHelper( root->getRightChildPtr() );
		if ( diff != 1 && diff != 0 )
			return false;

		//other wise check the Completion of left and right subTrees
		return isCompleteHelper( root->getLeftChildPtr() ) && isCompleteHelper( root->getRightChildPtr() );
	}
	//if nullptr, return true
	return true;
}

// Recursively deletes all nodes from the tree.
template<class DataType>
void BinaryTree<DataType>::destroyTree(BinaryNode<DataType>* subTreePtr){
	if (subTreePtr){
		if (subTreePtr->getLeftChildPtr()) //to prevent unneeded recusive calls
			destroyTree(subTreePtr->getLeftChildPtr());

		if (subTreePtr->getRightChildPtr()) //to prevent unneeded recusive calls
			destroyTree(subTreePtr->getRightChildPtr());

		delete subTreePtr;
		subTreePtr = nullptr;
	}
}

// Recursively adds a new node to the tree in a left/right fashion to
// keep the tree balanced.
template<class DataType>
BinaryNode<DataType>* BinaryTree<DataType>::balancedAdd(BinaryNode<DataType>* subTreePtr, BinaryNode<DataType>* newNodePtr){

	if (subTreePtr == nullptr)
		return newNodePtr;

	BinaryNode<DataType>* leftPtr = subTreePtr->getLeftChildPtr();
	BinaryNode<DataType>* rightPtr = subTreePtr->getRightChildPtr();

	if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr)){
		rightPtr = balancedAdd(rightPtr, newNodePtr);
		subTreePtr->setRightChildPtr(rightPtr);
	}

	else {
		leftPtr = balancedAdd(leftPtr, newNodePtr);
		subTreePtr->setLeftChildPtr(leftPtr);
	}

	return subTreePtr;
}


// Removes the target value from the tree by calling moveValuesUpTree
// to overwrite value with value from child.
template<class DataType>
BinaryNode<DataType>* BinaryTree<DataType>::removeValue(BinaryNode<DataType>* subTreePtr, const DataType target, bool& success){
	success = false;
	if (!subTreePtr)
		return subTreePtr;

	if (subTreePtr->getItem() == target){
		success = true;
		subTreePtr = moveValuesUpTree(subTreePtr);
		return subTreePtr;
	}

	else {
		subTreePtr->setLeftChildPtr( removeValue(subTreePtr->getLeftChildPtr(), target, success) );
		if (success)
			return subTreePtr;

		subTreePtr->setRightChildPtr( removeValue(subTreePtr->getRightChildPtr(), target, success) );
		if (success)
			return subTreePtr;
	}
	return subTreePtr;
}


// Copies values up the tree to overwrite value in current node until
// a leaf is reached; the leaf is then removed, since its value is
// stored in the parent.
template<class DataType>
BinaryNode<DataType>* BinaryTree<DataType>::moveValuesUpTree(BinaryNode<DataType>* subTreePtr){

	if (!subTreePtr->getLeftChildPtr() && !subTreePtr->getRightChildPtr()){
		//if it has no chidlren
		delete subTreePtr;
		subTreePtr = nullptr;
		return nullptr;

	}
	else if (!subTreePtr->getLeftChildPtr() && subTreePtr->getRightChildPtr()){
		//if it has right child only
		subTreePtr->setItem(subTreePtr->getRightChildPtr()->getItem());
		subTreePtr->setRightChildPtr( moveValuesUpTree(subTreePtr->getRightChildPtr()) );
	}
	else{
		//if it has left child only or both, I would go left
		subTreePtr->setItem(subTreePtr->getLeftChildPtr()->getItem());
		subTreePtr->setLeftChildPtr( moveValuesUpTree(subTreePtr->getLeftChildPtr()) );
	}
	
	return subTreePtr;
}


// Recursively searches for target value in the tree by using a
// preorder traversal.
template<class DataType>
BinaryNode<DataType>* BinaryTree<DataType>::findNode(BinaryNode<DataType>* treePtr, const DataType& target, bool& success) const {
	success = false;

	//if nullptr
	if (!treePtr)
		return treePtr;

	if (treePtr->getItem() == target){
		success = true;
		return treePtr;
	}

	BinaryNode<DataType> * left = findNode(treePtr->getLeftChildPtr(), target, success);
	if (left)
		return left;

	BinaryNode<DataType> * right = findNode(treePtr->getRightChildPtr(), target, success);
	if (right)
		return right;

	return nullptr;

}


// Copies the tree rooted at treePtr and returns a pointer to
// the copy.
template<class DataType>
BinaryNode<DataType>* BinaryTree<DataType>::copyTree( const BinaryNode<DataType>* treeRootPtr) const {
	BinaryNode<DataType> * newTreeRoot = nullptr;
	if (treeRootPtr){
		//copy current Node
		newTreeRoot = new BinaryNode<DataType>(treeRootPtr->getItem());
		//copy left subtree
		newTreeRoot->setLeftChildPtr(copyTree(treeRootPtr->getLeftChildPtr()));
		//copy right subtree
		newTreeRoot->setRightChildPtr(copyTree(treeRootPtr->getRightChildPtr()));
	}
	return newTreeRoot;
}


// Recursive traversal helper methods:
//Breadth-First traversal:
template<class DataType>
void BinaryTree<DataType>::LevelOrder( void visit(DataType&), BinaryNode<DataType>* treePtr, LinkedQueue <BinaryNode<DataType>*> &Q) const {
	if (treePtr){
		DataType item = treePtr->getItem();
		visit(item);

		if (treePtr->getLeftChildPtr())
			Q.enqueue(treePtr->getLeftChildPtr());
		if (treePtr->getRightChildPtr())
			Q.enqueue(treePtr->getRightChildPtr());

		if (Q.isEmpty())
			return;

		treePtr = Q.peekFront();
		Q.dequeue();
		LevelOrder(visit, treePtr, Q);
	}

}

//Depth-First Traversal:
template<class DataType>
//root, left, right
void BinaryTree<DataType>::preorder( void visit(DataType&), BinaryNode<DataType>* treePtr) const {
	if (treePtr){
		DataType item = treePtr->getItem();
		visit(item);
		preorder(visit, treePtr->getLeftChildPtr());
		preorder(visit, treePtr->getRightChildPtr());
	}
}

template<class DataType>
//left, root, right

//with recursion
void BinaryTree<DataType>::inorder( void visit(DataType&), BinaryNode<DataType>* treePtr) const {
	//visit is a function sent to Inorder function (remember sort according to a user-defined function?)
	if (treePtr){
		inorder(visit, treePtr->getLeftChildPtr());
		DataType item = treePtr->getItem();
		visit(item);
		inorder(visit, treePtr->getRightChildPtr());
	}

}

//Without recursion
//void BinaryTree<DataType>::inorder( void visit(DataType&), BinaryNode<DataType>* treePtr) const {
//	LinkedStack < BinaryNode <DataType> * > S;
//	BinaryNode <DataType> * currPtr = root;
//	bool done = false;
//
//	while (!done){
//		if (currPtr){
//			S.push(currPtr);
//			currPtr = currPtr->getLeftChildPtr();
//		}
//		else {
//			//I reached the most left node, so I should
//			//traverse the last node and head right
//			if (!S.isEmpty()){
//				//if I still have nodes to traverse
//				currPtr = S.pop();
//				DataType item = currPtr->getItem();
//				visit(item);
//				//traverse Right subTree
//				currPtr = currPtr->getRightChildPtr();
//			}
//			else
//				done = true;
//		}
//	}
//}

template<class DataType>
//left, right, root
void BinaryTree<DataType>::postorder( void visit(DataType&), BinaryNode<DataType>* treePtr) const {
	if (treePtr){
		postorder(visit, treePtr->getLeftChildPtr());
		postorder(visit, treePtr->getRightChildPtr());
		DataType item = treePtr->getItem();
		visit(item);
	}
}


//------------------------------------------------------------
// Constructor and Destructor Section.
//------------------------------------------------------------
template<class DataType>
BinaryTree<DataType>::BinaryTree(){
	root = nullptr;
}

template<class DataType>
BinaryTree<DataType>::BinaryTree( const DataType& rootItem){
	root = new BinaryNode<DataType>(rootItem);
}

template<class DataType>
BinaryTree<DataType>::BinaryTree( const DataType& rootItem, const BinaryTree<DataType>* leftTreePtr, const BinaryTree<DataType>* rightTreePtr){
	root = new BinaryNode<DataType>(rootItem, copyTree(leftTreePtr->root), copyTree(rightTreePtr->root));
}

//Copy Constructor
template<class DataType>
BinaryTree<DataType>::BinaryTree( const BinaryTree<DataType>& tree){
	*this = tree; //it will be done using the operator = overloading
	//root = copyTree(tree->root);
}

//Destructor
template<class DataType>
BinaryTree<DataType>::~BinaryTree(){
	destroyTree(root);
}

//------------------------------------------------------------
// Public BinaryTree General Methods Section.
//------------------------------------------------------------
template<class DataType>
bool BinaryTree<DataType>::isEmpty() const {
	return root == nullptr;
}

template<class DataType>
bool BinaryTree<DataType>::isFull() const {
	return isFullHelper(root);
}

template<class DataType>
int BinaryTree<DataType>::getHeight() const {
	return getHeightHelper(root);
}

template<class DataType>
int BinaryTree<DataType>::getNumberOfNodes() const {
	return getNumberOfNodesHelper(root);
}


template<class DataType>
DataType BinaryTree<DataType>::getRootData() const {
	return root->getItem();
}

template<class DataType>
void BinaryTree<DataType>::setRootData( const DataType& newData){
	root->setItem(newData);
}

template<class DataType>
bool BinaryTree<DataType>::add( const DataType& newData) { // Adds a node
	BinaryNode<DataType> * newNode = new BinaryNode<DataType>(newData);

	root = balancedAdd(root, newNode);
	return true;
}

template<class DataType>
bool BinaryTree<DataType>::remove( const DataType& data) { // Removes a node
	bool success = false;
	root = removeValue(root, data, success);
	return success;
}

template<class DataType>
void BinaryTree<DataType>::clear(){
	destroyTree(root);
	root = nullptr;
}

template<class DataType>
bool BinaryTree<DataType>::contains( const DataType& anEntry) const {
	bool success = false;
	BinaryNode<DataType> * temp = findNode(root, anEntry, success);
	return success;
}

template<class DataType>
bool BinaryTree<DataType>::isBST() const {
	return isBSTHelper(root, INT_MIN, INT_MAX);
}

template<class DataType>
bool BinaryTree<DataType>::isComplete() const {
	if (isEmpty()) return true;
	if ( isCompleteHelper(root) ){
		//Means that no Node has right branches only, and Height of
		//Right SubTree is not HIGHER than that of Left SubTree

		//if Heights are equal, Left SubTree must be Full
		if ( getHeightHelper( root->getRightChildPtr() ) == getHeightHelper( root->getLeftChildPtr() ) )
			if (isFullHelper(root->getLeftChildPtr()))
				return true;
			else
				return false;
		//if H of right SubTree is less than that of left SubTree
		//Right SubTree must be Full
		if ( getHeightHelper( root->getRightChildPtr() ) < getHeightHelper( root->getLeftChildPtr() ) )
			if (isFullHelper(root->getRightChildPtr()))
				return true;
			else
				return false;
	}
	return false;
}

template<class DataType>
bool BinaryTree<DataType>::isBalanced () const {
	if (!root) return true;
	int diff = getHeightHelper(root->getLeftChildPtr()) - getHeightHelper(root->getRightChildPtr());
	if (diff < 0) diff *= -1; //taking absolute value
	if (diff == 0 || diff == 1) return true;
	return false;
}

//------------------------------------------------------------
// Public Traversals Section.
//------------------------------------------------------------
template<class DataType>
void BinaryTree<DataType>::LevelOrderTraverse( void visit(DataType&)) const {
	LinkedQueue <BinaryNode<DataType>*> Q;
	LevelOrder(visit, root, Q);
}

template<class DataType>
void BinaryTree<DataType>::preorderTraverse( void visit(DataType&)) const {
	preorder(visit, root);
}

template<class DataType>
void BinaryTree<DataType>::inorderTraverse( void visit(DataType&)) const {
	inorder(visit, root);
}

template<class DataType>
void BinaryTree<DataType>::postorderTraverse( void visit(DataType&)) const {
	postorder(visit, root);
}


//------------------------------------------------------------
// Overloaded Operator Section.
//------------------------------------------------------------
template<class DataType>
BinaryTree<DataType> & BinaryTree<DataType>::operator = (const BinaryTree<DataType> & rightHandSide){
	clear();
	root = copyTree(rightHandSide.root);
	return *this;
}
