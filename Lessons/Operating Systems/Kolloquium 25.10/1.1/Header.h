
#pragma once

#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;
mp::cpp_int calculateFactorial(int num)
{
        if (num == 0 || num == 1) {
            return 1;
        }
        return num * calculateFactorial(num - 1);
}

