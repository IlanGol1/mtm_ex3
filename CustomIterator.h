#include "UniqueArray.h"

#ifndef CUSTOM_ITERATOR_H
#define CUSTOM_ITERATOR_H

template<Element, Compare>
class CustomIterator {

	UniqueArray<Element, Compare> boss*;
	unsigned int index = 0;
public:
	CustomIterator(UniqueArray<Element, Compare>);

};


#endif