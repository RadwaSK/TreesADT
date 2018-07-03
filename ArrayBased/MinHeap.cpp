#include "MinHeap.h"
#include <cmath>
#include <cassert>

//Global function
template<class DataType>
void swapItems(DataType & a, DataType &b){
	DataType temp = b;
	b = a;
	a = temp;
}


// Returns the array index of the left child (if it exists).
template<class DataType>	
int MinHeap<DataType>::getLeftChildIndex( const int nodeIndex) const {
	return (2 * nodeIndex) + 1;
}

// Returns the array index of the right child (if it exists).
template<class DataType>
int MinHeap<DataType>::getRightChildIndex( int nodeIndex) const {
	return (2 * nodeIndex) + 2;
}

// Returns the array index of the parent node.
template<class DataType>
int MinHeap<DataType>::getParentIndex( int nodeIndex) const {
	//an assumption I made
	if (nodeIndex == ROOT_INDEX) return 0;
	//generally
	return (nodeIndex - 1) / 2;
}

// Tests whether this node is a leaf.
template<class DataType>
bool MinHeap<DataType>::isLeaf( int nodeIndex) const {
	return getRightChildIndex(nodeIndex) < itemCount && getLeftChildIndex(nodeIndex) < itemCount;
}

//It takes max item from end to top
template<class DataType>
void MinHeap<DataType>::ReheapUp( int LeafIndex){
	int parentIndex = getParentIndex(LeafIndex);

	//if it has a parent
	if (parentIndex >= 0){
		if (items[parentIndex] > items[LeafIndex])
		{
			swapItems(items[parentIndex], items[LeafIndex]);
			ReheapUp(parentIndex);
		}
	}
}

//It takes min item from top to end
template<class DataType>
void MinHeap<DataType>::ReheapDown( int subTreeRootIndex){
	if (subTreeRootIndex >= itemCount) return;

	int LeftInd = getLeftChildIndex(subTreeRootIndex);
	int RightInd = getRightChildIndex(subTreeRootIndex);

	//if it has two children
	if (RightInd < itemCount){
		//Get the index of larger item
		int minInd = (items[RightInd] < items[LeftInd]) ? RightInd : LeftInd;
		//if smaller (mostly) swap them
		if (items[minInd] < items[subTreeRootIndex]){
			swapItems(items[minInd], items[subTreeRootIndex]);
			//Reheap Down again
			ReheapDown(minInd);
		}
	}


	//if I have a left child only (last child)
	if (LeftInd < itemCount && RightInd >= itemCount)
		//if the left child is lesser than that of the root
		if (items[LeftInd] < items[subTreeRootIndex])
			swapItems(items[LeftInd], items[subTreeRootIndex]);
}

// Creates a heap from an unordered array.
template<class DataType>
void MinHeap<DataType>::heapCreate(){
	for (int i = itemCount/2; i>=0; i++)
		ReheapUp(i);
}

//LevelOrder (Breadth-First) Traversal
template<class DataType>
void MinHeap<DataType>::LevelOrder(void visit(DataType&), int rootInd) const {
	for (int i = 0; i<itemCount; i++)
		visit(items[i]);
}


//--------Constructors--------//
template<class DataType>
MinHeap<DataType>::MinHeap(){
	itemCount = 0;
	items = new DataType[DEFAULT_CAPACITY];
	maxItems = DEFAULT_CAPACITY;
}

template<class DataType>
MinHeap<DataType>::MinHeap( const DataType someArray[], const int arraySize){
	//alocate a larger array
	items = new DataType[2*arraySize];

	maxItems = 2*arraySize;

	itemCount = arraySize; //count of already existing items

	//copying gived items in array, with no order
	for (int i = 0; i < itemCount; i++)
		items[i] = someArray[i];

	//Build the heap of these values;
	heapCreate();
}

//--------Destructor--------//
template<class DataType>
MinHeap<DataType>::~MinHeap(){
	clear();
}


//--------Heap Public Methods--------//
template<class DataType>
bool MinHeap<DataType>::isEmpty() const {
	return itemCount == 0;
}

template<class DataType>
int MinHeap<DataType>::getNumberOfNodes() const {
	return itemCount;
}

template<class DataType>
int MinHeap<DataType>::getHeight() const {
	return (int)(log10(itemCount) / log10(2)) + 1;
}

template<class DataType>
DataType MinHeap<DataType>::peekTop() const {
	assert(!isEmpty());
	return items[0];
}

template<class DataType>
bool MinHeap<DataType>::add( const DataType& newData){
	if (itemCount == maxItems) return false;
	//add new item to array
	items[itemCount] = newData;
	itemCount++;
	//rebuild heap
	ReheapUp(itemCount-1);
	return true;
}

template<class DataType>
bool MinHeap<DataType>::remove(){
	if (isEmpty()) return false;
	//We delete the root
	items[ROOT_INDEX] = items[itemCount-1];
	itemCount--;
	ReheapDown(ROOT_INDEX);
	return true;
}

template<class DataType>
void MinHeap<DataType>::clear(){
	delete [] items;
	items = nullptr;
	itemCount = 0;
}

//Traversal functions
template<class DataType>
void MinHeap<DataType>::LevelOrderTraverse(void visit(DataType&)) const {
	LevelOrder(visit, ROOT_INDEX);
}
