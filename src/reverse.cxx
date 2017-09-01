#include <print_container.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void print_file(const std::string& fname, bool reversed)
{
    auto in{ std::ifstream{ fname } };

    if (!in) {
        std::cerr << "Cannot print file " << fname << '\n';
        return;
    }

    auto lines{ std::vector<std::string>{} };
    for (std::string line; std::getline(in, line);) {
        lines.push_back(line);
    }

    if (reversed) {
        std::reverse(lines.begin(), lines.end());
    }

    print_container(lines, "", "\n");
}

// "cat"-like utility
int main(int argc, char* argv[])
{
    const char* program_name = argv[0];

    auto usage = [program_name](std::ostream& out = std::cerr) {
        out << "usage: " << program_name << " [-r] filename.txt\n";
    };

    if (argc < 2) {
        usage();
        return 1;
    }

    auto reversed{ false };
    std::string filename;

    if (argc == 3) {
        if (std::string{ argv[1] } == std::string{ "-r" }) {
            reversed = true;
            filename = argv[2];
        }
        else {
            usage();
            return 1;
        }
    }
    else if (argc == 2) {
        filename = argv[1];
    }
    else {
        usage();
        return 1;
    }

    print_file(filename, reversed);
}
