#include <print_container.h>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

// Based on http://en.cppreference.com/w/cpp/algorithm/adjacent_difference
int main()
{
    std::vector<int> fib(12, 1);
    std::adjacent_difference(fib.begin(), fib.end() - 1, fib.begin() + 1, std::plus<int>());

    print_container(fib, "Fibonacci sequence: ");

    std::vector<int> seq(9, 1);
    std::iota(seq.begin(), seq.end(), 0);
    print_container(seq, "sequence:                          ");

    std::cout << "adjacent difference of a sequence: ";
    std::adjacent_difference(seq.begin(), seq.end(),
                             std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
