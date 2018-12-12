#ifndef SRC_SACK_H_
#define SRC_SACK_H_

#include <stdexcept>
#include <vector>


template<typename T>
class Sack {
	using SackType = std::vector<T>;
	using size_type = typename SackType::size_type;

	SackType theSack{};

public:
	bool empty() const {
		return theSack.empty();
	}

	size_type size() const {
		return theSack.size();
	}

	void putInto(T const & element) {
		theSack.push_back(element);
	}

	T getOut() {
		if (theSack.empty()) {
			throw std::logic_error{"Sack cannot be empty"};
		}
		auto indexToRemove = static_cast<size_type>(rand() % size());
		T returnValue{theSack.at(indexToRemove)};
		theSack.erase(next(theSack.begin(), indexToRemove));
		return returnValue;
	}
};


#endif /* SRC_SACK_H_ */
