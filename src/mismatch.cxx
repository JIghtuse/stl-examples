#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "color.h"

// Stupid 'diff'. Prints changes inline.
int main(int argc, char* argv[])
{
    auto usage = [argv](std::ostream& out) {
        out << "usage: " << argv[0] << " file1 file2\n";
    };
    if (argc != 3) {
        usage(std::cerr);
        return 1;
    }

    std::ifstream a{ argv[1] };
    std::ifstream b{ argv[2] };
    if (!a || !b) {
        usage(std::cerr);
        return 1;
    }

    for (auto lineno = 1; a || b; ++lineno) {
        auto astr = std::string{};
        if (a)
            std::getline(a, astr);
        auto bstr = std::string{};
        if (b)
            std::getline(b, bstr);

        auto [astart, bstart] = std::mismatch(astr.begin(), astr.end(),
                                         bstr.begin(), bstr.end());
        auto aend = std::string(astart, astr.end());
        auto bend = std::string(bstart, bstr.end());
        if (!aend.empty() || !bend.empty()) {
            std::cout << std::setw(6) << lineno << ' '
                      << std::string(astr.begin(), astart)
                      << Color::Red << aend << Color::None
                      << Color::Green << bend << Color::None
                      << std::endl;
        }
    }
}
