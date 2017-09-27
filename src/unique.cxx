#include <algorithm>
#include <experimental/optional>
#include <experimental/string_view>
#include <fstream>
#include <regex>
#include <string>
#include <print_container.h>

using std::experimental::nullopt;
using std::experimental::optional;
using std::experimental::string_view;

using Link = std::string;

namespace {
    const char kHTTPPrefix[] = "http://";
} // namespace

inline bool starts_with(string_view s, string_view prefix)
{
    return std::equal(std::begin(prefix), std::end(prefix), s.begin());
}

optional<std::vector<Link>> get_links(const std::string& fname, const std::string& hostname)
{
    auto in{std::ifstream{fname}};
    if (!in) {
        return nullopt;
    }

    std::regex re_link{R"#(href\s*=\s*['"]([^'"]*)")#", std::regex_constants::icase};

    auto links{std::vector<Link>{}};
    for (std::string line; std::getline(in, line);) {
        auto begin = std::sregex_iterator(line.begin(), line.end(), re_link);

        for (auto it = begin; it != std::sregex_iterator{}; ++it) {
            std::smatch match = *it;
            auto link = std::string{match[1]};
            if (!starts_with(link, {kHTTPPrefix, sizeof(kHTTPPrefix)})) {
                link = kHTTPPrefix + hostname + link;
            }
            links.push_back(link);
        }
    }

    // Remove repeating links
    std::sort(links.begin(), links.end());
    auto new_end = std::unique(links.begin(), links.end());
    links.erase(new_end, links.end());

    return links;
}

// Reads html file and tries to extract all unique links from it
int main()
{
    const auto input_file{std::string{"index.html"}};

    if (auto links = get_links(input_file, "en.cppreference.com"); links) {
        print_container(*links, "All links:\n", "\n");
    } else {
        std::cerr << "Cannot open file " << input_file << std::endl;
    }
}
