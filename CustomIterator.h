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
	Element*& operator[](int i);
	Element*& operator*();
	void operator++();
	void operator--();
	void operator+=(int);
	void operator-=(int);

	template<class Element>
	friend bool operator==(const CustomIterator<Element>& first, const CustomIterator<Element>& second);
	
	template<class Element>
	friend bool operator!=(const CustomIterator<Element>& first, const CustomIterator<Element>& second);
	
	template<class Element>
	friend bool operator<(const CustomIterator<Element>& first, const CustomIterator<Element>& second);
};


#endif