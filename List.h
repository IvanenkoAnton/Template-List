/*******************************************************************************
	Created by Anton Ivanenko,April 2017
	OOP Lab
*******************************************************************************/

#pragma once
#include <iostream>
#include "Iterator.h"
template <class T>
class List {

	struct ListNode{
		T data;
		ListNode* next;
		ListNode() :next(NULL) {};
		ListNode(T _data) :data(_data) {};
		void Print() { std::cout << data << std::endl; }
	};

public:
	typedef  ListNode node_type;
	typedef _iterator<node_type> iterator;

	List():Head(NULL) {};
	List(const List<T> &_list);
    ~List();

	List<T>& operator =(const List<T> &_list);
	bool operator ==(const List<T> &_list) const;
	bool operator !=(const List<T> &_list) const;

	iterator begin();
	iterator end();
	iterator find(const node_type &val);

	void clear();
	bool empty();
	void pop_front();
	void push_front(const T val);
	void remove(const T val);

	int size() const;
	void splice(iterator Where, List<T>& Right);

	void Print();
private:
	node_type* Head;
};

template <typename T>
List<T>::List(const List<T> &_list) {

	if (_list.empty()) {
		abort();
	}
	else {
		node_type* Temp = _list.Head;
		while (Temp) {
			push_front(Temp->data);
			Temp = Temp->next;
		}
	}
}

template <typename T>
List<T>::~List() {
	if (!empty()) clear();
}

template <typename T>
List<T>& List<T>::operator =(const List<T> &_list) {

	if (*this == _list) {
		return *this;
	}
	else {
		node_type* Temp = NULL;
		clear();
		for (int i = 0; i < _list.size(); i++){
			Temp = _list.Head;
			for (int j = 0; j < _list.size() - 1 - i; j++) {
				Temp = Temp->next;
			}
			push_front(Temp->data);
		}
		return *this;
	}
}

template <typename T>
bool List<T>::operator==(const List<T> &_list)const{
	if (size() == _list.size()) {
		node_type *Temp1 = Head, *Temp2 = _list.Head;
		while (Temp1 && Temp2) {
			if (Temp1->data != Temp2->data) return false;
			Temp1 = Temp1->next;
			Temp2 = Temp2->next;
		}

		return true;
	}
	return false;
}

template <typename T>
bool List<T>::operator!=(const List<T> &_list)const{
	return !(*this == _list);
}

template <typename T>
typename List<T>::iterator List<T>::begin(){
	return *(new iterator(Head));
}

template <typename T>
typename List<T>::iterator List<T>::end(){
	if (empty()) {
		return *(new iterator(Head));
	}
	else {
		node_type* Temp = Head;
		while (Temp) {
			Temp = Temp->next;
		}
		return *(new iterator(Temp));
	}
}

template <typename T>
typename List<T>::iterator List<T>::find(const node_type &val) {
	if (empty()) {
		abort();
	}
	else {
		node_type* Temp = Head;
		while (Temp && (Temp->data != val.data)) Temp = Temp->next;
		return *(new iterator(Temp));
	}
}

template <typename T>
bool List<T>::empty() {
	return (Head == NULL);
}

template <typename T>
int List<T>::size()const {
	int count = 0;
	node_type* Temp = Head;
	while (Temp) {
		count++;
		Temp = Temp->next;
	}
	return count;
}

template <typename T>
void List<T>::pop_front() {
	if (!empty()) {
		node_type* Temp = Head;
		Head = Head->next;
		delete Temp;
	}
	else {
		abort();
	}
}

template <typename T>
void List<T>::push_front(const T val) {
	node_type* NewNode = new node_type(val);
	NewNode->next = Head;
	Head = NewNode;
}

template <typename T>
void List<T>::remove(const T val) {
	if (empty()) {
		abort();
	}
	else {
		node_type* Temp = Head;
		node_type* Parent = NULL;
		bool found = false;
		while (Temp){
			if (Temp->data == val) {
				found = true;
				break;
			}
			Parent = Temp;
			Temp = Temp->next;

		}
		if (found) {
			if (Parent) {
				Parent->next = Temp->next;
				delete Temp;
			}
			else {
	     		pop_front();
			}
		}
	}
}

template <typename T>
void List<T>::clear() {
	while (!empty()) {
		pop_front();
	}
}

template <typename T>
void List<T>::splice(iterator Where, List<T>&Right) {
	if (!Where.empty()) {
		Right.push_front((*Where).data);
		remove((*Where).data);
	}
	else {
		abort();
	}
}

template <typename T>
void List<T>::Print() {
	if (!empty()) {
		for (auto& iter : *this) {
			iter.Print();
		}
	}
	else {
		std::cout << "Empty" << std::endl;
	}

}
