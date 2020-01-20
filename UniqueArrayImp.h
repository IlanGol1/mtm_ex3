#ifndef UniqueArrayImp_H

#define UniqueArrayImp_H

template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(unsigned int size) :
	len(size),
	elements(new Element[size]),
	used_positions(new bool[size] = { false }),
	cmp(new Compare()) { 
}

template <class Element, class Compare>
UniqueArray<Element,Compare>::UniqueArray(const UniqueArray& other) :
    len(other.getSize()),
    elements(new Element[other.getSize()]),
    used_positions(new bool [other.getSize()] = {false}),
    cmp(new Compare()) {
        for(int i = 0; i < other.getSize(); i++) {
            if (other.used_positions[i]) {
                this.used_positions[i] = true;
                this.elements[i] = new Element(other.elements[i]);
            }
        }
}

template <class Element, class Compare>
UniqueArray<Element,Compare>::~UniqueArray() {
	for (int i = 0; i < len; i++) if(elements[i]) delete elements[i];
	delete[] elements;
    delete cmp;
	delete[] used_positions;
}

template <class Element, class Compare>
unsigned int UniqueArray<Element,Compare>::insert(const Element& element) {
    int index = 0;
    if(getIndex(element, index)) {
        return index;
    }
    for (index=0 ; index< len && !used_positions[index] ; index++) ;
    if (index == len) {
        throw new ArrayIsFullException();
    }
    this->elements[index] = new Element(element);
    used_positions[index] = true;
    return index;
}

template <class Element, class Compare>
bool UniqueArray<Element,Compare>::getIndex(const Element& element, unsigned int& index) const {
    for (int i = 0; i < len ; ++i) {
        if (used_positions[i] && cmp(element,elements[i])) {
            index = i;
            return true;
        }
    }
    return false;
}

template <class Element, class Compare>
const Element* UniqueArray<Element,Compare>::operator[] (const Element& element) const {
    unsigned int index = 0;
    if (!getIndex(element,index)) {
        return NULL;
    }
    return elements[index];
}

template <class Element, class Compare>
bool UniqueArray<Element,Compare>::remove(const Element& element) {
    unsigned int index = 0;
    if (!getIndex(element,index)) {
        return false;
    }
    delete elements[index];
    used_positions[index] = false;
    return true;
}

template <class Element, class Compare>
unsigned int UniqueArray<Element,Compare>::getCount() const {
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (used_positions[i]) {
            count++;
        }
    }
    return count;
}

template <class Element, class Compare>
unsigned int UniqueArray<Element,Compare>::getSize() const {
    return  len;
}

template <class Element, class Compare>
UniqueArray<Element,Compare>& UniqueArray<Element,Compare>::filter(const Filter& f) const {
    UniqueArray filter_array = new UniqueArray<Element,Compare>(*this);
    for (int i = 0; i < len; ++i) {
        if (used_positions[i] && !f(elements[i])) {
            filter_array.remove(elements[i]);
        }
    }
	return filterArray;
}

#endif