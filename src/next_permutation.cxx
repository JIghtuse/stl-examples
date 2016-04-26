#include <algorithm>
#include <iostream>
#include <string>

int main()
{
    auto s = std::string{"sand"};
    std::cout << "All permutations of '" << s << "':\n";

    auto original = s;

    while (std::prev_permutation(s.begin(), s.end())) {
        std::cout << "\t" << s << std::endl;
    }

    s = original;

    while (std::next_permutation(s.begin(), s.end())) {
        std::cout << "\t" << s << std::endl;
    }
}
