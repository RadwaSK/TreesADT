#include "LinkedQueue.h"

template<class T>
LinkedQueue<T>::LinkedQueue(){
	frontPtr = nullptr;
	backPtr = nullptr;
}

template<class T>
LinkedQueue<T>::LinkedQueue( const LinkedQueue<T> & aQueue){
	if (aQueue.isEmpty()){
		frontPtr = backPtr = nullptr;
		return;
	}

	Node<T> * currOriginPtr = aQueue.frontPtr;

	frontPtr = new Node<T> (currOriginPtr->getItem());

	Node<T> * currPtr = frontPtr;
	currOriginPtr = currOriginPtr->getNextNode();
	Node<T> * newNode;

	while (currOriginPtr){
		newNode = new Node<T>(currOriginPtr->getItem());
		currPtr->setNextNode(newNode);
		currPtr = newNode;
		currOriginPtr = currOriginPtr->getNextNode();
	}

	backPtr = currPtr;
}

template<class T>
LinkedQueue<T>::~LinkedQueue(){
	while (!isEmpty())
		dequeue();
}

template<class T>
bool LinkedQueue<T>::isEmpty() const {
	if (frontPtr ==  nullptr && backPtr == nullptr) return true;
	return false;
}

template<class T>
bool LinkedQueue<T>::enqueue(T newEntry){

	if (isEmpty()){
		frontPtr = new Node<T> (newEntry);
		backPtr = frontPtr;
	}

	else {
		Node<T> * newNode = new Node<T> (newEntry);
		backPtr->setNextNode(newNode);
		backPtr = newNode;
	}

	return true;
}

template<class T>
bool LinkedQueue<T>::dequeue(){
	if (isEmpty()) return false;
	
	T PopedEntry = frontPtr->getItem();

	//1 Node only in queue
	if (frontPtr == backPtr){
		delete frontPtr;
		frontPtr = backPtr = nullptr;
		return true;
	}

	Node<T> * NodeToDelete = frontPtr;

	//shift frontPtr to the next element
	frontPtr = frontPtr->getNextNode();

	delete NodeToDelete;
	NodeToDelete = nullptr;

	return true;

}

template<class T>
T LinkedQueue<T>::peekFront() const {
	assert(!isEmpty());
	return frontPtr->getItem();
}
