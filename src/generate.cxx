#include <algorithm>
#include <array>
#include <iostream>
#include <tuple>

struct FibGenerator {
    FibGenerator()
        : a{ 1 }
        , b{ 0 }
    {
    }
    size_t operator()()
    {
        std::tie(a, b) = std::make_pair(b + a, a);
        return b;
    }

private:
    size_t a;
    size_t b;
};

int main(void)
{
    auto values = std::array<size_t, 30>();
    std::generate(values.begin(), values.end(), FibGenerator{});

    std::cout << "values: ";
    for (auto e : values)
        std::cout << e << ' ';
    std::cout << std::endl;
}
