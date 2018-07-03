#pragma once
#include "AVLTree.h"
#include <climits>
#include <cmath>

//------------------------------------------------------------
// Protected Utility Methods Section:
// Recursive helper methods for the public methods.
//------------------------------------------------------------
template<class DataType>
int AVLTree<DataType>::getHeightHelper(BinaryNode<DataType>* subTreePtr) const {
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
int AVLTree<DataType>::getNumberOfNodesHelper(BinaryNode<DataType>* subTreePtr) const {
	if (subTreePtr){
		return 1 + getNumberOfNodesHelper(subTreePtr->getRightChildPtr()) + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr());
	}
	return 0;
}

template<class DataType>
DataType AVLTree<DataType>::getMaxItemHelper(BinaryNode<DataType> * subTreePtr) const {
	if (subTreePtr->getRightChildPtr()){
		return getMaxItemHelper(subTreePtr->getRightChildPtr());
	}
	return subTreePtr->getItem();
}

template<class DataType>
DataType AVLTree<DataType>::getMinItemHelper(BinaryNode<DataType> * subTreePtr) const {
	if (subTreePtr->getLeftChildPtr()){
		return getMinItemHelper(subTreePtr->getLeftChildPtr());
	}
	return subTreePtr->getItem();
}

template<class DataType>
bool AVLTree<DataType>::isFullHelper(BinaryNode<DataType> * subTreePtr) const {
	if (pow(2, getHeightHelper(subTreePtr)) -1 == getNumberOfNodesHelper(subTreePtr))
		return true;
	return false;
}

////Rotate Left to restore balance if H-right > H-left
//template<class DataType>	
//BinaryNode<DataType> * AVLTree<DataType>::RotateLeft(BinaryNode<DataType> * subTree) {
//	BinaryNode<DataType> * right = subTree->getRightChildPtr();
//	BinaryNode<DataType> * newRight = right->getLeftChildPtr();
//	subTree->setRightChildPtr(newRight);
//	right->setLeftChildPtr(subTree);
//	return right;
//}
//	
////Rotate Right to restore balance if H-left > H-right
//template<class DataType>	
//BinaryNode<DataType> * AVLTree<DataType>::RotateRight(BinaryNode<DataType> * subTree) {
//	BinaryNode<DataType> * left = subTree->getLeftChildPtr();
//	BinaryNode<DataType> * newLeft = left->getRightChildPtr();
//	subTree->setLeftChildPtr(newLeft);
//	left->setRightChildPtr(subTree);
//	return left;
//}
//
////After Sorted Addition, I restore Balance of AVL Tree
//template<class DataType>	
//BinaryNode<DataType> * AVLTree<DataType>::RestoreBalance(BinaryNode<DataType> * subTree){
//	if (!subTree) return nullptr;
//
//	subTree->setLeftChildPtr(RestoreBalance(subTree->getLeftChildPtr()));
//	subTree->setRightChildPtr(RestoreBalance(subTree->getRightChildPtr()));
//
//	if (!isEqualHeights(subTree)){
//		int diffH = getHeightHelper(subTree->getLeftChildPtr()) - getHeightHelper(subTree->getRightChildPtr());
//		int diffNodes = getNumberOfNodesHelper(subTree->getLeftChildPtr()) - getNumberOfNodesHelper(subTree->getRightChildPtr());
//		if ((diffH == 1 && diffNodes > 1) || diffH > 1)
//			//if H-left > H-right
//			subTree = RotateRight(subTree);
//		
//		if ((diffH == -1 && diffNodes < -1) || diffH < -1)
//			//if H-left < H-right
//				subTree = RotateLeft(subTree);
//	}
//	return subTree;
//}
//
////Checks the balance of a specific Node
//template<class DataType>
//bool AVLTree<DataType>::isEqualHeights(BinaryNode<DataType> * subTreePtr) const {
//	int diff = getHeightHelper(subTreePtr->getLeftChildPtr()) - getHeightHelper(subTreePtr->getRightChildPtr());
//	if (diff == 0)
//		return true;
//	return false;
//}

//Helpers for Balancing the AVL Tree
template<class DataType>
BinaryNode<DataType> * AVLTree<DataType>::MakeBalancedHelper(BinaryNode<DataType> * subTreePtr, DataType * arr, int n, int index) {
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

//Read BST Data in inorder traversal and stores them in an Array
template<class DataType>
void AVLTree<DataType>::ReadTree (BinaryNode<DataType> * treePtr, DataType * arr, int &index) const {
	if (treePtr){
		ReadTree(treePtr->getLeftChildPtr(), arr, index);
		DataType item = treePtr->getItem();
		arr[index++] = item;
		ReadTree(treePtr->getRightChildPtr(), arr, index);
	}
}

template<class DataType>
bool AVLTree<DataType>::MakeBalanced() {
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


// Recursively deletes all nodes from the tree.
template<class DataType>
void AVLTree<DataType>::destroyTree(BinaryNode<DataType>* subTreePtr){
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
BinaryNode<DataType>* AVLTree<DataType>::SortedAdd(BinaryNode<DataType>* subTreePtr, BinaryNode<DataType>* newNodePtr){

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
BinaryNode<DataType>* AVLTree<DataType>::removeValue(BinaryNode<DataType>* subTreePtr, const DataType target, bool& success){
	success = false;
	if (!subTreePtr)
		return subTreePtr;

	if (subTreePtr->getItem() == target){
		success = true;
		subTreePtr = moveValuesUpTree(subTreePtr);
	}
	else if (subTreePtr->getItem() > target){
		BinaryNode<DataType> * left = subTreePtr->getLeftChildPtr();
		subTreePtr->setLeftChildPtr( removeValue(left , target, success) );
	}
	else {
		BinaryNode<DataType> * right = subTreePtr->getRightChildPtr();
		subTreePtr->setRightChildPtr( removeValue(right, target, success) );
	}

	return subTreePtr;
}


// Copies values up the tree to overwrite value in current node until
// a leaf is reached; the leaf is then removed, since its value is
// stored in the parent.
template<class DataType>
BinaryNode<DataType>* AVLTree<DataType>::moveValuesUpTree(BinaryNode<DataType>* subTreePtr){
	if (!subTreePtr->getLeftChildPtr() && !subTreePtr->getRightChildPtr()){
		//if it has no chidlren
		delete subTreePtr;
		subTreePtr = nullptr;
		return nullptr;
	}
	else if (!subTreePtr->getLeftChildPtr() && subTreePtr->getRightChildPtr()){
		//if it has right child only
		//1. Get min Value in right subTree
		bool dummy = true;
		DataType minValue = getMaxItemHelper(subTreePtr->getRightChildPtr());
		//2. Swap their values
		subTreePtr->setItem(minValue);
		//3. Remove the newNode
		subTreePtr->setRightChildPtr( DeleteMin(subTreePtr->getRightChildPtr()) );
	}
	else {
		//if it has left child only or both, I would go left

		//1. Get max Value in left subTree
		bool dummy = true;
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
BinaryNode<DataType> * AVLTree<DataType>::DeleteMax(BinaryNode<DataType> * subTree){
	if (!subTree) return subTree;
	BinaryNode<DataType> * right = subTree->getRightChildPtr();
	if (right){
		subTree->setRightChildPtr(DeleteMax(right));
	}
	else {
		delete subTree;
		subTree = nullptr;
	}
	return subTree;
}

//Delete min node in a subTree
template<class DataType>
BinaryNode<DataType> * AVLTree<DataType>::DeleteMin(BinaryNode<DataType> * subTree){
	if (!subTree) return subTree;
	BinaryNode<DataType> * left = subTree->getLeftChildPtr();
	if (left){
		subTree->setLeftChildPtr(DeleteMax(left));
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
BinaryNode<DataType>* AVLTree<DataType>::BinarySearch(BinaryNode<DataType>* treePtr, const DataType& target, bool& success) const {
	success = false;

	//if nullptr
	if (!treePtr)
		return treePtr;

	if (treePtr->getItem() == target){
		success = true;
		return treePtr;
	}
	else if (treePtr->getItem() > target){
		BinaryNode<DataType> * left = BinarySearch(treePtr->getLeftChildPtr(), target, success);
		if (success)
			return left;
	}
	else{
		BinaryNode<DataType> * right = BinarySearch(treePtr->getRightChildPtr(), target, success);
		if (right)
			return right;
	}

	return nullptr;
}

// Copies the tree rooted at treePtr and returns a pointer to
// the copy.
template<class DataType>
BinaryNode<DataType>* AVLTree<DataType>::copyTree( const BinaryNode<DataType>* treeRootPtr) const {
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
void AVLTree<DataType>::LevelOrder( void visit(DataType&), BinaryNode<DataType>* treePtr, LinkedQueue <BinaryNode<DataType>*> &Q) const {
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
void AVLTree<DataType>::preorder( void visit(DataType&), BinaryNode<DataType>* treePtr) const {
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
void AVLTree<DataType>::inorder( void visit(DataType&), BinaryNode<DataType>* treePtr) const {
	//visit is a function sent to Inorder function (remember sort according to a user-defined function?)
	if (treePtr){
		inorder(visit, treePtr->getLeftChildPtr());
		DataType item = treePtr->getItem();
		visit(item);
		inorder(visit, treePtr->getRightChildPtr());
	}

}

//Without recursion
//void AVLTree<DataType>::inorder( void visit(DataType&), BinaryNode<DataType>* treePtr) const {
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
void AVLTree<DataType>::postorder( void visit(DataType&), BinaryNode<DataType>* treePtr) const {
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
AVLTree<DataType>::AVLTree(){
	root = nullptr;
}

template<class DataType>
AVLTree<DataType>::AVLTree( const DataType& rootItem){
	root = new BinaryNode<DataType>(rootItem);
}

//Copy Constructor
template<class DataType>
AVLTree<DataType>::AVLTree( const AVLTree<DataType>& tree){
	//*this = tree; //it will be done using the operator = overloading
	root = copyTree(tree.root);
}

//Destructor
template<class DataType>
AVLTree<DataType>::~AVLTree(){
	if (!isEmpty())
		destroyTree(root);
}

//------------------------------------------------------------
// Public AVLTree General Methods Section.
//------------------------------------------------------------
template<class DataType>
bool AVLTree<DataType>::isEmpty() const {
	return root == nullptr;
}

template<class DataType>
int AVLTree<DataType>::getHeight() const {
	return getHeightHelper(root);
}

template<class DataType>
int AVLTree<DataType>::getNumberOfNodes() const {
	return getNumberOfNodesHelper(root);
}

template<class DataType>
DataType AVLTree<DataType>::getMaxItem() const {
	if (isEmpty()) return INT_MIN;
	return getMaxItemHelper(root);
}

template<class DataType>
DataType AVLTree<DataType>::getMinItem() const {
	if (isEmpty()) return INT_MIN;
	return getMinItemHelper(root);
}


template<class DataType>
DataType AVLTree<DataType>::getRootData() const {
	assert(!isEmpty());
	return root->getItem();
}

template<class DataType>
bool AVLTree<DataType>::add( const DataType& newData) { // Adds a node
	BinaryNode<DataType> * newNode = new BinaryNode<DataType>(newData);
	root = SortedAdd(root, newNode);
	MakeBalanced();
	return true;
}

template<class DataType>
bool AVLTree<DataType>::remove( const DataType& data) { // Removes a node
	bool success = false;
	root = removeValue(root, data, success);
	MakeBalanced();
	return success;
}

template<class DataType>
void AVLTree<DataType>::clear(){
	destroyTree(root);
	root = nullptr;
}

template<class DataType>
bool AVLTree<DataType>::contains( const DataType& anEntry) const {
	bool success = false;
	BinarySearch(root, anEntry, success);
	return success;
}

template<class DataType>
bool AVLTree<DataType>::isFull() const {
	return isFullHelper(root);
}


//------------------------------------------------------------
// Public Traversals Section.
//------------------------------------------------------------
template<class DataType>
void AVLTree<DataType>::LevelOrderTraverse( void visit(DataType&)) const {
	LinkedQueue <BinaryNode<DataType>*> Q;
	LevelOrder(visit, root, Q);
}

template<class DataType>
void AVLTree<DataType>::preorderTraverse( void visit(DataType&)) const {
	preorder(visit, root);
}

template<class DataType>
void AVLTree<DataType>::inorderTraverse( void visit(DataType&)) const {
	inorder(visit, root);
}

template<class DataType>
void AVLTree<DataType>::postorderTraverse( void visit(DataType&)) const {
	postorder(visit, root);
}


//------------------------------------------------------------
// Overloaded Operator Section.
//------------------------------------------------------------
template<class DataType>
AVLTree<DataType> & AVLTree<DataType>::operator = (const AVLTree<DataType> & rightHandSide){
	root = copyTree(rightHandSide.root);
	return *this;
}

