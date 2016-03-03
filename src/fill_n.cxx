#include <algorithm>
#include <iostream>
#include <vector>
#include <print_container.h>

int main()
{
    std::vector<int> v(9);
    print_container(v, "initially:                              ");

    auto it = std::fill_n(v.begin(), v.size() / 2, -1);
    print_container(v, "after std::fill_n half of the elements: ");

    std::fill(it, v.end(), 1);
    print_container(v, "after std::fill remaining elements:     ");
}
