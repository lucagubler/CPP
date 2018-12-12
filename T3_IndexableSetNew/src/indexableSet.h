#ifndef SRC_INDEXABLESET_H_
#define SRC_INDEXABLESET_H_

#include <functional>
#include <iterator>
#include <set>
#include <stdexcept>


template<typename T, class COMPARE=std::less<T>>
class indexableSet : public std::set<T, COMPARE> {
public:
	using std::set<T, COMPARE>::set;

	T const & at(int index) const {
		int size = this->size();
		if (index < size && index >= (-size)) {
			if (index < 0) {
				index += size;
			}
			auto it{this->begin()};
			std::advance(it, index);
			return *it;
		} else {
			throw std::out_of_range{"Index out of range"};
		}
	}

	T const & operator[](int index) const {
		return this->at(index);
	}

	T const & front() const {
		return this->at(0);
	}

	T const & back() const {
		return this->at(this->size()-1);
	}
};


#endif /* SRC_INDEXABLESET_H_ */
