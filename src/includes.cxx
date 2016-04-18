#include <print_container.h>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>

int main()
{
    auto knownExtensions = std::vector<std::string>{ ".ini",  ".toml", ".txt" };
    auto imageExtensions = std::vector<std::string>{ ".jpg", ".png" };

    print_container(knownExtensions, "known extensions: ");
    print_container(imageExtensions, "image extensions: ");

    bool hasImages = std::includes(knownExtensions.begin(), knownExtensions.end(),
                                   imageExtensions.begin(), imageExtensions.end());
    std::cout << "Do we know about image extensions: "
              << std::boolalpha
              << hasImages
              << std::endl;

    if (!hasImages) {
        auto newKnownExtensions = std::vector<std::string>{};
        std::set_union(knownExtensions.begin(), knownExtensions.end(),
                       imageExtensions.begin(), imageExtensions.end(),
                       std::back_inserter(newKnownExtensions));
        knownExtensions = std::move(newKnownExtensions);
    }

    print_container(knownExtensions, "known extensions: ");
}
