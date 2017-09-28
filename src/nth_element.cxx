#include <print_container.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

// Based on http://en.cppreference.com/w/cpp/algorithm/nth_element
int main()
{
    std::vector<int> v{5, 6, 4, 3, 2, 6, 7, 9, 3};
    print_container(v, "initially:            ");

    std::nth_element(v.begin(), v.begin() + v.size() / 2, v.end());
    std::cout << "The median is " << v[v.size() / 2] << std::endl;

    print_container(v, "after finding median: ");

    auto order = 3u;
    std::nth_element(v.begin(), v.begin() + order, v.end(), std::greater<>());
    std::cout << "The " << order << " largest element is " << v[order] << std::endl;

    print_container(v, "now:                  ");

    order = 1u;
    std::nth_element(v.begin(), v.begin() + order, v.end(), std::greater<>());
    std::cout << "The " << 1 + order << " largest element is " << v[order] << std::endl;

    print_container(v, "finally:              ");
}
