#ifndef _BINARY_NODE_TREE
#define _BINARY_NODE_TREE

#include "..\Helper ADT's\BinaryNode.cpp"
#include "..\Helper ADT's\LinkedQueue.cpp"

template<class DataType>
class BinaryTree
{
	BinaryNode<DataType> * root;
protected :
	//------------------------------------------------------------
	// Protected Utility Methods Section:
	// Recursive helper methods for the public methods.
	//------------------------------------------------------------
	int getHeightHelper(BinaryNode<DataType>* subTreePtr) const ;
	int getNumberOfNodesHelper(BinaryNode<DataType>* subTreePtr) const ;
	bool isBSTHelper(BinaryNode<DataType>* subTreePtr, int min, int max) const ;
	bool isFullHelper(BinaryNode<DataType> * subTreePtr) const ;
	bool isCompleteHelper(BinaryNode<DataType> * root) const ;
	
	// Recursively deletes all nodes from the tree.
	void destroyTree(BinaryNode<DataType>* subTreePtr);
	
	// Recursively adds a new node to the tree in a left/right fashion to
	// keep the tree balanced.
	BinaryNode<DataType>* balancedAdd(BinaryNode<DataType>* subTreePtr, BinaryNode<DataType>* newNodePtr);
	
	// Removes the target value from the tree by calling moveValuesUpTree
	// to overwrite value with value from child.
	BinaryNode<DataType>* removeValue(BinaryNode<DataType>* subTreePtr, const DataType target, bool& success);
	
	// Copies values up the tree to overwrite value in current node until
	// a leaf is reached; the leaf is then removed, since its value is
	// stored in the parent.
	BinaryNode<DataType>* moveValuesUpTree(BinaryNode<DataType>* subTreePtr);
	
	// Recursively searches for target value in the tree by using a
	// preorder traversal.
	BinaryNode<DataType>* findNode(BinaryNode<DataType>* treePtr, const DataType& target, bool& success) const ;
	
	// Copies the tree rooted at treePtr and returns a pointer to
	// the copy.
	BinaryNode<DataType>* copyTree( const BinaryNode<DataType>* treePtr) const ;
	
	// Recursive traversal helper methods:
	void LevelOrder( void visit(DataType&), BinaryNode<DataType>* treePtr, LinkedQueue <BinaryNode<DataType>*> &Q) const ;
	void preorder( void visit(DataType&), BinaryNode<DataType>* treePtr) const ;
	void inorder( void visit(DataType&), BinaryNode<DataType>* treePtr) const ;
	void postorder( void visit(DataType&), BinaryNode<DataType>* treePtr) const ;

public :
	//------------------------------------------------------------
	// Constructor and Destructor Section.
	//------------------------------------------------------------
	BinaryTree();
	BinaryTree( const DataType& rootItem);
	BinaryTree( const DataType& rootItem, const BinaryTree<DataType>* leftTreePtr, const BinaryTree<DataType>* rightTreePtr);
	BinaryTree( const BinaryTree<DataType>& tree);
	virtual ~BinaryTree();
	
	//------------------------------------------------------------
	// Public BinaryTree General Methods Section.
	//------------------------------------------------------------
	bool isEmpty() const ;
	int getHeight() const ;
	int getNumberOfNodes() const ;
	DataType getRootData() const ;
	void setRootData( const DataType& newData);
	bool add( const DataType& newData); // Adds a node
	bool remove( const DataType& data); // Removes a node
	void clear();
	bool contains( const DataType& anEntry) const ;
	bool isBST() const ; //Checks if every subTree is a Binary Search Tree
	bool isFull() const ;
	bool isComplete() const ;
	bool isBalanced () const ;


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
	BinaryTree & operator=(const BinaryTree& rightHandSide);
};

#endif