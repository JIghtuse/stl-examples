#include <algorithm>
#include <array>
#include <iostream>
#include <print_container.h>

int main()
{
    std::array<double, 10> a{ { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } };
    print_container(a, "initially: ");

    auto max = *std::max_element(a.cbegin(), a.cend());
    std::transform(a.begin(), a.end(), a.begin(),
                   [max](auto i) { return i / max; });

    print_container(a, "after normalization: ");

    std::array<double, 10> weights{ { 10, 20, 10, 30, 20 } };
    std::transform(a.begin(), a.end(), weights.begin(), a.begin(),
                   [](auto i, auto j) { return i * j; });

    print_container(a, "after weighting: ");
}
