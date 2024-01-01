#pragma once
#include <boost/container/flat_set.hpp>
#include <vector>
std::vector<int> removeDuplicates(const std::vector<int>& input) {
    boost::container::flat_set<int> uniqueSet(input.begin(), input.end());
    return std::vector<int>(uniqueSet.begin(), uniqueSet.end());
}