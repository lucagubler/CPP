#include <iterator>
#include <iostream>

int main() {
	using in = std::istreambuf_iterator<char>;
	std::cout << distance(in{std::cin}, in{});
}
