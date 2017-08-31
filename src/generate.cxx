#include <algorithm>
#include <array>
#include <iostream>
#include <tuple>
#include <print_container.h>

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
    
    print_container(values, "values: ");

    constexpr auto countdownFrom = 10;
    auto countdown = std::array<int, countdownFrom + 1>();
    std::generate(countdown.begin(), countdown.end(), [x = countdownFrom + 1]() mutable {
        return --x;
    });

    print_container(countdown, "countdown: ");
}
