#include <stdexcept>

template <class Element, class Compare>
UniqueArrayIterator<Element,Compare>::UniqueArrayIterator(const UniqueArray<Element,Compare>& other_uniqueArray,
                                                          unsigned int start_index) : uniqueArray(other_uniqueArray) , index(start_index){
    if(start_index > other_uniqueArray.getSize()) throw std::out_of_range("out_of_range");
}

template <class Element, class Compare>
Element*& UniqueArrayIterator<Element,Compare>::operator*() {
    if (index >= uniqueArray.getSize() || index < 0) throw std::out_of_range("out_of_range");
    return uniqueArray.elements[index];
}

template <class Element, class Compare>
void UniqueArrayIterator<Element,Compare>::operator++() {
    index++;
}

template <class Element, class Compare>
void UniqueArrayIterator<Element,Compare>::operator--() {
    index--;
}

template <class Element, class Compare>
void UniqueArrayIterator<Element,Compare>::operator+=(unsigned int i) {
    index += i;
}

template <class Element, class Compare>
void UniqueArrayIterator<Element,Compare>::operator-=(unsigned int i) {
    index -= i;
}

/*template <class Element, class Compare>
bool operator<(const UniqueArrayIterator<Element,Compare>& first, const UniqueArrayIterator<Element,Compare>& second) {

	return first.index < second.index;
}*/

template <class Element, class Compare>
bool operator==(const UniqueArrayIterator<Element,Compare>& first, const UniqueArrayIterator<Element,Compare>& second) {
	return &first.uniqueArray == &second.uniqueArray && first.index == second.index;
}

template <class Element, class Compare>
bool operator!=(const UniqueArrayIterator<Element,Compare>& first, const UniqueArrayIterator<Element, Compare>& second) {
    return !(first == second);
}