#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

// Prints input one word per line, replacing word "one" with "zero"
int main()
{
    std::replace_copy(std::istream_iterator<std::string>{ std::cin },
                      std::istream_iterator<std::string>{},
                      std::ostream_iterator<std::string>{ std::cout, "\n"},
                      std::string{ "one" }, std::string{ "zero" });
}
