#include "Sack.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <string>

void testDefaultSackIsEmpty() {
	Sack<int> values{};
	ASSERT(values.empty());
}

void testDefaultSackHasSizeZero() {
	Sack<int> values{};
	ASSERT_EQUAL(0, values.size());
}

void testSackIsNotEmptyAfterInsertingAnElement() {
	Sack<int> values{};
	values.putInto(5);
	ASSERT(!values.empty());
}

void testSizeOfSackIsOneAfterInsertingAnElement() {
	Sack<int> values{};
	values.putInto(5);
	ASSERT_EQUAL(1, values.size());
}

void testGetOutReturnsElement() {
	Sack<std::string> values{};
	values.putInto("Element");
	ASSERT_EQUAL("Element", values.getOut());
}

void testGetOutThrowsIfSackIsEmpty() {
	Sack<std::string> values{};
	ASSERT_THROWS(values.getOut(), std::logic_error);
}

void testSackIsEmptyAfterGettingOutLastElement() {
	Sack<double> values{};
	values.putInto(3.14159);
	values.getOut();
	ASSERT(values.empty());
}

void testSackIsZeroAfterGettingOutLastElement() {
	Sack<double> values{};
	values.putInto(3.14159);
	values.getOut();
	ASSERT_EQUAL(0, values.size());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(testDefaultSackIsEmpty));
	s.push_back(CUTE(testDefaultSackHasSizeZero));
	s.push_back(CUTE(testSackIsNotEmptyAfterInsertingAnElement));
	s.push_back(CUTE(testSizeOfSackIsOneAfterInsertingAnElement));
	s.push_back(CUTE(testGetOutReturnsElement));
	s.push_back(CUTE(testGetOutThrowsIfSackIsEmpty));
	s.push_back(CUTE(testSackIsEmptyAfterGettingOutLastElement));
	s.push_back(CUTE(testSackIsZeroAfterGettingOutLastElement));
	//TODO add your test here
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
