#include <algorithm>
#include <array>
#include <iostream>

struct server {
    bool available;
};

int main()
{
    std::array<server, 3> servers{ {
        server{ false },
        server{ true },
        server{ false },
    } };
    std::cout << std::boolalpha;

    auto available = [](auto& server) { return server.available; };
    std::cout << "Servers are not available: "
              << std::none_of(servers.begin(), servers.end(), available)
              << std::endl;

    std::array<std::string, 3> appliances{ {
        "fork",
        "knife",
        "grater",
    } };
    auto is_spoon = [](auto& appliance) { return "spoon" == appliance; };
    std::cout << "There is no spoon: "
              << std::none_of(appliances.begin(), appliances.end(), is_spoon)
              << std::endl;

    std::array<std::string, 0> empty;
    std::cout << "There is no spoon among (zero) elements: "
              << std::none_of(empty.begin(), empty.end(), is_spoon)
              << std::endl;
}
