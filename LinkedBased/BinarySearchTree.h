#pragma once
#include "..\Helper ADT's\BinaryNode.cpp"
#include "..\Helper ADT's\LinkedQueue.cpp"
#include "..\Helper ADT's\LinkedStack.h"

template<class DataType>
class BinarySearchTree
{
	BinaryNode<DataType> * root;
protected :
	//------------------------------------------------------------
	// Protected Utility Methods Section:
	// Recursive helper methods for the public methods.
	//------------------------------------------------------------
	int getHeightHelper(BinaryNode<DataType>* subTreePtr) const ;
	int getNumberOfNodesHelper(BinaryNode<DataType>* subTreePtr) const ;
	DataType getMaxItemHelper(BinaryNode<DataType> * subTreePtr) const ;
	DataType getMinItemHelper(BinaryNode<DataType> * subTreePtr) const ;
	bool isBSTHelper(BinaryNode<DataType>* subTreePtr, int min, int max) const ;
	bool isFullHelper(BinaryNode<DataType> * subTreePtr) const ;
	BinaryNode<DataType> * MakeBalancedHelper(BinaryNode<DataType> * subTreePtr, DataType * arr, int size, int index) ;
	
	// Recursively deletes all nodes from the tree.
	void destroyTree(BinaryNode<DataType>* subTreePtr);
	
	// Recursively adds a new node to the tree in a left/right fashion to
	// keep the tree balanced.
	BinaryNode<DataType>* SortedAdd(BinaryNode<DataType>* subTreePtr, BinaryNode<DataType>* newNodePtr);
	
	// Removes the target value from the tree by calling moveValuesUpTree
	// to overwrite value with value from child.
	BinaryNode<DataType>* removeValue(BinaryNode<DataType>* subTreePtr, const DataType target, bool& success);
	
	// Copies values up the tree to overwrite value in current node until
	// a leaf is reached; the leaf is then removed, since its value is
	// stored in the parent.
	BinaryNode<DataType>* moveValuesUpTree(BinaryNode<DataType>* subTreePtr);

	//Delete max node from a subTree
	BinaryNode<DataType> * DeleteMax(BinaryNode<DataType> * subTree);
	//Delete min node from a subTree
	BinaryNode<DataType> * DeleteMin(BinaryNode<DataType> * subTree);
	
	// Recursively searches for target value in the tree by using a
	// preorder traversal.
	BinaryNode<DataType>* BinarySearch(BinaryNode<DataType>* treePtr, const DataType& target, bool& success) const ;
	
	// Copies the tree rooted at treePtr and returns a pointer to
	// the copy.
	BinaryNode<DataType>* copyTree( const BinaryNode<DataType>* treePtr) const ;
	
	//Read BST Data in inorder traversal and stores them in an Array 
	void ReadTree(BinaryNode<DataType> * treePtr, DataType * arr, int &index) const ;

	// Recursive traversal helper methods:
	void LevelOrder( void visit(DataType&), BinaryNode<DataType>* treePtr, LinkedQueue <BinaryNode<DataType>*> &Q) const ;
	void preorder( void visit(DataType&), BinaryNode<DataType>* treePtr) const ;
	void inorder( void visit(DataType&), BinaryNode<DataType>* treePtr) const ;
	void postorder( void visit(DataType&), BinaryNode<DataType>* treePtr) const ;

public :
	//------------------------------------------------------------
	// Constructor and Destructor Section.
	//------------------------------------------------------------
	BinarySearchTree();
	BinarySearchTree( const DataType& rootItem);
	BinarySearchTree( const BinarySearchTree<DataType>& tree);
	virtual ~BinarySearchTree();
	
	//------------------------------------------------------------
	// Public BinarySearchTree General Methods Section.
	//------------------------------------------------------------
	bool isEmpty() const ;
	int getHeight() const ;
	int getNumberOfNodes() const ;
	DataType getMaxItem() const ;
	DataType getMinItem() const ;
	DataType getRootData() const ;
	bool add( const DataType& newData); // Adds a node
	bool remove( const DataType& data); // Removes a node
	void clear();
	bool contains( const DataType& anEntry) const ;
	bool isBST() const ; //Checks if every subTree is a Binary Search Tree
	bool isFull() const ;
	bool MakeBalanced() ;

	//------------------------------------------------------------
	// Public Traversals Section.
	//------------------------------------------------------------
	void LevelOrderTraverse( void visit(DataType&)) const ;
	void preorderTraverse( void visit(DataType&)) const ;
	void inorderTraverse( void visit(DataType&)) const ;
	void postorderTraverse( void visit(DataType&)) const ;
	
	//------------------------------------------------------------
	// Overloaded Operator Section.
	//------------------------------------------------------------
	BinarySearchTree & operator=(const BinarySearchTree& rightHandSide);
};