#include <string>
#include <iostream>

void print(std::ostream & out){
	out << "Basecase has been reached!\n";
}

template<typename First, typename...Args>
void print(std::ostream & out, First f, Args...args) {
	out << "First is: " << f << " and there are " << sizeof...(args) << " additional arguments\n";
	print(out, args...);
}

int main() {
	int i = 5;
	float f = 3.14159;
	std::string s = "Hello";
	char c = '*';
	print(std::cout, i, f, s, c);
}
