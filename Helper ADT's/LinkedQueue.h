#ifndef _LINKED_QUEUE
#define _LINKED_QUEUE

#include "Node.cpp"
#include <cassert>

template<class T>
class LinkedQueue
{
	// The queue is implemented as a chain of linked nodes that has
	// two external pointers, a head pointer for the front of the queue
	// and a tail pointer for the back of the queue.
	Node<T>* backPtr;
	Node<T>* frontPtr;

public :

	LinkedQueue();
	LinkedQueue( const LinkedQueue<T> & aQueue);
	~LinkedQueue();

	bool isEmpty() const ;

	bool enqueue(T newEntry);

	bool dequeue();

	T peekFront() const;

}; // end Queue

#endif