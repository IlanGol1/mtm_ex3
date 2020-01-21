#include "CustomIterator.h"

namespace CustomIterator {
	template<Element>
	CustomIterator(Element** arr, int size) : elements(arr),  index(0), len(size){

	}

	template<Element>
	Element*& operator[](unsigned int i) {

		if (i >= len - index || i + index < 0) throw std::out_of_range;
		return arr[i + index];
	}
	template<Element>
	Element*& operator*() {

		if (index >= len || index < 0) throw std::out_of_range;
		return arr[index];
	}

	template<Element>
	void operator++() {
		index++;
	}

	template<Element>
	void operator--() {
		index--;
	}

	template<Element>
	void operator+=(int i) {
		index += i;
	}

	template<Element>
	void operator-=(int i) {
		index -= i;
	}
}

template<Element>
bool operator<(const CustomIterator<Element>& first, const CustomIterator<Element>& second) {

	return first.index < second.index;
}

template<Element>
bool operator==(const CustomIterator<Element>& first, const CustomIterator<Element>& second) {

	return first.index == second.index && first.elements == second.elements && first.len == second.len;
}

template<Element>
bool operator!=(const CustomIterator<Element>& first, const CustomIterator<Element>& second) {

	return !(first.index == second.index && first.elements == second.elements && first.len == second.len);
}