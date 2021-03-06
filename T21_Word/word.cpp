#include "word.h"
#include <cctype>
#include <string>
#include <stdexcept>

namespace word {

Word::Word(std::string word) : word{word} {
	if(word.empty()) {
		throw std::invalid_argument{"Word can't be empty!"};
	}
	for(auto const & c : word) {
		if(!std::isalpha(c)) {
			throw std::invalid_argument{"Word can't contain non alphabetic chars!"};
		}
	}
}

}
