// A class of nodes for a link-based binary tree

#ifndef _BINARY_NODE
#define _BINARY_NODE

template < class DataType>
class BinaryNode
{
	DataType item;					// Data portion
	BinaryNode<DataType>* leftChildPtr;		// Pointer to left child
	BinaryNode<DataType>* rightChildPtr;	// Pointer to right child
public :
	//constructors
	BinaryNode();
	BinaryNode( const DataType& anItem);
	BinaryNode( const DataType& anItem, BinaryNode<DataType>* leftPtr,	BinaryNode<DataType>* rightPtr);
	//copy constructor
	BinaryNode( const BinaryNode<DataType> & newNode);
	
	//setters
	void setItem( const DataType& anItem);
	void setLeftChildPtr(BinaryNode<DataType>* leftPtr);
	void setRightChildPtr(BinaryNode<DataType>* rightPtr);

	//getters
	DataType getItem() const ;
	BinaryNode<DataType>* getLeftChildPtr() const ;
	BinaryNode<DataType>* getRightChildPtr() const ;
	
	//boolean
	bool isLeaf() const ;

}; // end BinaryNode

#endif