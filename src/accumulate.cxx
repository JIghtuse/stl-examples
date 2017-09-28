#include <print_container.h>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    auto v{std::vector<int>(10)};
    std::iota(v.begin(), v.end(), 1);

    auto sum = std::accumulate(v.begin(), v.end(), 0);
    auto sqsum = std::accumulate(v.begin(), v.end(), 0, [](const int& a, const int& b) {
        return a + b * b;
    });
    auto product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<>());

    print_container(v, "v: ");
    std::cout << "sum of elements:     " << sum << std::endl;
    std::cout << "sqsum of elements:   " << sqsum << std::endl;
    std::cout << "product of elements: " << product << std::endl;

    std::cout << "enter some numbers: ";
    auto input_sum = std::accumulate(std::istream_iterator<double>{std::cin},
                                     std::istream_iterator<double>{},
                                     0);

    std::cout << "sum of input numbers: " << input_sum << std::endl;
}
