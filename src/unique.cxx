#include <algorithm>
#include <experimental/optional>
#include <fstream>
#include <regex>
#include <string>
#include <print_container.h>

using std::experimental::nullopt;
using std::experimental::optional;

using Link = std::string;

const std::string kHTTPPrefix{"http://"};

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
            if (!std::equal(kHTTPPrefix.begin(), kHTTPPrefix.end(), link.begin())) {
                link = kHTTPPrefix + hostname + link;
            }
            links.push_back(link);
        }
    }

    // Remove repeating links
    std::sort(links.begin(), links.end());
    auto end = std::unique(links.begin(), links.end());
    links.resize(std::distance(links.begin(), end));

    return links;
}

// Reads html file and tries to extract all unique links from it
int main()
{
    const auto input_file{std::string{"index.html"}};

    auto links = get_links(input_file, "en.cppreference.com");

    if (links) {
        print_container(*links, "All links:\n", "\n");
    } else {
        std::cerr << "Cannot open file " << input_file << std::endl;
    }
}
