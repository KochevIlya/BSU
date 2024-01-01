#define BOOST_TEST_MODULE MyTest
#include "Header.h"
#include <boost/test/included/unit_test.hpp>    

BOOST_AUTO_TEST_CASE(test_calculateFactorial) {
    BOOST_CHECK_EQUAL(calculateFactorial(0), 1);
    BOOST_CHECK_EQUAL(calculateFactorial(5), 120);

}
