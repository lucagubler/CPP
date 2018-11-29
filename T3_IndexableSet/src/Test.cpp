#include "IndexableSet.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <algorithm>
#include <cctype>
#include <functional>
#include <iterator>
#include <string>
#include <vector>

void test_default_constructed_indexable_set_is_empty() {
	indexableSet<int> const empty_set { };
	ASSERTM("Default constructed indexableSet is expected to be empty.",
			empty_set.empty());
}

void test_iterator_constructor_resulting_size() {
	std::vector<std::string> input { "Pistons", "Spurs", "Heat", "Spurs", "Celtics", "Lakers", "Lakers", "Mavericks", "Heat", "Heat", "Spurs",
			"Warriors", "Cavaliers" };
	indexableSet<std::string> const champions { std::begin(input), std::end(input) };
	ASSERT_EQUALM("An indexableSet constructed with a range of distinct elements specified by iterators is expected to contain all elements of the range.",
			8, champions.size());
}

void test_initializer_list_constructor() {
	indexableSet<std::string> const champions { "Penguins", "Blackhawks", "Kings", "Blackhawks", "Kings", "Bruins", "Blackhawks", "Penguins", "Wings",
			"Ducks", "Hurricanes" };
	ASSERT_EQUALM("An indexableSet constructed with the initializer list constructor is expected to contain all supplied distinct elements.",
			7, champions.size());
}

void test_copy_constructor() {
	indexableSet<std::string> const champions { "Packers", "Giants", "Ravens", "Seahawks", "Patriots", "Broncos" };
	indexableSet<std::string> const copy { champions };
	ASSERT_EQUALM("An indexableSet constructed with the copy constructor is expected to contain the same number of elements as the original indexableSet.",
			6, copy.size());
}

void test_elements_in_iterator_range() {
	indexableSet<std::string> champions { "Yankees", "Giants", "Cardinals", "Sox", "Royals", "Cubs" };
	std::vector<std::string> expected { "Cardinals", "Cubs", "Giants", "Royals", "Sox", "Yankees" };
	std::vector<std::string> actual { std::begin(champions), std::end(champions) };
	ASSERT_EQUALM("An indexableSets iterators are expected to contain all elements in ascending order.",
			expected, actual);
}

void test_elements_in_reverse_iterator_range() {
	indexableSet<std::string> const champions { "Yankees", "Giants", "Cardinals", "Sox", "Royals", "Cubs" };
	std::vector<std::string> expected { "Yankees", "Sox", "Royals", "Giants", "Cubs", "Cardinals" };
	std::vector<std::string> actual { std::rbegin(champions), std::rend(champions) };
	ASSERT_EQUALM("An indexableSets reverse iterators are expected to contain all elements in descending order.",
			expected, actual);
}

void test_at_with_positive_indices() {
	using namespace std::string_literals;
	indexableSet<std::string> const champions { "Yankees", "Giants", "Cardinals", "Sox", "Royals", "Cubs" };
	std::vector<std::string> expected { "Cardinals", "Cubs", "Giants", "Royals", "Sox", "Yankees" };

	for(auto i = 0u; i < champions.size(); i++) {
		auto expected_value = expected.at(i);
		auto actual_value = champions.at(i);
		std::string const message = "Mismatch at index "s + std::to_string(i) + " expected: "s + expected_value + " but was "s + actual_value;
		ASSERT_EQUALM(message, expected_value, actual_value);
	}
}

void test_at_with_negative_indices() {
	using namespace std::string_literals;
	indexableSet<std::string> const champions { "Yankees", "Giants", "Cardinals", "Sox", "Royals", "Cubs" };
	std::vector<std::string> expected { "Cardinals", "Cubs", "Giants", "Royals", "Sox", "Yankees" };

	for(auto i = -1; i >= -static_cast<long>(champions.size()); i--) {
		auto expected_value = expected.at(expected.size() + i);
		auto actual_value = champions.at(i);
		std::string const message = "Mismatch at index "s + std::to_string(i) + " expected: "s + expected_value + " but was "s + actual_value;
		ASSERT_EQUALM(message, expected_value, actual_value);
	}
}

void test_at_with_too_large_index() {
	indexableSet<std::string> const champions { "Yankees", "Giants", "Cardinals", "Sox", "Royals", "Cubs" };
	ASSERT_THROWS(champions.at(6), std::out_of_range);
}

void test_at_with_too_small_index() {
	indexableSet<std::string> const champions { "Yankees", "Giants", "Cardinals", "Sox", "Royals", "Cubs" };
	ASSERT_THROWS(champions.at(-7), std::out_of_range);
}


void test_index_operator_with_positive_indices() {
	using namespace std::string_literals;
	indexableSet<std::string> const champions { "Yankees", "Giants", "Cardinals", "Sox", "Royals", "Cubs" };
	std::vector<std::string> expected { "Cardinals", "Cubs", "Giants", "Royals", "Sox", "Yankees" };

	for(auto i = 0u; i < champions.size(); i++) {
		auto expected_value = expected.at(i);
		auto actual_value = champions[i];
		std::string const message = "Mismatch at index "s + std::to_string(i) + " expected: "s + expected_value + " but was "s + actual_value;
		ASSERT_EQUALM(message, expected_value, actual_value);
	}
}

void test_index_operator_with_negative_indices() {
	using namespace std::string_literals;
	indexableSet<std::string> const champions { "Yankees", "Giants", "Cardinals", "Sox", "Royals", "Cubs" };
	std::vector<std::string> expected { "Cardinals", "Cubs", "Giants", "Royals", "Sox", "Yankees" };

	for (auto i = -1; i >= -static_cast<long>(champions.size()); i--) {
		auto expected_value = expected.at(expected.size() + i);
		auto actual_value = champions[i];
		std::string const message = "Mismatch at index "s + std::to_string(i) + " expected: "s + expected_value + " but was "s + actual_value;
		ASSERT_EQUALM(message, expected_value, actual_value);
	}
}

void test_index_operator_with_too_large_index() {
	indexableSet<std::string> const champions { "Yankees", "Giants", "Cardinals", "Sox", "Royals", "Cubs" };
	ASSERT_THROWS(champions[6], std::out_of_range);
}

void test_index_operator_with_too_small_index() {
	indexableSet<std::string> const champions { "Yankees", "Giants", "Cardinals", "Sox", "Royals", "Cubs" };
	ASSERT_THROWS(champions[-7], std::out_of_range);
}

void test_front_on_empty_throws() {
	indexableSet<std::string> const empty {};
	ASSERT_THROWS(empty.front(), std::out_of_range);
}

void test_front_on_non_empty_gets_first() {
	indexableSet<std::string> const champions { "Yankees", "Giants", "Cardinals", "Sox", "Royals", "Cubs" };
	ASSERT_EQUAL("Cardinals", champions.front());
}

void test_back_on_empty_throws() {
	indexableSet<std::string> const empty {};
	ASSERT_THROWS(empty.back(), std::out_of_range);
}

void test_back_on_non_empty_gets_last() {
	indexableSet<std::string> const champions { "Yankees", "Giants", "Cardinals", "Sox", "Royals", "Cubs" };
	ASSERT_EQUAL("Yankees", champions.back());
}

void test_elements_in_iterator_range_with_custom_comparator() {
	indexableSet<std::string, std::greater<>> champions { "Yankees", "Giants", "Cardinals", "Sox", "Royals", "Cubs" };
	std::vector<std::string> expected { "Yankees", "Sox", "Royals", "Giants", "Cubs", "Cardinals" };
	ASSERT_EQUAL_RANGESM("An indexableSet with supplied std::greater compare functor is expected to contain the elements in descending order.",
			std::begin(expected), std::end(expected), std::begin(champions), std::end(champions));
}

void test_elements_returned_by_index_and_at_are_returned_by_lvalue_reference() {
	indexableSet<int> const values{42};
	ASSERT_EQUAL(&values.at(0), &values[0]);
}

void test_elements_returned_by_front_and_back_are_returned_by_lvalue_reference() {
	indexableSet<int> const values{42};
	ASSERT_EQUAL(&values.front(), &values.back());
}

// Test Functor
struct caselessCompare {
	bool operator()(const std::string &l, const std::string &r) {
		return std::lexicographical_compare(
			std::begin(l), std::end(l),
			std::begin(r), std::end(r),
			[](char a, char b) {
				return std::tolower(a) < std::tolower(b);
			});
	}
};

void test_elements_in_iterator_range_with_custom_functor() {
	indexableSet<std::string, caselessCompare> champions { "yankees", "Giants", "cardinals", "Sox", "Royals", "cubs" };
	std::vector<std::string> expected { "cardinals", "cubs", "Giants", "Royals", "Sox", "yankees" };
	ASSERT_EQUAL_RANGESM("An indexableSet with supplied casless compare functor is expected to contain the elements in casless lexicographical order",
				std::begin(expected), std::end(expected), std::begin(champions), std::end(champions));
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite constructor_tests { };
	constructor_tests.push_back(CUTE(test_default_constructed_indexable_set_is_empty));
	constructor_tests.push_back(CUTE(test_iterator_constructor_resulting_size));
	constructor_tests.push_back(CUTE(test_initializer_list_constructor));
	constructor_tests.push_back(CUTE(test_copy_constructor));
	constructor_tests.push_back(CUTE(test_elements_in_iterator_range));
	constructor_tests.push_back(CUTE(test_elements_in_reverse_iterator_range));
	constructor_tests.push_back(CUTE(test_at_with_positive_indices));
	constructor_tests.push_back(CUTE(test_at_with_negative_indices));
	constructor_tests.push_back(CUTE(test_at_with_too_large_index));
	constructor_tests.push_back(CUTE(test_at_with_too_small_index));
	constructor_tests.push_back(CUTE(test_index_operator_with_positive_indices));
	constructor_tests.push_back(CUTE(test_index_operator_with_negative_indices));
	constructor_tests.push_back(CUTE(test_index_operator_with_too_large_index));
	constructor_tests.push_back(CUTE(test_index_operator_with_too_small_index));
	constructor_tests.push_back(CUTE(test_front_on_empty_throws));
	constructor_tests.push_back(CUTE(test_front_on_non_empty_gets_first));
	constructor_tests.push_back(CUTE(test_back_on_empty_throws));
	constructor_tests.push_back(CUTE(test_back_on_non_empty_gets_last));
	constructor_tests.push_back(CUTE(test_elements_in_iterator_range_with_custom_comparator));
	constructor_tests.push_back(CUTE(test_elements_returned_by_index_and_at_are_returned_by_lvalue_reference));
	constructor_tests.push_back(CUTE(test_elements_returned_by_front_and_back_are_returned_by_lvalue_reference));
	constructor_tests.push_back(CUTE(test_elements_in_iterator_range_with_custom_functor));

	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto const runner { cute::makeRunner(lis, argc, argv) };
	return runner(constructor_tests, "Indexable Set Tests");
}

int main(int argc, char const *argv[]) {
	return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}

