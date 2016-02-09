#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

// http://stackoverflow.com/a/19453043/1145239
struct recursive_directory_range {
    typedef fs::recursive_directory_iterator iterator;
    recursive_directory_range(fs::path p)
        : p_(p)
    {
    }

    iterator begin() { return fs::recursive_directory_iterator{ p_ }; }
    iterator end() { return fs::recursive_directory_iterator{}; }
    fs::path p_;
};

enum class Extension {
    C,
    CXX,
};

using ExtensionDict = std::map<Extension, std::vector<std::string> >;
ExtensionDict extensions{
    { Extension::C, { ".c" } },
    { Extension::CXX, { ".cxx", ".cc", ".cpp" } },
};

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

    struct HasExtension {
        HasExtension(Extension e)
            : exts_{ extensions[e] }
        {
        }
        bool operator()(const fs::path& p)
        {
            auto file_ext = p.extension().string();
            return std::any_of(exts_.begin(), exts_.end(), [file_ext](auto& ext) {
                return file_ext == ext;
            });
        }
        std::vector<std::string> exts_;
    };
    auto search_path = fs::path(".");
    auto it = recursive_directory_range{ search_path };
    if (std::any_of(it.begin(), it.end(), [](auto& path) {
            auto p = fs::path{ path };
            return fs::is_regular_file(p) && HasExtension{ Extension::CXX }(p);
        })) {
        std::cout << "Current directory or its subdirectories contains C++ source code files\n";
    }
    else {
        std::cout << "C++ source code files not found\n";
    }
}
