#ifndef UNIQUE_ARRAY_ITERATOR_H
#define UNIQUE_ARRAY_ITERATOR_H

template <class Element, class Compare> class UniqueArray;

/**
 * It's an iterator, of a class unique array.
 * @tparam Element The element of unique array.
 * @tparam Compare The comparison function of unique array.
 */
template <class Element, class Compare>
class UniqueArrayIterator {
    /**
     * Holds our parking lot and indexes where to look.
     */
    const UniqueArray<Element,Compare>& uniqueArray;
    unsigned int index;
public:

    /**
     * The constructor of the iterator.
     * @param uniqueArray our array.
     * @param start_index where to look in the array.
     */
    UniqueArrayIterator(const UniqueArray<Element,
                        Compare>& uniqueArray,
                        unsigned int start_index);

	/**
	 * @return Pointer to current element.
	 */
	Element*& operator*();

	/**
	 * Adds 1 to the value of index.
	 */
	void operator++();

    /**
     * Subtracts 1 from the value of index.
     */
    void operator--();

    /**
     * Adds i to our index.
     */
	void operator+=(unsigned int i);

	/**
	 * Subtracts i from our index.
	 */
	void operator-=(unsigned int i);

    /**
     * Performs "==" operation between two iterators.
     * @tparam E gets the element type.
     * @tparam C gets the compare function between 2 elements.
     * @param first element.
     * @param second element.
     * @return boolean value with are equal (true) or different (false)
     */
    template <class E, class C>
    friend bool operator==(const UniqueArrayIterator<E,C>& first,
                           const UniqueArrayIterator<E,C>& second);

    /**
     * Performs "!=" operation between two iterators.
     * @tparam E gets the element type.
     * @tparam C gets the compare function between 2 elements.
     * @param first element.
     * @param second element.
     * @return boolean value with are equal (true) or different (false)
     */
    template <class E, class C>
    friend bool operator!=(const UniqueArrayIterator<E,C>& first,
                           const UniqueArrayIterator<E,C>& second);
	};

#include "UniqueArrayIteratorImp.h"

#endif