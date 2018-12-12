#ifndef KWIC_H_
#define KWIC_H_

#include "word.h"
#include <iosfwd>
#include <set>
#include <string>
#include <vector>

namespace kwic {

std::vector<word::Word> getWordsFromLine(const std::string & line);
std::vector<std::vector<word::Word>> getWordsPerLine(std::istream & in);
std::set<std::vector<word::Word>> shiftCircularly(const std::vector<std::vector<word::Word>> & words);
void print(const std::set<std::vector<word::Word>> & lines, std::ostream & out);
void kwic(std::istream & in, std::ostream & out);

}



#endif /* KWIC_H_ */
