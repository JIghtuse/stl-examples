#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

// Prints input one word per line, replacing word "one" with "zero"
int main()
{
    const auto forbidden_words{ std::vector<std::string>{
        "dog",
        "broccoli",
    } };

    auto should_be_censored = [&forbidden_words](const std::string& word) {
        return std::find(forbidden_words.begin(), forbidden_words.end(), word) != forbidden_words.end();
    };

    std::replace_copy_if(std::istream_iterator<std::string>{ std::cin },
                         std::istream_iterator<std::string>{},
                         std::ostream_iterator<std::string>{ std::cout, "\n" },
                         should_be_censored, std::string{ "NONE" });
}
