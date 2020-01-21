#include "CustomIterator.h"

namespace CustomIterator {
	CustomIterator(Element** arr, int size) : elements(arr),  index(0), len(size){

	}
	Element*& operator[](unsigned int i) {

		if (i >= len - index || i + index < 0) throw std::out_of_range;
		return arr[i + index];
	}
	void operator++() {
		index++;
	}
	void operator--() {
		index--;
	}
	void operator+=(int i) {
		index += i;
	}
	void operator-=(int i) {
		index -= i;
	}
}
bool operator<(const CustomIterator& first, const CustomIterator& second) {

	return first.index < second.index;
}
