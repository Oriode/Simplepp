#pragma once

#include "Log.h"
#include "String.h"
#include "IO/IO.h"

template<typename T>
class ListNode : public IO::BasicIO {
public:

	ListNode();
	ListNode(const T& data);
	ListNode(ListNode<T>* previousNode, ListNode<T>* nextNode, const T& data);

	const ListNode<T> * getPrevious() const;
	ListNode<T>* getPrevious();

	const ListNode<T>* getNext() const;
	ListNode<T>* getNext();

	void setPrevious(ListNode<T>* previousNode);
	void setNext(ListNode<T>* nextNode);

	const T& getData() const;
	T& getData();

	void setData(const T& data);

	/**
	 * @brief 	read from a file stream
	 *
	 * @param [in,out]	stream	stream used to read load this object.
	 *
	 * @returns	boolean to know if the operation is a success of not.
	 */
	template<typename Stream>
	bool read(Stream* stream);

	/**
	 * @brief 	write this object as binary into a file stream
	 *
	 * @param [in,out]	stream	stream used to write this object.
	 *
	 * @returns	boolean to know if the operation is a success of not.
	 */
	template<typename Stream>
	bool write(Stream* stream) const;

	ListNode<T>* copy();

private:
	ListNode<T>* previousNode;
	ListNode<T>* nextNode;
	T data;
};

template<typename T>
ListNode<T>::ListNode() {

}

template<typename T>
ListNode<T>::ListNode(const T& data) :
	data(data) {

}

template<typename T>
ListNode<T>::ListNode(ListNode<T>* previousNode, ListNode<T>* nextNode, const T& data) :
	previousNode(previousNode),
	nextNode(nextNode),
	data(data) {

}

template<typename T>
inline const ListNode<T>* ListNode<T>::getPrevious() const {
	return this->previousNode;
}

template<typename T>
inline ListNode<T>* ListNode<T>::getPrevious() {
	return this->previousNode;
}

template<typename T>
inline const ListNode<T>* ListNode<T>::getNext() const {
	return this->nextNode;
}

template<typename T>
inline ListNode<T>* ListNode<T>::getNext() {
	return this->nextNode;
}

template<typename T>
inline void ListNode<T>::setPrevious(ListNode<T>* previousNode) {
	this->previousNode = previousNode;
}

template<typename T>
inline void ListNode<T>::setNext(ListNode<T>* nextNode) {
	this->nextNode = nextNode;
}

template<typename T>
inline const T& ListNode<T>::getData() const {
	return this->data;
}

template<typename T>
inline T& ListNode<T>::getData() {
	return this->data;
}

template<typename T>
inline void ListNode<T>::setData(const T& data) {
	this->data = data;
}

template<typename T>
inline ListNode<T>* ListNode<T>::copy() {
	return new ListNode<T>(this->previousNode, this->nextNode, this->data);
}

template<typename T>
class List : public IO::BasicIO {
public:
	List();
	List(const List<T>& l);
	List(List<T>&& l);
	~List();

	using Iterator = ListNode<T> *;

	List<T>& operator=(const List<T>& l);
	List<T>& operator=(List<T>&& l);

	const typename List<T>::Iterator getBegin() const;
	typename List<T>::Iterator getBegin();

	const typename List<T>::Iterator getEnd() const;
	typename List<T>::Iterator getEnd();

	bool iterate(typename List<T>::Iterator* it) const;
	bool iterate(typename List<T>::Iterator* it, T ** v) const;
	template<typename TestFunctor>
	bool iterate(typename List<T>::Iterator* it, T** v, TestFunctor& testFunctor) const;

	const T& getValueIt(typename List<T>::Iterator it) const;
	T& getValueIt(typename List<T>::Iterator it);

	const ListNode<T> * getNodeIt(typename List<T>::Iterator it) const;
	ListNode<T> * getNodeIt(typename List<T>::Iterator it);

	void setValueIt(typename List<T>::Iterator it, const T& data);

	const T& getLast() const;
	T& getLast();

	const T& getFirst() const;
	T& getFirst();

	typename List<T>::Iterator push(const T& data);
	T& pop();

	typename List<T>::Iterator insert(const T& data, typename List<T>::Iterator previousIt);

	typename List<T>::Iterator pushNode(ListNode<T> * newNode);

	typename List<T>::Iterator pushBegin(const T& data);
	T& popBegin();

	void clear();

	bool isEmpty() const;

	/**
	 * @brief 	Search a data and retrieve the Iterator
	 *
	 * @param 	data	Data to be searched.
	 *
	 * @returns	Oterator where the data has bee founded if founded. return NULL instead.
	 */
	const typename List<T>::Iterator search(const T& data) const;
	typename List<T>::Iterator search(const T& data);

	bool exists(const T& value) const;

	/**
	 * @brief 	Replace the first occurrence of the data
	 *
	 * @param 	search	Data to be searched.
	 * @param 	data  	Data to be set instead.
	 *
	 * @returns	True if something has been replaced, False otherwise.
	 */
	bool replaceFirst(const T& search, const T& data);

	/**
	 * @brief 	Replace ALL occurrences of the data searched
	 *
	 * @param 	search	Data to be searched.
	 * @param 	data  	Data to be set instead.
	 *
	 * @returns	True if something has been replaced, False otherwise.
	 */
	bool replaceAll(const T& search, const T& data);

	/**
	 * @brief 	Erase the first occurrence and rearrange the data
	 *
	 * @param 	value	Value to be searched and erased.
	 *
	 * @returns	True if something has been deleted, False otherwise.
	 */
	bool eraseFirst(const T& value);

	/**
	 * @brief 	Erase all the occurrences and rearrange the data
	 *
	 * @param 	value	Value to be searched and erased.
	 *
	 * @returns	True if something has been deleted, False otherwise.
	 */
	bool eraseAll(const T& value);

	void eraseIt(const typename List<T>::Iterator it);

	template<typename C = String>
	C toString() const;

	/**
	 * @brief 	read from a file stream
	 *
	 * @param [in,out]	stream	stream used to read load this object.
	 *
	 * @returns	boolean to know if the operation is a success of not.
	 */
	template<typename Stream>
	bool read(Stream* stream);

	/**
	 * @brief 	write this object as binary into a file stream
	 *
	 * @param [in,out]	stream	stream used to write this object.
	 *
	 * @returns	boolean to know if the operation is a success of not.
	 */
	template<typename Stream>
	bool write(Stream* stream) const;


private:
	void _delete();

	ListNode<T> * firstNode;
	ListNode<T> * lastNode;

	Size size;
};

#include "List.hpp"

template<typename T>
inline List<T>::List() :
	firstNode(NULL),
	lastNode(NULL),
	size(0)
{}

template<typename T>
inline List<T>::List(const List<T>&l) :
	firstNode(NULL),
	lastNode(NULL),
	size(0)
{
	for ( typename List<T>::Iterator it(l.getBegin()); it != l.getEnd(); l.iterate(&it) ) {
		ListNode* newNode(l.getNodeIt(it)->copy());
		pushNode(newNode);
	}
}

template<typename T>
inline List<T>::List(List<T>&& l) :
	firstNode(l.firstNode),
	lastNode(l.lastNode),
	size(l.size)
{

}

template<typename T>
inline List<T>::~List() {
	_delete();
}

template<typename T>
inline List<T>& List<T>::operator=(const List<T>& l) {
	clear();
	for ( typename List<T>::Iterator it(l.getBegin()); it != l.getEnd(); l.iterate(&it) ) {
		ListNode* newNode(l.getNodeIt(it)->copy());
		pushNode(newNode);
	}
}

template<typename T>
inline List<T>& List<T>::operator=(List<T>&& l) {
	this->firstNode = l.firstNode;
	this->lastNode = l.lastNode;
	this->size = l.size;
}

template<typename T>
inline const typename List<T>::Iterator List<T>::getBegin() const {
	return this->firstNode;
}

template<typename T>
inline typename List<T>::Iterator List<T>::getBegin() {
	return this->firstNode;
}

template<typename T>
inline const typename List<T>::Iterator List<T>::getEnd() const {
	return NULL;
}

template<typename T>
inline typename List<T>::Iterator List<T>::getEnd() {
	return NULL;
}

template<typename T>
inline bool List<T>::iterate(typename List<T>::Iterator* it) const {
	typename ListNode<T>*& node(*it);
	node = node->getNext();
	return node;
}

template<typename T>
inline bool List<T>::iterate(typename List<T>::Iterator* it, T** v) const {
	typename ListNode<T>* node(*it);
	node = node->getNext();
	if ( node != NULL ) {
		( *v ) = &node->getData();
		return true;
	}
	return false;
}

template<typename T>
inline const T& List<T>::getValueIt(typename List<T>::Iterator it) const {
	return it->getData();
}

template<typename T>
inline T& List<T>::getValueIt(typename List<T>::Iterator it) {
	return it->getData();
}

template<typename T>
inline const ListNode<T> * List<T>::getNodeIt(typename List<T>::Iterator it) const {
	return it;
}

template<typename T>
inline ListNode<T>* List<T>::getNodeIt(typename List<T>::Iterator it) {
	return it;
}

template<typename T>
inline void List<T>::setValueIt(typename List<T>::Iterator it, const T& data) {
	it->setData(data);
}

template<typename T>
inline const T& List<T>::getLast() const {
	return this->lastNode->getData();
}

template<typename T>
inline T& List<T>::getLast() {
	return this->lastNode->getData();
}

template<typename T>
inline const T& List<T>::getFirst() const {
	return this->firstNode->getData();
}

template<typename T>
inline T& List<T>::getFirst() {
	return this->firstNode->getData();
}

template<typename T>
inline typename List<T>::Iterator List<T>::push(const T& data) {
	ListNode<T>* newNode(new ListNode<T>(data));
	return pushNode(newNode);
}

template<typename T>
inline T& List<T>::pop() {
	ListNode<T> * node(this->lastNode);
	T data(node->getData());
	if ( node->getPrevious() ) {
		node->getPrevious()->setNext(NULL);
		this->lastNode = node->getPrevious();
	} else {
		this->lastNode = NULL;
		this->firstNode = NULL;
	}
	delete node;
	this->size--;
	return data;
}

template<typename T>
inline typename List<T>::Iterator List<T>::insert(const T& data, typename List<T>::Iterator previousIt) {
	if ( previousIt ) {
		ListNode<T>* newNode(new ListNode<T>(data));

		newNode->setPrevious(previousIt);

		if ( previousIt->getNext() ) {
			newNode->setNext(previousIt->getNext());
			previousIt->getNext()->setPrevious(newNode);
		} else {
			this->lastNode = newNode;
		}
		previousIt->setNext(newNode);

		this->size++;

		return newNode;
	} else {
		return pushBegin(data);
	}
}

template<typename T>
inline typename List<T>::Iterator List<T>::pushNode(ListNode<T>* newNode) {
	newNode->setPrevious(this->lastNode);
	newNode->setNext(NULL);

	if ( this->firstNode ) {
		this->lastNode->setNext(newNode);
	} else {
		this->firstNode = newNode;
	}
	this->lastNode = newNode;

	this->size++;

	return newNode;
}

template<typename T>
inline typename List<T>::Iterator List<T>::pushBegin(const T& data) {
	ListNode<T>* newNode(new ListNode<T>(data));

	newNode->setPrevious(NULL);
	newNode->setNext(this->firstNode);

	if ( this->lastNode ) {
		this->firstNode->setPrevious(newNode);
	} else {
		this->lastNode = newNode;
	}
	this->firstNode = newNode;

	this->size++;

	return newNode;
}

template<typename T>
inline T& List<T>::popBegin() {
	ListNode<T> * node(this->firstNode);
	T data(node->getData());
	if ( node->getNext() ) {
		node->getNext()->setPrevious(NULL);
		this->firstNode = node->getNext();
	} else {
		this->lastNode = NULL;
		this->firstNode = NULL;
	}

	this->size--;

	delete node;
	return data;
}

template<typename T>
inline void List<T>::clear() {
	_delete();
	this->firstNode = NULL;
	this->lastNode = NULL;
	this->size = Size(0);
}

template<typename T>
inline bool List<T>::isEmpty() const {
	return this->firstNode == NULL;
}

template<typename T>
inline const typename List<T>::Iterator List<T>::search(const T& data) const {
	return const_cast< List<T> * >( this )->search(data);
}

template<typename T>
inline typename List<T>::Iterator List<T>::search(const T& data) {
	for ( typename List<T>::Iterator it(getBegin()); it != getEnd(); iterate(&it) ) {
		const T& v(getValueIt(it));

		if ( data == v ) {
			return it;
		}
	}
	return NULL;
}

template<typename T>
inline bool List<T>::exists(const T& value) const {
	return search(value) != NULL;
}

template<typename T>
inline bool List<T>::replaceFirst(const T& search, const T& data) {
	for ( typename List<T>::Iterator it(getBegin()); it != getEnd(); iterate(&it) ) {
		T& v(getValueIt(it));

		if ( search == v ) {
			v = data;
			return true;
		}
	}
	return false;
}

template<typename T>
inline bool List<T>::replaceAll(const T& search, const T& data) {
	bool bFounded(false);
	for ( typename List<T>::Iterator it(getBegin()); it != getEnd(); iterate(&it) ) {
		T& v(getValueIt(it));

		if ( search == v ) {
			v = data;
			bFounded = true;
		}
	}
	return bFounded;
}

template<typename T>
inline bool List<T>::eraseFirst(const T& value) {
	for ( ListNode<T>* it(this->firstNode); it != NULL; it = it->getNext() ) {
		T& v(it->getData());

		if ( value == v ) {
			eraseIt(it);
			return true;
		}

	}
}

template<typename T>
inline bool List<T>::eraseAll(const T& value) {
	bool bFounded(false);
	ListNode<T>* nextNode;
	for ( ListNode<T>* it(this->firstNode); it != NULL; it = nextNode ) {
		T& v(it->getData());

		nextNode = it->getNext();

		if ( value == v ) {
			eraseIt(it);
			bFounded = true;
		}
	}
	return bFounded;
}

template<typename T>
inline void List<T>::eraseIt(const typename List<T>::Iterator it) {
	ListNode<T>* node(getNodeIt(it));
	if ( node->getPrevious() ) {
		node->getPrevious()->setNext(node->getNext());
	} else {
		this->firstNode = node->getNext();
	}
	if ( node->getNext() ) {
		node->getNext()->setPrevious(node->getPrevious());
	} else {
		this->lastNode = node->getPrevious();
	}

	this->size--;

	delete node;
}

template<typename T>
inline void List<T>::_delete() {
	ListNode<T>* nextNode;
	for ( ListNode<T>* it(this->firstNode); it != NULL; it = nextNode ) {
		nextNode = it->getNext();
		delete it;
	}
}

template<typename T>
template<typename TestFunctor>
inline bool List<T>::iterate(typename List<T>::Iterator* it, T** v, TestFunctor& testFunctor) const {
	if ( testFunctor() ) {
		typename ListNode<T>* node(*it);
		node = node->getNext();
		if ( node != NULL ) {
			( *v ) = &node->getData();
			return true;
		}
		return false;
	} else {
		return false;
	}
}

template<typename T>
template<typename C>
inline C List<T>::toString() const {
	C strOutput;
	strOutput << C::ElemType('{');
	strOutput << C::ElemType(' ');
	for ( typename List<T>::Iterator it(getBegin()); it != getEnd(); iterate(&it) ) {
		const T& data(getValueIt(it));

		if ( it != getBegin() ) {
			strOutput << C::ElemType(',');
			strOutput << C::ElemType(' ');
		}
		strOutput << data;
	}
	strOutput << C::ElemType(' ');
	strOutput << C::ElemType('}');

	return strOutput;
}

template<typename T>
template<typename Stream>
inline bool List<T>::read(Stream* stream) {
	clear();

	Size newSize;
	if ( !IO::read(stream, &newSize) ) {
		return false;
	}
	for ( Size i(0); i < newSize; i++ ) {
		ListNode<T>* newNode(new ListNode<T>());
		if ( !IO::read(stream, newNode) ) {
			delete newNode;
			return false;
		}
		pushNode(newNode);
	}

	return true;
}

template<typename T>
template<typename Stream>
inline bool List<T>::write(Stream* stream) const {
	if ( !IO::write(stream, &this->size) ) {
		return false;
	}
	for ( typename List<T>::Iterator it(getBegin()); it != getEnd(); iterate(&it) ) {
		const ListNode<T>* node(getNodeIt(it));

		if ( !IO::write(stream, node) ) {
			return false;
		}
	}

	return true;
}

template<typename T>
template<typename Stream>
inline bool ListNode<T>::read(Stream* stream) {
	if ( !IO::read(stream, &this->data) ) {
		return false;
	}
	return true;
}

template<typename T>
template<typename Stream>
inline bool ListNode<T>::write(Stream* stream) const {
	if ( !IO::write(stream, &this->data) ) {
		return false;
	}
	return true;
}
