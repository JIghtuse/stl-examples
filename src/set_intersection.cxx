#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

using PackageGroup = std::vector<std::string>;
using Packages = std::map<std::string, PackageGroup>;

int main()
{
    auto packages{ Packages{
        { "development", { "anjuta", "gnome-builder", "kdevelop", "qtcreator" } },
        { "kde", { "kate", "kdevelop", "konsole", "okular", "qtcreator" } },
        { "gnome", { "anjuta", "gedit", "gnome-builder", "totem" } },
    } };

    std::cout << "Packages for development in KDE:\n";
    std::set_intersection(packages["development"].begin(), packages["development"].end(),
                          packages["kde"].begin(), packages["kde"].end(),
                          std::ostream_iterator<std::string>(std::cout, "\n"));

    std::cout << "Packages for development in GNOME:\n";
    std::set_intersection(packages["development"].begin(), packages["development"].end(),
                          packages["gnome"].begin(), packages["gnome"].end(),
                          std::ostream_iterator<std::string>(std::cout, "\n"));
}
