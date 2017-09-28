#include <print_container.h>
#include <algorithm>
#include <functional>
#include <numeric>
#include <random>
#include <vector>

std::vector<int> get_data()
{
    auto v = std::vector<int>(20, 0);
    std::iota(v.begin(), v.end(), 0);

    std::random_device rd;
    std::mt19937 g{rd()};

    std::shuffle(v.begin(), v.end(), g);

    return v;
}

int main()
{
    auto v = get_data();
    print_container(v, "v initially: ");

    const auto n = 3;
    std::partial_sort(v.begin(), v.begin() + n, v.end(), std::greater<>());

    std::cout << n << " largest values:  ";
    for (auto it = v.begin(); it != v.begin() + n; ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    print_container(v, "v now:       ");

    std::partial_sort(v.begin(), v.begin() + n, v.end());
    std::cout << n << " smallest values: ";
    for (auto it = v.begin(); it != v.begin() + n; ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    print_container(v, "v now:       ");

    auto top5 = std::vector<int>(5, 0);
    std::partial_sort_copy(v.begin(), v.end(), top5.begin(), top5.end(), std::greater<>());
    print_container(top5, "top5 elements:     ");
}
