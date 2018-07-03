#pragma once
#include "Node.h"

template<typename T>
Node<T>::Node(){
	next = nullptr;
}

template<typename T>
Node<T>::Node(const T & newItem){
	item = newItem;
	next = nullptr;
}

template<typename T>
Node<T>::Node(const T& newItem, Node<T> *nextNodePtr){
	item = newItem;
	next = nextNodePtr;
}

template<typename T>
void Node<T>::setItem(const T & newItem){
	item = newItem;
}

template<typename T>
void Node<T>::setNextNode(Node<T> *nextNodePtr){
	next = nextNodePtr;
}

template<typename T>
T Node<T>::getItem() const {
	return item;
}

template<typename T>
Node<T> * Node<T>::getNextNode() const {
	return next;
}
