#ifndef CUSTOM_ITERATOR_H
#define CUSTOM_ITERATOR_H

//I think this prevents a "segmentation fault" error, so it's necessary/:
template<Element>
class CustomIterator {

	Element** elements;
	unsigned int index = 0;
	unsigned int len = 0;
public:
	CustomIterator(Element** arr, int len);
	friend bool operator<(const CustomIterator& first, const CustomIterator& second);
	Element*& operator[](int i);
	void operator++();
	void operator--();
	void operator+=(int);
	void operator-=(int);
};


#endif