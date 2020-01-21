#include "CustomIterator.h"

#ifndef MTMPARKINGLOT_UNIQUEARRAY_H
#define MTMPARKINGLOT_UNIQUEARRAY_H

template <class Element, class Compare>
class UniqueArray {

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

	class Filter {
	public:
        virtual bool operator() (const Element&) const = 0;
    };
    UniqueArray filter(const Filter& f) const;

    class UniqueArrayIsFullException{
	};

	class CustomIterator<Element>;

	CustomIterator<Element> begin() {

		return CustomIterator<Element>(elements, len);
	}
	CustomIterator<Element> end() {
		
		return CustomIterator<Element>(elements, len);
	}
};
#include "UniqueArrayImp.h"


#endif //MTMPARKINGLOT_UNIQUEARRAY_H
