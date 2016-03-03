#include <algorithm>
#include <array>
#include <iostream>
#include <string>
// Part of the example lives in this header
#include <print_container.h>

template <typename Container, typename Predicate>
void print_container_if(const Container& c, Predicate p,
                        const char* header="", const char* delim = " ",
                        std::ostream& out = std::cout)
{
    out << header;
    using ValueType = typename Container::value_type;
    std::copy_if(c.begin(), c.end(), std::ostream_iterator<ValueType>(out, delim), p);
    out << std::endl;
}

int main()
{
    std::array<int, 10> fib_sequence{ { 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 } };
    print_container(fib_sequence, "fibonacci sequence: ");
    print_container_if(fib_sequence, [](int i) { return i < 42; },
                       "fibbonaci sequence with values less then 42: ");

    std::array<char, 5> hello{ { 'h', 'e', 'l', 'l', 'o' } };
    print_container(hello, "array of chars 'hello': ", "");

    auto hello_world = std::string{ "Hello, world!" };
    print_container_if(hello_world, [](char c) { return c != 'l'; },
                       "'Hello, world' without 'l': ", "");

    auto is_vowel = [](char c) {
        std::string vowels{ "aeiou" };
        return vowels.find(c) != std::string::npos;
    };

    auto vowels = std::string{};
    std::copy_if(hello_world.begin(), hello_world.end(),
                 std::back_inserter(vowels), is_vowel);
    std::cout << "Vowels of \"" << hello_world << "\":     ";
    print_container(vowels, "vowels of 'Hello, world': ");

    auto non_vowels = std::string{};
    std::remove_copy_if(hello_world.begin(), hello_world.end(),
                        std::back_inserter(non_vowels), is_vowel);
    print_container(non_vowels, "non-vowels of 'Hello, world': ");
}
