#include <vector>
#include <iostream>

using std::equal_to;

//element needs to have a copy costructor and an assignment operator overload (but an empty constructor is not necessary)
template <class Element, class Compare = equal_to<Element>>
class UniqueArray{

	int len = 0;
	Compare cmp;

	Element elements[];
	bool used_positions[];

public:

	UniqueArray(unsigned int len) {
		
		this.elements = new Element[len];
		this.used_positions = new bool[len];
		empty_positions();

		this.len = len;
		this.cmp = new Compare();
	}

	UniqueArray(const UniqueArray& other) {
		
		this.elements = new Element[other.len];
		this.used_positions = new bool[other.len];

		empty_positions();

		for(int i = 0; i < other.size; i++) {			
			if (other.used_positions[i]) {
				this.used_positions[i] = true;
				this.elements[i] = new Element(other.elements[i]);
			}
		}
		this.len = other.len;
		this.cmp = new Compare();
	}
	~UniqueArray() {

		delete[] elements;
		delete[] used_positions;
		delete len;
		delete cmp;
	}

	class ArrayIsFullException : std::exception {
		const char* what() const throw () {
			return "Array Is Full!";
		}
	};

	unsigned int insert(const Element& element) {
		int i = first_not_used();
		if (i != len) {
			this.elements[i] = new Element(element);
			return i;
		}
		//throw out of bounds error:

		throw new ArrayIsFullException();
	}

	bool getIndex(const Element& element, unsigned int& index) const {
		
		for (int i = 0; i < len; i++) {
			if (used_positions[i]) if (cmp(element, elements[i])) { index = i; return true; }
		}
		return false;
	}

	const Element* operator[] (const Element& element) const{

		unsigned int index = 0;
		if (!getIndex(element, index)) return NULL;

		return this.elements + index;
	}

	bool remove(const Element& element) {
		unsigned int index = 0;
		
		if (!getIndex(element, index)) return false;
		delete elements[index];
		used_positions[index] = false;

		return true;
	}

	unsigned int count() const {
		
		int count = 0;
		for (int i = 0; i < len; i++) if (used_positions[i]) count++;

		return count;
	}

	unsigned int size() const {

		return len;
	}

	class Filter {
		virtual bool operator() (const Element&) = 0;
	};

	UniqueArray<Element, Compare> filter(const Filter& f) const {
		UniqueArray<Element, Compare> res = new UniqueArray<Element, Compare>(*this);
		for (int i = 0; i < size; i++) {
			
			if (used_positions[i]) if (!f(elements[i])) {
				
				delete res.elements[i];
				res.used_positions[i] = false;
			}
		}

		return res;
	}

private:
	inline void empty_positions( ) {

		for (int i = 0; i < this.size; i++) this.used_positions[i] = false;
	}

	inline int first_not_used() {
		
		for (int i = 0; i < this.size; i++) if (!this.used_positions[i]) return i;
		return this.len;
	}	

};
