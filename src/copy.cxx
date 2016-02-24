#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>

template <typename Container>
void print_container(const Container& c, std::ostream& out = std::cout, const char* delim = " ")
{
    using ValueType = typename Container::value_type;
    std::copy(c.begin(), c.end(), std::ostream_iterator<ValueType>(out, delim));
    out << std::endl;
}

template <typename Container, typename Predicate>
void print_container_if(const Container& c, std::ostream& out, const char* delim, Predicate p)
{
    using ValueType = typename Container::value_type;
    std::copy_if(c.begin(), c.end(), std::ostream_iterator<ValueType>(out, delim), p);
    out << std::endl;
}

int main()
{
    std::array<int, 10> fib_sequence{ 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
    print_container(fib_sequence);
    print_container_if(fib_sequence, std::cout, " ", [](int i) { return i < 42; });

    std::array<char, 5> hello{ 'h', 'e', 'l', 'l', 'o' };
    print_container(hello, std::cout, "");

    auto hello_world = std::string{ "Hello, world!" };
    print_container_if(hello_world, std::cout, "", [](char c) { return c != 'l'; });

    auto is_vowel = [](char c) {
        std::string vowels{ "aeiou" };
        return vowels.find(c) != std::string::npos;
    };

    auto vowels = std::string{};
    std::copy_if(hello_world.begin(), hello_world.end(),
                 std::back_inserter(vowels), is_vowel);
    std::cout << "Vowels of \"" << hello_world << "\":     ";
    print_container(vowels);

    auto non_vowels = std::string{};
    std::remove_copy_if(hello_world.begin(), hello_world.end(),
                        std::back_inserter(non_vowels), is_vowel);
    std::cout << "Non-vowels of \"" << hello_world << "\": ";
    print_container(non_vowels);
}
