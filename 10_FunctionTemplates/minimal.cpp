#include <iostream>
#include <string>

template<typename T>
T const & my_min(T const & lhs, T const & rhs) {
	return lhs < rhs ? lhs : rhs;
}

int main() {
	int someNumber{5}, anotherNumber{15};
	std::cout << "Smaller number is: " << my_min(someNumber, anotherNumber) << '\n';

	std::string someCity{"Bern"}, anotherCity{"Zurich"};
	std::cout << "Smaller city is: " << my_min(someCity, anotherCity) << '\n';
}
