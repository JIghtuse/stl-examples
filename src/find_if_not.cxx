#include <print_container.h>
#include <algorithm>
#include <array>
#include <iostream>

int main()
{
    std::array<int, 6> values{ { 3, 4, 2, 1, -1, 0 } };

    print_container(values, "Array values: ");

    auto positive = [](auto i) { return i > 0; };

    auto positive_pos = std::find_if(values.begin(), values.end(), positive);
    if (positive_pos != values.end())
        std::cout << "Index of first positive value: "
                  << std::distance(values.begin(), positive_pos)
                  << std::endl;

    auto non_positive_pos = std::find_if_not(values.begin(), values.end(), positive);
    if (non_positive_pos != values.end())
        std::cout << "Index of first non-positive value: "
                  << std::distance(values.begin(), non_positive_pos)
                  << std::endl;
}
