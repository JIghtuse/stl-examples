#include <print_container.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

int main()
{
    auto v{std::vector<int>{1, 2, 3, 4, 5}};
    print_container(v, "initially:          ");

    std::random_device rd;
    std::mt19937 g{rd()};

    std::shuffle(v.begin(), v.end(), g);
    print_container(v, "after std::shuffle: ");
}
