#include <iterator>
#include <iostream>

int main() {
	using in = std::istream_iterator<char>;
	std::cout << count(in{std::cin}, in{}, 'a');
}
