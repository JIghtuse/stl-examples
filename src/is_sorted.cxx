#include <print_container.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

int main()
{
    auto v{std::vector<int>(10, 3)};
    std::iota(v.begin(), v.end(), 1);

    std::random_device rd;
    std::mt19937 gen{rd()};

    std::shuffle(v.begin(), v.end(), gen);

    print_container(v, "v initially:     ");
    std::cout << " is sorted: " << std::is_sorted(v.begin(), v.end()) << std::endl;

    std::sort(v.begin(), v.end());

    print_container(v, "v after sorting: ");
    std::cout << " is sorted: " << std::is_sorted(v.begin(), v.end()) << std::endl;
}
