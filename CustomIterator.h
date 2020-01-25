#include "CustomIteratorImp.h"

#ifndef CUSTOM_ITERATOR_H
#define CUSTOM_ITERATOR_H

//I think this prevents a "segmentation fault" error, so it's necessary/:
template<class Element>
class CustomIterator {

	Element** elements;
	unsigned int index = 0;
	unsigned int len = 0;
public:
	CustomIterator(Element** arr, int len);
	Element*& operator[](const CustomIterator<Element>& iterator, int i);
	Element*& operator*(const CustomIterator<Element>& iterator);
	void operator++(const CustomIterator<Element>& iterator);
	void operator--(const CustomIterator<Element>& iterator);
	void operator+=(int);
	void operator-=(int);

	template<class ElementC>
	friend bool operator==(const CustomIterator<Element>& first, const CustomIterator<Element>& second);
	
	template<class ElementC>
	friend bool operator!=(const CustomIterator<Element>& first, const CustomIterator<Element>& second);
	
	template<class ElementC>
	friend bool operator<(const CustomIterator<Element>& first, const CustomIterator<Element>& second);
};


#endif