#pragma once
#include "BinarySearchTree.h"
#include <climits>
#include <cmath>

//------------------------------------------------------------
// Protected Utility Methods Section:
// Recursive helper methods for the public methods.
//------------------------------------------------------------
template<class DataType>
int BinarySearchTree<DataType>::getHeightHelper(BinaryNode<DataType>* subTreePtr) const {
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
int BinarySearchTree<DataType>::getNumberOfNodesHelper(BinaryNode<DataType>* subTreePtr) const {
	if (subTreePtr){
		return 1 + getNumberOfNodesHelper(subTreePtr->getRightChildPtr()) + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr());
	}
	return 0;
}

template<class DataType>
DataType BinarySearchTree<DataType>::getMaxItemHelper(BinaryNode<DataType> * subTreePtr) const {
	if (subTreePtr->getRightChildPtr()){
		return getMaxItemHelper(subTreePtr->getRightChildPtr());
	}
	return subTreePtr->getItem();
}

template<class DataType>
DataType BinarySearchTree<DataType>::getMinItemHelper(BinaryNode<DataType> * subTreePtr) const {
	if (subTreePtr->getLeftChildPtr()){
		return getMinItemHelper(subTreePtr->getLeftChildPtr());
	}
	return subTreePtr->getItem();
}

template<class DataType>
bool BinarySearchTree<DataType>::isBSTHelper(BinaryNode<DataType>* subTreePtr, int min, int max) const {
	if (!subTreePtr)
		return true;

	if (subTreePtr->getItem() >= min && subTreePtr->getItem() < max &&
		isBSTHelper(subTreePtr->getLeftChildPtr(), min, subTreePtr->getItem()) &&
		isBSTHelper(subTreePtr->getRightChildPtr(), subTreePtr->getItem(), max))
		return true;

	return false;
}

template<class DataType>
bool BinarySearchTree<DataType>::isFullHelper(BinaryNode<DataType> * subTreePtr) const {
	if (pow(2, getHeightHelper(subTreePtr)) -1 == getNumberOfNodesHelper(subTreePtr))
		return true;
	return false;
}

template<class DataType>
BinaryNode<DataType> * BinarySearchTree<DataType>::MakeBalancedHelper(BinaryNode<DataType> * subTreePtr, DataType * arr, int n, int index)  {
	BinaryNode<DataType> * newNode = new BinaryNode<DataType>(arr[index]);
	subTreePtr = SortedAdd(subTreePtr, newNode);

	if (n != 1)
		//first half of array
			subTreePtr->setLeftChildPtr(MakeBalancedHelper(subTreePtr->getLeftChildPtr(), arr, n/2, n/4));

	if (index + 1 < n)
		//second half of array
			subTreePtr->setRightChildPtr(MakeBalancedHelper(subTreePtr->getRightChildPtr(), &arr[index+1], (n-1)/2, (n-1)/4));

	return subTreePtr;
}

// Recursively deletes all nodes from the tree.
template<class DataType>
void BinarySearchTree<DataType>::destroyTree(BinaryNode<DataType>* subTreePtr){
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
BinaryNode<DataType>* BinarySearchTree<DataType>::SortedAdd(BinaryNode<DataType>* subTreePtr, BinaryNode<DataType>* newNodePtr){

	if (subTreePtr == nullptr)
		return newNodePtr;

	BinaryNode<DataType>* leftPtr = subTreePtr->getLeftChildPtr();
	BinaryNode<DataType>* rightPtr = subTreePtr->getRightChildPtr();

	if (newNodePtr->getItem() > subTreePtr->getItem()){
		//if newNode > subTree, add it in right subTree
		rightPtr = SortedAdd(rightPtr, newNodePtr);
		subTreePtr->setRightChildPtr(rightPtr);
	}

	else {
		//if newNode < subTree, add it in left subTree
		leftPtr = SortedAdd(leftPtr, newNodePtr);
		subTreePtr->setLeftChildPtr(leftPtr);
	}

	return subTreePtr;
}

// Removes the target value from the tree by calling moveValuesUpTree
// to overwrite value with value from child.
template<class DataType>
BinaryNode<DataType>* BinarySearchTree<DataType>::removeValue(BinaryNode<DataType>* subTreePtr, const DataType target, bool& success){
	success = false;
	if (!subTreePtr)
		return subTreePtr;

	if (subTreePtr->getItem() == target){
		success = true;
		subTreePtr = moveValuesUpTree(subTreePtr);
	}
	else if (subTreePtr->getItem() > target) 
		subTreePtr->setLeftChildPtr( removeValue(subTreePtr->getLeftChildPtr(), target, success) );
	else 
		subTreePtr->setRightChildPtr( removeValue(subTreePtr->getRightChildPtr(), target, success) );

	return subTreePtr;
}


// Copies values up the tree to overwrite value in current node until
// a leaf is reached; the leaf is then removed, since its value is
// stored in the parent.
template<class DataType>
BinaryNode<DataType>* BinarySearchTree<DataType>::moveValuesUpTree(BinaryNode<DataType>* subTreePtr){

	if (!subTreePtr->getLeftChildPtr() && !subTreePtr->getRightChildPtr()){
		//if it has no chidlren
		delete subTreePtr;
		subTreePtr = nullptr;
		return nullptr;
	}
	else if (!subTreePtr->getLeftChildPtr() && subTreePtr->getRightChildPtr()){
		//if it has right child only
		//1. Get min Value in right subTree
		DataType minValue = getMinItemHelper(subTreePtr->getRightChildPtr());
		//2. Swap their values
		subTreePtr->setItem(minValue);
		//3. Remove the min Node
		subTreePtr->setRightChildPtr( DeleteMin(subTreePtr->getRightChildPtr()) );
	}
	else { //if it has left child only or both, I would go left
		//1. Get max Value in left subTree
		DataType maxValue = getMaxItemHelper(subTreePtr->getLeftChildPtr());
		//2. Put Max in SubTree
		subTreePtr->setItem(maxValue);
		//3. Remove the Max Node from the left subTree
		subTreePtr->setLeftChildPtr(DeleteMax(subTreePtr->getLeftChildPtr()));
	}
	return subTreePtr;
}

//Delete max node in a subTree
template<class DataType>
BinaryNode<DataType> * BinarySearchTree<DataType>::DeleteMax(BinaryNode<DataType> * subTree){
	if (!subTree) return subTree;
	BinaryNode<DataType> * left = subTree->getLeftChildPtr();
	BinaryNode<DataType> * right = subTree->getRightChildPtr();

	if (right){
		subTree->setRightChildPtr(DeleteMax(right));
	}
	else if (left){
		subTree->setLeftChildPtr(nullptr);
		delete subTree;
		subTree = nullptr;
		return left;
	}

	else {
		delete subTree;
		subTree = nullptr;
	}
	return subTree;
}

//Delete min node in a subTree
template<class DataType>
BinaryNode<DataType> * BinarySearchTree<DataType>::DeleteMin(BinaryNode<DataType> * subTree){
	if (!subTree) return subTree;
	BinaryNode<DataType> * left = subTree->getLeftChildPtr();
	BinaryNode<DataType> * right = subTree->getRightChildPtr();

	if (left){
		subTree->setLeftChildPtr(DeleteMin(left));
	}
	else if (right){
		subTree->setRightChildPtr(nullptr);
		delete subTree;
		subTree = nullptr;
		return right;
	}
	else {
		delete subTree;
		subTree = nullptr;
	}
	return subTree;
}


// Recursively searches for target value in the tree by using a
// preorder traversal.
template<class DataType>
BinaryNode<DataType>* BinarySearchTree<DataType>::BinarySearch(BinaryNode<DataType>* treePtr, const DataType& target, bool& success) const {
	success = false;

	//if nullptr
	if (!treePtr)
		return treePtr;

	if (treePtr->getItem() == target){
		success = true;
		return treePtr;
	}
	else if (treePtr->getItem() > target){
		//target is less than treePtr->item
		BinaryNode<DataType> * left = BinarySearch(treePtr->getLeftChildPtr(), target, success);
		if (success)
			return left;
	}
	else{
		//target is larger than treePtr->item
		BinaryNode<DataType> * right = BinarySearch(treePtr->getRightChildPtr(), target, success);
		if (right)
			return right;
	}

	return nullptr;
}

// Copies the tree rooted at treePtr and returns a pointer to
// the copy.
template<class DataType>
BinaryNode<DataType>* BinarySearchTree<DataType>::copyTree( const BinaryNode<DataType>* treeRootPtr) const {
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

//Read BST Data in inorder traversal and stores them in an Array
template<class DataType>
void BinarySearchTree<DataType>::ReadTree (BinaryNode<DataType> * treePtr, DataType * arr, int &index) const {
	if (treePtr){
		ReadTree(treePtr->getLeftChildPtr(), arr, index);
		DataType item = treePtr->getItem();
		arr[index++] = item;
		ReadTree(treePtr->getRightChildPtr(), arr, index);
	}
}


// Recursive traversal helper methods:
//Breadth-First traversal:
template<class DataType>
void BinarySearchTree<DataType>::LevelOrder( void visit(DataType&), BinaryNode<DataType>* treePtr, LinkedQueue <BinaryNode<DataType>*> &Q) const {
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
void BinarySearchTree<DataType>::preorder( void visit(DataType&), BinaryNode<DataType>* treePtr) const {
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
void BinarySearchTree<DataType>::inorder( void visit(DataType&), BinaryNode<DataType>* treePtr) const {
	//visit is a function sent to Inorder function (remember sort according to a user-defined function?)
	if (treePtr){
		inorder(visit, treePtr->getLeftChildPtr());
		DataType item = treePtr->getItem();
		visit(item);
		inorder(visit, treePtr->getRightChildPtr());
	}

}

//Without recursion
//void BinarySearchTree<DataType>::inorder( void visit(DataType&), BinaryNode<DataType>* treePtr) const {
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
void BinarySearchTree<DataType>::postorder( void visit(DataType&), BinaryNode<DataType>* treePtr) const {
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
BinarySearchTree<DataType>::BinarySearchTree(){
	root = nullptr;
}

template<class DataType>
BinarySearchTree<DataType>::BinarySearchTree( const DataType& rootItem){
	root = new BinaryNode<DataType>(rootItem);
}

//Copy Constructor
template<class DataType>
BinarySearchTree<DataType>::BinarySearchTree( const BinarySearchTree<DataType>& tree){
	//*this = tree; //it will be done using the operator = overloading
	root = copyTree(tree.root);
}

//Destructor
template<class DataType>
BinarySearchTree<DataType>::~BinarySearchTree(){
	if (!isEmpty())
		destroyTree(root);
}

//------------------------------------------------------------
// Public BinarySearchTree General Methods Section.
//------------------------------------------------------------
template<class DataType>
bool BinarySearchTree<DataType>::isEmpty() const {
	return root == nullptr;
}

template<class DataType>
int BinarySearchTree<DataType>::getHeight() const {
	return getHeightHelper(root);
}

template<class DataType>
int BinarySearchTree<DataType>::getNumberOfNodes() const {
	return getNumberOfNodesHelper(root);
}

template<class DataType>
DataType BinarySearchTree<DataType>::getMaxItem() const {
	if (isEmpty()) return INT_MIN;
	return getMaxItemHelper(root);
}

template<class DataType>
DataType BinarySearchTree<DataType>::getMinItem() const {
	if (isEmpty()) return INT_MIN;
	return getMinItemHelper(root);
}


template<class DataType>
DataType BinarySearchTree<DataType>::getRootData() const {
	return root->getItem();
}

template<class DataType>
bool BinarySearchTree<DataType>::add( const DataType& newData) { // Adds a node
	BinaryNode<DataType> * newNode = new BinaryNode<DataType>(newData);
	root = SortedAdd(root, newNode);
	return true;
}

template<class DataType>
bool BinarySearchTree<DataType>::remove( const DataType& data) { // Removes a node
	bool success = false;
	root = removeValue(root, data, success);
	return success;
}

template<class DataType>
void BinarySearchTree<DataType>::clear(){
	destroyTree(root);
	root = nullptr;
}

template<class DataType>
bool BinarySearchTree<DataType>::contains( const DataType& anEntry) const {
	bool success = false;
	BinarySearch(root, anEntry, success);
	return success;
}

template<class DataType>
bool BinarySearchTree<DataType>::isBST() const {
	return isBSTHelper(root, INT_MIN, INT_MAX);
}

template<class DataType>
bool BinarySearchTree<DataType>::isFull() const {
	return isFullHelper(root);
}

template<class DataType>
bool BinarySearchTree<DataType>::MakeBalanced() {
	if (isEmpty())
		return false;

	int n = getNumberOfNodes();
	
	DataType * list = new DataType[n];
	//store data in a list
	int index = 0;
	ReadTree(root, list, index);
	//destroy current Tree
	clear();
	//construct new Balanced Tree
	root = MakeBalancedHelper(root, list, n, n/2);
	//Deallocate the array
	delete [] list;

	if (getHeightHelper(root->getLeftChildPtr()) == getHeightHelper(root->getRightChildPtr()))
		return true;

	return false;
}

//------------------------------------------------------------
// Public Traversals Section.
//------------------------------------------------------------
template<class DataType>
void BinarySearchTree<DataType>::LevelOrderTraverse( void visit(DataType&)) const {
	LinkedQueue <BinaryNode<DataType>*> Q;
	LevelOrder(visit, root, Q);
}

template<class DataType>
void BinarySearchTree<DataType>::preorderTraverse( void visit(DataType&)) const {
	preorder(visit, root);
}

template<class DataType>
void BinarySearchTree<DataType>::inorderTraverse( void visit(DataType&)) const {
	inorder(visit, root);
}

template<class DataType>
void BinarySearchTree<DataType>::postorderTraverse( void visit(DataType&)) const {
	postorder(visit, root);
}


//------------------------------------------------------------
// Overloaded Operator Section.
//------------------------------------------------------------
template<class DataType>
BinarySearchTree<DataType> & BinarySearchTree<DataType>::operator = (const BinarySearchTree<DataType> & rightHandSide){
	clear();
	root = copyTree(rightHandSide.root);
	return *this;
}

