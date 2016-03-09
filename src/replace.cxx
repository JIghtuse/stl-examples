#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <print_container.h>

template<typename Container, typename ValueType>
void replace_in_container(Container& c, const ValueType& old_value, const ValueType& new_value)
{
    std::replace(c.begin(), c.end(), old_value, new_value);
}

// Stupid CSV->TSV converter. Will break on any non-trivial file.
int main(int argc, char* argv[])
{
    auto usage = [argv](const char* warning=nullptr, std::ostream& out=std::cerr) {
        if (warning) {
            out << warning << '\n';
        }
        out << "usage: " << argv[0] << " input.csv output.tsv\n";
    };
    if (argc < 3) {
        usage();
        return 1;
    }
    std::ifstream in{argv[1]};
    if (!in) {
        usage("cannot open input file");
        return 1;
    }
    std::ofstream out{argv[2]};
    if (!out) {
        usage("cannot open output file");
        return 1;
    }
    for (std::string s; std::getline(in, s);) {
        replace_in_container(s, ',', '\t');
        out << s << '\n';
    }
}
