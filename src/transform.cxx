#include <algorithm>
#include <array>
#include <iostream>

int main()
{
    auto print_container = [](const auto& c) {
        for (auto i : c)
            std::cout << i << ' ';
        std::cout << std::endl;
    };

    std::array<double, 10> a{ { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } };
    std::cout << "initially: ";
    print_container(a);

    auto max = *std::max_element(a.cbegin(), a.cend());
    std::transform(a.begin(), a.end(), a.begin(),
                   [max](auto i) { return i / max; });

    std::cout << "after normalization: ";
    print_container(a);

    std::array<double, 10> weights{ { 10, 20, 10, 30, 20 } };
    std::transform(a.begin(), a.end(), weights.begin(), a.begin(),
                   [](auto i, auto j) { return i * j; });

    std::cout << "after weighting: ";
    print_container(a);
}
