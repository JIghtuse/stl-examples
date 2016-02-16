#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <experimental/optional>
#include <experimental/string_view>

using std::experimental::optional;
using std::experimental::string_view;

struct Header {
    char bytes[64];
};

std::istream& operator>>(std::istream& in, Header& header)
{
    return in >> header.bytes;
}

optional<Header> read_header(const char* fname)
{
    auto result = optional<Header>{};
    std::ifstream binary(fname, std::ios::binary);
    if (binary) {
        Header header;
        if (binary >> header)
            result = header;
    }
    return result;
}

const char kElfMagic[4]{ 0x7f, 'E', 'L', 'F' };

// is_palindrome() taken from http://en.cppreference.com/w/cpp/algorithm/equal
bool is_palindrome(string_view sv)
{
    return std::equal(sv.begin(), sv.begin() + sv.size() / 2, sv.rbegin());
}

int main(int, char* argv[])
{
    auto binary_name = argv[0];
    auto header = read_header(binary_name);
    if (!header) {
        std::cerr << "Cannot read file " << binary_name << std::endl;
        return 1;
    }
    if (std::equal(kElfMagic, kElfMagic + sizeof(kElfMagic), header->bytes)) {
        std::cout << binary_name << " is ELF file\n";
    }

    auto words = std::vector<const char*>{
        "radar",
        "hello",
        "",
    };
    for (auto word : words) {
        std::cout << '"' << word << '"';
        if (is_palindrome(word)) {
            std::cout << " is palindrome\n";
        }
        else {
            std::cout << " not a palindrome\n";
        }
    }
}
