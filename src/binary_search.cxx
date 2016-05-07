#include <print_container.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

std::vector<size_t> gen_primes(size_t nPrimes)
{
    auto primes = std::vector<size_t>{};
    primes.reserve(nPrimes);
    if (nPrimes > 1) {
        primes.push_back(2);
    }
    auto cur = size_t{1};
    while (primes.size() != nPrimes) {
        cur += 2;
        auto not_factor = [cur](size_t prime) {
            return cur % prime != 0;
        };
        if (std::all_of(primes.begin(), primes.end(), not_factor)) {
            primes.push_back(cur);
        }
    }
    return primes;
}

int main()
{
    auto nPrimes = size_t{10};
    auto primes = gen_primes(nPrimes);

    const int x = 31;
    std::cout << std::boolalpha;
    std::cout << x << " is in first "
              << nPrimes << " prime numbers: "
              << std::binary_search(primes.begin(), primes.end(), x)
              << std::endl;

    nPrimes *= 2;
    primes = gen_primes(nPrimes);

    std::cout << x << " is in first "
              << nPrimes << " prime numbers: "
              << std::binary_search(primes.begin(), primes.end(), x)
              << std::endl;
}
