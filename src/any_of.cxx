#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

enum class Extension {
    C,
    CXX,
};

using ExtensionDict = std::map<Extension, std::vector<std::string> >;

int main()
{
    std::array<int, 5> values{ { 1, 2, 3, 4, 5 } };
    std::cout << "At least one number is even: "
              << std::any_of(values.begin(), values.end(), [](int i) { return i % 2 == 0; }) << std::endl;

    std::array<bool, 0> bar{};
    if (std::any_of(bar.begin(), bar.end(), [](bool b) { return b; }))
        std::cout << "There is no 'true' in all (zero) elements\n";
    if (std::any_of(bar.begin(), bar.end(), [](bool b) { return !b; }))
        std::cout << "There is no 'false' in all (zero) elements\n";

    ExtensionDict extensions{
        { Extension::C, { ".c" } },
        { Extension::CXX, { ".cxx", ".cc", ".cpp" } },
    };

    struct HasExtension {
        HasExtension(const ExtensionDict& exts, Extension e)
            : exts_{ exts.at(e) }
        {
        }
        bool operator()(const fs::path& p)
        {
            return std::any_of(exts_.begin(), exts_.end(), [p](auto& ext) {
                return fs::is_regular_file(p) && p.extension().string() == ext;
            });
        }
        std::vector<std::string> exts_;
    };
    auto is_cxx_file = HasExtension{ extensions, Extension::CXX };
    if (std::any_of(fs::recursive_directory_iterator{ fs::path(".") },
                    fs::recursive_directory_iterator{},
                    is_cxx_file)) {
        std::cout << "Current directory or its subdirectories contains C++ source code files\n";
    }
    else {
        std::cout << "C++ source code files not found\n";
    }
}
