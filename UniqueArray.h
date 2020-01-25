#ifndef MTMPARKINGLOT_UNIQUEARRAY_H
#define MTMPARKINGLOT_UNIQUEARRAY_H

#include "UniqueArrayIterator.h"

template <class Element, class Compare>
class UniqueArray {
    // it it an iterator to go all over the array
    friend class UniqueArrayIterator<Element,Compare>;
    // In uniguearray are held: array of elements, array size and element
    // comparison function
	unsigned int len = 0;
	Compare cmp;
	Element** elements;

public:
    UniqueArray(unsigned int size);
    UniqueArray(const UniqueArray& other);
    ~UniqueArray();
    UniqueArray& operator=(const UniqueArray&) = delete;
    unsigned int insert(const Element& element);
    bool getIndex(const Element& element, unsigned int& index) const;
    const Element* operator[] (const Element& element) const;
    bool remove(const Element& element);
    unsigned int getCount() const;
    unsigned int getSize() const;

    /** This is an iterator function
     * @return a pointer to the first element in the array
     */
    UniqueArrayIterator<Element,Compare> begin() const {
        UniqueArrayIterator<Element,Compare> it (*this, 0);
        return it;
    }

    /**
     * this is an iterator function
     * @return pointer to an unreal element after the last element of the array
     */
    UniqueArrayIterator<Element,Compare> end() const {
        return UniqueArrayIterator<Element,Compare>(*this, len);
    }


	class Filter {
	public:
        virtual bool operator() (const Element&) const = 0;
    };
    UniqueArray filter(const Filter& f) const;

    class UniqueArrayIsFullException{
	};
};
#include "UniqueArrayImp.h"


#endif //MTMPARKINGLOT_UNIQUEARRAY_H
