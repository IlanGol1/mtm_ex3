#ifndef UNIQUE_ARRAY_IMP_H
#define UNIQUE_ARRAY_IMP_H

template <class Element, class Compare>
UniqueArray<Element,Compare>::UniqueArray(unsigned int size) :
        len(size),
        elements(new Element * [size])
{
    for (int i=0; i<size ; i++) {
		elements[i] = NULL;
    }
}

template <class Element, class Compare>
UniqueArray<Element,Compare>::UniqueArray(const UniqueArray& other) :
        len(other.getSize()),
        elements(new Element * [other.getSize()])
{
    for(int i = 0; i < other.getSize(); i++) {
		this->elements[i] = NULL;
		if (other.elements[i]) this->elements[i] =
		          new Element(*other.elements[i]);
    }
}

template <class Element, class Compare>
UniqueArray<Element,Compare>::~UniqueArray() {
    for (int i=0 ; i<len ; i++) {
        delete elements[i];
    }
    delete[] elements;
}

template <class Element, class Compare>
unsigned int UniqueArray<Element,Compare>::insert(const Element& element) {
    unsigned int index = 0;
    if(getIndex(element, index)) {
        return index;
    }
    for (index=0 ; index < len && elements[index] ; index++) ;
    if (index == len) {
        throw UniqueArrayIsFullException();
    }
    this->elements[index] = new Element(element);
    return index;
}

template <class Element, class Compare>
bool UniqueArray<Element,Compare>::getIndex(const Element& element,
                                            unsigned int& index) const {
    for (int i = 0; i < len ; ++i) {
        if (elements[i] && cmp(element , *elements[i])) {
            index = i;
            return true;
        }
    }
    return false;
}

template <class Element, class Compare>
const Element* UniqueArray<Element,Compare>::operator[]
                                                (const Element& element) const {
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
	
	Element* temp = elements[index];
	elements[index] = NULL;
	delete temp;

    return true;
}

template <class Element, class Compare>
unsigned int UniqueArray<Element,Compare>::getCount() const {
    int counter = 0;
    for (int i = 0; i < len; i++) {
        if (elements[i]) {
            counter++;
        }
    }
    return counter;
}

template <class Element, class Compare>
unsigned int UniqueArray<Element,Compare>::getSize() const {
    return  len;
}

template <class Element, class Compare>
UniqueArray<Element,Compare>
                UniqueArray<Element,Compare>::filter(const Filter& f) const {
    UniqueArray filter_array (*this);
    for (int i = 0; i < len; ++i) {
        if (elements[i] && !f(*elements[i])) {
            filter_array.remove(*elements[i]);
        }
    }
    return filter_array;
}
#endif