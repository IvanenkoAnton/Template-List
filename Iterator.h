/*******************************************************************************
	Created by Anton Ivanenko,April 2017
	OOP Lab
*******************************************************************************/

#pragma once
#include <cstdlib>
template <typename T>
class _iterator {
	T* ptr;
public:
	typedef T value_type;
	typedef _iterator<value_type> it_type;
	_iterator() :ptr(NULL) {};
	_iterator(T* _ptr) :ptr(_ptr) {};
	T& operator * ();
	void operator ++();
	void operator ++(int);
	bool operator ==(const it_type & _iter) const;
	bool operator !=(const it_type & _iter) const;
	bool empty() { return (ptr == NULL); };
};

template <typename T>
T& _iterator<T>::operator * () {
	return *ptr;
}

template <typename T>
void _iterator<T>::operator ++() {
	 ptr = ptr->next;
}

template <typename T>
void _iterator<T>::operator ++(int) {
     ptr = ptr->next;
}

template <typename T>
bool _iterator<T>::operator ==(const it_type & _iter) const {
	return (ptr == _iter.ptr);
}

template <typename T>
bool _iterator<T>::operator !=(const it_type & _iter) const {
	return !(*this == _iter);
}

