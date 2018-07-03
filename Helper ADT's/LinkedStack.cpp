#pragma once
#include "LinkedStack.h"

template < class T>
LinkedStack<T>::LinkedStack(){
	top = nullptr;
}

template<class T>
LinkedStack<T>::LinkedStack( const LinkedStack<T> & aStack){// Copy constructor

	// Point to nodes in original chain
	Node<T>* origChainPtr = aStack->top;

	if (origChainPtr == nullptr)
		top = nullptr; // Original bag is empty

	else
	{
		// Copy first node
		top = new Node<T>(origChainPtr->getItem());
		
		// Point to first node in new chain
		Node<T>* newChainPtr = top;

		// Copy remaining nodes
		while (origChainPtr != nullptr )
		{
			// Advance original-chain pointer
			origChainPtr = origChainPtr->getNextNode();

			// Get next item from original chain
			T nextItem = origChainPtr->getItem();

			// Create a new node containing the next item
			Node<T>* newNodePtr = new Node<T>(nextItem);

			// Link new node to end of new chain
			newChainPtr->setNextNode(newNodePtr);

			// Advance pointer to new last node
			newChainPtr = newChainPtr->getNextNode();

		} // end while
		newChainPtr->setNextNode( nullptr); // Flag end of chain

	} // end if
}

template<class T>
LinkedStack<T>::~LinkedStack(){ // Destructor
	while (!isEmpty())
		pop();
}

template < class T>
bool LinkedStack<T>::isEmpty() const {
	return top == nullptr;
}


template < class T>
bool LinkedStack<T>::push( const T & newEntry ){
	if (isEmpty()){
		top = new Node<T>(newEntry);
		return true;
	}

	Node<T> * newNode = new Node <T> (newEntry);
	newNode->setNextNode(top);
	top = newNode;
	return true;
}


template < class T>
bool LinkedStack<T>::pop(){
	if (isEmpty()) return false;

	T poppedEntry = top->getItem();

	Node<T> * nodeToPop = top;
	top = top->getNextNode();

	delete nodeToPop;

	return true;
}

template < class T>
T LinkedStack<T>::peek() const {
	assert(!isEmpty());
	return top->getItem();
}

