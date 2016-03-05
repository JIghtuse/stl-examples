#include <algorithm>
#include <iostream>
#include <iterator>
#include <regex>
#include <vector>
// Part of the example lives in this header
#include <print_container.h>

int main()
{
    std::array<int, 10> values{ 1, 1, 2, 3, 5, 8, 13, 21, 34, 55 };
    print_container(values, "initial values:                  ");

    auto max_value = 30;
    print_container_if(values, [max_value](int v) { return v > max_value; },
                       "values larger then 30:           ");
    print_container_if_not(values, [max_value](int v) { return v > max_value; },
                       "values less then or equal to 30: ");

    std::array<int, 10> numbers{ 1, 0, 2, 3, 5, 0, 3, 4, 1, 0 };
    print_container(numbers, "all numbers:       ");

    std::vector<int> non_zero;
    std::remove_copy(numbers.begin(), numbers.end(), std::back_inserter(non_zero), 0);
    print_container(non_zero, "non-zero numbers:  ");
}
