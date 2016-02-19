#include <array>
#include <algorithm>
#include <iostream>
#include <string>

int main()
{
    auto lorem = std::string {
R"(Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod
tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At
vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren,
no sea takimata sanctus est Lorem ipsum dolor sit amet.)"};

    std::array<char, 5> vowels{{'a', 'e', 'i', 'o', 'u'}};
    auto vowel_pos = std::find_first_of(lorem.begin(), lorem.end(),
            vowels.begin(), vowels.end());

    std::cout << lorem << std::endl << std::endl;
    if (vowel_pos != lorem.end())
        std::cout << "First vowel: '" << *vowel_pos
            << "' at position " << 1 + std::distance(lorem.begin(), vowel_pos)
            << std::endl;
    else
        std::cout << "No vowels found\n";

    std::array<char, 0> empty{ {} };
    auto empty_pos = std::find_first_of(lorem.begin(), lorem.end(),
            empty.begin(), empty.end());
    if (empty_pos != lorem.end())
        std::cout << "empty found\n";
    else
        std::cout << "empty not found\n";
}
