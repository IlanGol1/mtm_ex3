#include "CustomIterator.h"

namespace CustomIterator {
	template<class Element>
	CustomIterator(Element** arr, int size) : elements(arr),  index(0), len(size){

	}

	template<class Element>
	Element*& operator[](unsigned int i) {

		if (i >= len - index || i + index < 0) throw std::out_of_range;
		return arr[i + index];
	}
	
	template<class Element>
	Element*& operator*() {

		if (index >= len || index < 0) throw std::out_of_range;
		return arr[index];
	}

	template<class Element>
	void operator++() {
		index++;
	}

	template<class Element>
	void operator--() {
		index--;
	}

	template<class Element>
	void operator+=(int i) {
		index += i;
	}

	template<class Element>
	void operator-=(int i) {
		index -= i;
	}
}

template<class Element>
bool operator<(const CustomIterator<Element>& first, const CustomIterator<Element>& second) {

	return first.index < second.index;
}

template<class Element>
bool operator==(const CustomIterator<Element>& first, const CustomIterator<Element>& second) {

	return first.index == second.index && first.elements == second.elements && first.len == second.len;
}

template<class Element>
bool operator!=(const CustomIterator<Element>& first, const CustomIterator<Element>& second) {

	return !(first.index == second.index && first.elements == second.elements && first.len == second.len);
}