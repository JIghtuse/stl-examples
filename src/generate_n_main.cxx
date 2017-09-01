#include <print_container.h>
#include <generate_n.h>
#include <fstream>
#include <iostream>

// "head"-like utility
int main(int argc, char* argv[])
{
    const auto nlines = size_t{ 10 };

    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " filename.txt\n";
        return 1;
    }

    std::ifstream in{ argv[1] };
    auto lines = get_n_lines(in, nlines);

    print_container(lines, "", "\n");
}
