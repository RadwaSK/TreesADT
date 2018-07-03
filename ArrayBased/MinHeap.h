#ifndef _ARRAY_MIN_HEAP
#define _ARRAY_MIN_HEAP


template < class DataType>
class MinHeap
{
	static const int ROOT_INDEX = 0; // Helps with readability
	static const int DEFAULT_CAPACITY = 21; // Small capacity to test for a full heap
	DataType* items; // Array of heap items
	int itemCount; // Current count of heap items
	int maxItems; // Maximum capacity of the heap
	// ---------------------------------------------------------------------
	// Most of the private utility methods use an array index as a parameter
	// and in calculations. This should be safe, even though the array is an
	// implementation detail, since the methods are private.
	// ---------------------------------------------------------------------
	// Returns the array index of the left child (if it exists).
	int getLeftChildIndex( const int nodeIndex) const;
	// Returns the array index of the right child (if it exists).
	int getRightChildIndex( int nodeIndex) const;
	// Returns the array index of the parent node.
	int getParentIndex( int nodeIndex) const ;
	// Tests whether this node is a leaf.
	bool isLeaf( int nodeIndex) const ;
	// Converts a semiheap to a heap.
	void ReheapUp( int subTreeRootIndex);
	//It takes min item from top to end
	void ReheapDown( int subTreeRootIndex);
	// Creates a heap from an unordered array.
	void heapCreate();
	//LevelOrder (Breadth-First) Traversal
	void LevelOrder(void visit(DataType&), int rootInd) const ;
public :
	MinHeap();
	MinHeap( const DataType someArray[], const int arraySize);
	virtual ~MinHeap();
	// Heap Public Methods:
	bool isEmpty() const ;
	int getNumberOfNodes() const ;
	int getHeight() const ;
	DataType peekTop() const ; //returns data of Root
	bool add( const DataType& newData );
	bool remove();
	void clear();

	//Traversal functions
	void LevelOrderTraverse(void visit(DataType&)) const ;
};

#endif