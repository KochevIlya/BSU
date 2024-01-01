#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>    
#include "Header.h"

BOOST_AUTO_TEST_CASE(empty_vector_test) {
    std::vector<int> input;
    std::vector<int> result = removeDuplicates(input);
    BOOST_CHECK(result.empty());
}

BOOST_AUTO_TEST_CASE(no_duplicates_test) {
    std::vector<int> input = { 1, 2, 3, 4, 5 };
    std::vector<int> result = removeDuplicates(input);
    BOOST_CHECK_EQUAL_COLLECTIONS(input.begin(), input.end(), result.begin(), result.end());
}

BOOST_AUTO_TEST_CASE(all_duplicates_test) {
    std::vector<int> input = { 1, 1, 1, 1, 1 };
    std::vector<int> result = removeDuplicates(input);
    std::vector<int> expected_result = { 1};
    BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(), result.end(), expected_result.begin(), expected_result.end());
}

BOOST_AUTO_TEST_CASE(mixed_duplicates_test) {
    std::vector<int> input = { 1, 2, 3, 2, 4, 5, 3 };
    std::vector<int> result = removeDuplicates(input);
    std::vector<int> expected_result = { 1, 2, 3, 4, 5 };
    BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(), result.end(), expected_result.begin(), expected_result.end());
}
