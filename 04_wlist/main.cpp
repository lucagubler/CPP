#include <iterator>
#include <iostream>
#include <string>
#include <set>
#include <algorithm>

int main() {
	using in = std::istream_iterator<std::string>;
	std::set<std::string> wlist{in{std::cin}, in{}};
	copy(wlist.begin(), wlist.end(), std::ostream_iterator<std::string>{std::cout, "\n"});
}
