#ifndef WORD_H_
#define WORD_H_

#include <algorithm>
#include <cctype>
#include <string>
#include <istream>
#include <iterator>

namespace word {

class Word {
	std::string word{};

public:
	Word() = default;
	explicit Word(std::string word);

	std::ostream & print(std::ostream & os) const {
		os << word;
		return os;
	}

	std::istream & read(std::istream & is) {
		char character{};
		std::string inputString{};
		while (is.get(character)) {
			if (std::isalpha(character)) {
				inputString += character;
			} else {
				// At least one alphabetical character must be read
				if (!inputString.empty()) {
					is.putback(character);
					break;
				}
			}
		}
		if (!inputString.empty()) {
			word = inputString;
			is.clear();
		} else {
			is.setstate(std::ios::failbit);
		}
		return is;
	}

	inline bool operator<(Word const &rhs) const {
		return std::lexicographical_compare(
			std::begin(word), std::end(word),
			std::begin(rhs.word), std::end(rhs.word),
			[](char a, char b) {
				return std::tolower(a) < std::tolower(b);
			});
	}
};

inline std::ostream & operator<<(std::ostream & os, Word const & word) {
	return word.print(os);
}

inline std::istream & operator>>(std::istream & in, Word & word) {
	return word.read(in);
}

inline bool operator>(Word const & lhs, Word const & rhs) {
	return rhs < lhs;
}

inline bool operator>=(Word const & lhs, Word const & rhs) {
	return !(lhs < rhs);
}

inline bool operator<=(Word const & lhs, Word const & rhs) {
	return !(rhs < lhs);
}

inline bool operator==(Word const & lhs, Word const & rhs) {
	return !(lhs < rhs) && !(rhs < lhs);
}

inline bool operator!=(Word const & lhs, Word const & rhs) {
	return !(lhs == rhs);
}

}

#endif
