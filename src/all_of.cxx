#include <algorithm>
#include <array>
#include <experimental/optional>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>

using std::experimental::optional;

struct config {
    optional<int> version;
    std::map<std::string, optional<std::string> > parameters{
        { "os", optional<std::string>{} },
        { "arch", optional<std::string>{} },
    };
};

optional<std::string> get_os()
{
    std::regex pretty_name{ "PRETTY_NAME=\"(.*)\"" };
    std::ifstream os_release{ "/etc/os-release" };
    if (!os_release)
        return optional<std::string>{};
    for (std::string line; std::getline(os_release, line);) {
        std::smatch sm;
        std::regex_match(line, sm, pretty_name);
        if (sm.size() > 1)
            return std::string{ sm[1] };
    }

    return optional<std::string>{};
}

optional<std::string> get_arch()
{
    return std::string{ "x86_64" };
}

config get_config()
{
    return config{
        1,
        {
            { "os", get_os() },
            { "arch", get_arch() },
        }
    };
}

// Using std::all_of
// Based on example from http://www.cplusplus.com/reference/algorithm/all_of/
int main()
{
    std::array<int, 8> foo{ { 3, 5, 7, 11, 13, 17, 19, 23 } };
    if (std::all_of(foo.begin(), foo.end(), [](int i) { return i % 2; }))
        std::cout << "All the elements are odd numbers.\n";

    std::array<int, 0> bar{};
    if (std::all_of(bar.begin(), bar.end(), [](int i) { return i % 2; }))
        std::cout << "All the (zero) elements are odd numbers.\n";
    if (std::all_of(bar.begin(), bar.end(), [](int i) { return i % 2 == 0; }))
        std::cout << "All the (zero) elements are even numbers.\n";

    auto cfg = get_config();
    if (std::all_of(cfg.parameters.begin(), cfg.parameters.end(),
            [](auto param) { return param.second; })) {
        std::cout << "All config parameters are initialized\n";
    }
}
