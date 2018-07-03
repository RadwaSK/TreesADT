#pragma once

template<typename T>

class Node
{
	T item;
	Node<T> * next;
public:
	Node();
	Node(const T & newItem);
	Node(const T& newItem, Node<T> *nextNodePtr);
	void setItem(const T & newItem);
	void setNextNode(Node<T> *nextNodePtr);
	T getItem() const ;
	Node<T> * getNextNode() const ;
};
