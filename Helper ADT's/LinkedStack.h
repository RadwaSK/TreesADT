#ifndef _LINKED_STACK
#define __LINKED_STACK

#include <cassert>
#include "Node.cpp"

template < class T>
class LinkedStack
{
	Node<T>* top; // Index to top of stack
public:
	LinkedStack(); // Default constructor
	LinkedStack( const LinkedStack<T> & aStack); // Copy constructor
	~LinkedStack(); // Destructor

	bool isEmpty() const ;

	bool push( const T & newEntry );

	bool pop();

	T peek() const ;

}; // end ArrayStack


#endif