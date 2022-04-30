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