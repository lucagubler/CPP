#include <iostream>
#include <iterator>

int main() {
	using in = std::istreambuf_iterator<char>;
	std::cout << count(in{std::cin}, in{}, '\n');
}
