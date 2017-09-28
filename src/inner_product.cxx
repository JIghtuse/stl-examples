#include <print_container.h>
#include <functional>
#include <numeric>
#include <vector>

int main()
{
    auto a{std::vector<int>{5, 4, 0, 2, 3}};
    auto b{std::vector<int>{1, 4, 2, 5, 3}};

    auto product = std::inner_product(a.begin(), a.end(), b.begin(), 0);
    print_container(a, "a: ");
    print_container(b, "b: ");
    std::cout << "Inner product of a and b: " << product << std::endl;

    auto hamming_distance = std::inner_product(a.begin(), a.end(), b.begin(), 0,
                                               std::plus<>(), std::not_equal_to<>());
    std::cout << "Hamming distance between a and b: " << hamming_distance << std::endl;
}
