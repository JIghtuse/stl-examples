#include <print_container.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

int main()
{
    auto v{std::vector<int>(10)};
    std::iota(v.begin(), v.end(), 0);
    print_container(v, "v: ");

    std::sample(v.begin(), v.end(),
                std::ostream_iterator<int>{std::cout, " "},
                3,
                std::mt19937{std::random_device{}()});
    std::cout << std::endl;
}
