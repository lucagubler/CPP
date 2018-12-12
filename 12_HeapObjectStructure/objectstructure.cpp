#include <vector>
#include <memory>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>

using PersonPtr = std::shared_ptr<class Person>;

struct Person : std::enable_shared_from_this<Person> {
	Person(std::string name = "Robin") : name{name}{}
	~Person() {
		std::cout << "RIP " << name << '\n';
	}
	void adoptChild(PersonPtr child) {
		children.push_back(child);
		child->parent = shared_from_this();
	}
	void print(std::ostream & out, bool printChildren = false) const {
		out << "Person named '" << name << "' has " << children.size() << " children\n";
		if (parent) {
			out << "My parent is " << parent->name << '\n';
		}
		if (printChildren) {
			copy(children.begin(), children.end(), std::ostream_iterator<PersonPtr>{out});
		}
	}
private:
	std::vector<PersonPtr> children{};
	PersonPtr parent{};
	std::string name{};
};

std::ostream & operator<<(std::ostream & out, PersonPtr person) {
	person->print(out, true);
	return out;
}

int main() {
	PersonPtr morgan = std::make_shared<Person>("Morgan");
	std::cout << morgan << '\n';
	PersonPtr jamie = std::make_shared<Person>("Jamie");
	PersonPtr taylor = std::make_shared<Person>("Taylor");
	morgan->adoptChild(jamie);
	morgan->adoptChild(taylor);
	PersonPtr luca = std::make_shared<Person>("Luca");
	PersonPtr abi = std::make_shared<Person>("Abi");
	jamie->adoptChild(luca);
	jamie-> adoptChild(abi);
	std::cout << morgan << '\n';
}
