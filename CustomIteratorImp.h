#ifndef CUSTOMITERATORIMP_H
#define CUSTOMITERATORIMP_H

template<Element>
CustomIterator<Element>::CustomIterator<Element>(Element** arr, int size) : elements(arr),  index(0), len(size){
}

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


template<class ElementC>
bool operator<(const CustomIterator<ElementC>& first, const CustomIterator<ElementC>& second) {

	return first.index < second.index;
}

template<class ElementC>
bool operator==(const CustomIterator<ElementC>& first, const CustomIterator<ElementC>& second) {

	return first.index == second.index && first.elements == second.elements && first.len == second.len;
}

template<class ElementC>
bool operator!=(const CustomIterator<ElementC>& first, const CustomIterator<ElementC>& second) {

	return !(first.index == second.index && first.elements == second.elements && first.len == second.len);
}

#endif