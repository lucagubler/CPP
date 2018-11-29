#include "kwic.h"
#include "word.h"
#include <algorithm>
#include <iterator>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace word;

namespace kwic {

std::vector<Word> getWordsFromLine(const std::string & line) {
	std::istringstream is{line};
	using istream = std::istream_iterator<Word>;
	return std::vector<Word>{istream{is}, istream{}};
}

std::vector<std::vector<Word>> getWordsPerLine(std::istream & in) {
	std::string line{};
	std::vector<std::vector<Word>> wordsPerLine{};

	while (std::getline(in, line)) {
		wordsPerLine.push_back(getWordsFromLine(line));
	}
	return wordsPerLine;
}

std::set<std::vector<Word>> shiftCircularly(const std::vector<std::vector<Word>> & words) {
	std::set<std::vector<Word>> shiftedWords{};

	std::for_each(words.begin(), words.end(),
		[&shiftedWords](std::vector<Word> word) {
			for(auto i = 0u; i < word.size(); i++) {
				std::rotate(word.begin(), word.begin() + 1, word.end());
				shiftedWords.insert(word);
			}
		}
	);
	return shiftedWords;
}

void print(const std::set<std::vector<word::Word>> & lines, std::ostream & out) {
	std::for_each(lines.begin(), lines.end(),
		[&out](const std::vector<Word> & word) {
			std::copy(word.begin(), word.end(), std::ostream_iterator<Word>{out, " "});
			out << "\n";
		}
	);
}

void kwic(std::istream & in, std::ostream & out) {
	const auto wordsPerLine{getWordsPerLine(in)};
	print(shiftCircularly(wordsPerLine), out);
}

}
