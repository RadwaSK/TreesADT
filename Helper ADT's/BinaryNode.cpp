#include "BinaryNode.h"


//constructors
template<class DataType>
BinaryNode<DataType>::BinaryNode(){
	leftChildPtr = rightChildPtr = nullptr;
}

template<class DataType>
BinaryNode<DataType>::BinaryNode( const DataType& anItem){
	item = anItem;
	leftChildPtr = rightChildPtr = nullptr;
}

template<class DataType>
BinaryNode<DataType>::BinaryNode( const DataType& anItem, BinaryNode<DataType>* leftPtr,	BinaryNode<DataType>* rightPtr){
	item = anItem;
	leftChildPtr = leftPtr;
	rightChildPtr = rightPtr;
}

//copy constructor
template<class DataType>
BinaryNode<DataType>::BinaryNode(const BinaryNode<DataType> & newNode){
	if (!newNode){
		leftChildPtr = rightChildPtr = nullptr;
		return;
	}

	item = newNode->item;
	if (newNode->leftChildPtr)
		leftChildPtr = new BinaryNode(newNode->leftChildPtr->item);
	if (newNode->rightChildPtr)
		rightChildPtr = new BinaryNode(newNode->rightChildPtr->item);
}


//setters
template<class DataType>
void BinaryNode<DataType>::setItem( const DataType& anItem){
	item = anItem;
}

template<class DataType>
void BinaryNode<DataType>::setLeftChildPtr(BinaryNode<DataType>* leftPtr){
	leftChildPtr = leftPtr;
}

template<class DataType>
void BinaryNode<DataType>::setRightChildPtr(BinaryNode<DataType>* rightPtr){
	rightChildPtr = rightPtr;
}


//getters
template<class DataType>
DataType BinaryNode<DataType>::getItem() const {
	return item;
}

template<class DataType>
BinaryNode<DataType>* BinaryNode<DataType>::getLeftChildPtr() const {
	return leftChildPtr;
}

template<class DataType>
BinaryNode<DataType>* BinaryNode<DataType>::getRightChildPtr() const {
	return rightChildPtr;
}


//boolean
template<class DataType>
bool BinaryNode<DataType>::isLeaf() const {
	return (!leftChildPtr && !rightChildPtr);
}

