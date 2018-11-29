#include "word.h"
#include <cctype>
#include <string>
#include <stdexcept>

namespace word {

Word::Word(std::string word) : word{word} {
	if (word.empty()) {
		throw std::invalid_argument("Word can not be empty");
	}
	for (auto const & c : word) {
		if (!std::isalpha(c)) {
			throw std::invalid_argument("Word can only have alphabetical characters");
		}
	}
}

}
