#include <print_container.h>
#include <algorithm>
#include <array>
#include <iostream>

int main()
{
    auto b{ 1 };
    auto a{ 5 };

    std::cout << "max of " << a << " and " << b << ": "
              << std::max(a, b) << std::endl;

    auto lst = { 1, 5, 3, 2, 4 };

    print_container(lst, "max of ");
    std::cout << ": " << std::max(lst) << std::endl;

    constexpr auto x_size{3};
    constexpr auto y_size{5};

    auto array{std::array<int, std::max(x_size, y_size)>{}};
    std::cout << "array size enough to keep "
              << x_size << " or " << y_size << " elements: "
              << array.size() << std::endl;

    auto digits_sum = [](int i) {
        const auto base{10};
        auto sum{0};
        while (i) {
            sum += i % base;
            i /= base;
        }
        return sum;
    };
    auto digits_sum_larger = [digits_sum](const int& x, const int& y) {
        return digits_sum(x) < digits_sum(y);
    };

    auto int_list = { 111, 123, 900, 555, 324 };
    print_container(int_list, "max (by sum of digits) of ");
    std::cout << ": " << std::max(int_list, digits_sum_larger) << std::endl;
}
