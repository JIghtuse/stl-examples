#include <algorithm>
#include <future>
#include <iostream>
#include <string>
#include <vector>
#include "color.h"

std::vector<std::string> extract_servers(int argc, char* argv[])
{
    std::vector<std::string> servers;
    for (auto i = 1; i < argc; ++i)
        servers.push_back(argv[i]);
    return servers;
}

std::vector<std::future<bool> > get_ping_results(std::vector<std::string>& servers)
{
    std::vector<std::future<bool> > pings;
    pings.reserve(servers.size());

    for (auto& server : servers) {
        auto pinger = [server]() {
            auto command = std::string{ "ping -c1 " } + server + ">/dev/null 2>/dev/null";
            return !system(command.c_str());
        };
        pings.push_back(std::async(std::launch::async, pinger));
    }
    return pings;
}

// Tries to ping servers passed as args and reports result
int main(int argc, char* argv[])
{
    auto usage = [argv](std::ostream& out) {
        out << "usage: " << argv[0] << " server1 [server2 .. ]\n";
    };
    if (argc < 2) {
        usage(std::cerr);
        return 1;
    }
    auto servers = extract_servers(argc, argv);
    if (std::find(servers.begin(), servers.end(), "google.com") != servers.end())
        std::cout << "We will ping google.com!\n";

    auto pings = get_ping_results(servers);
    auto available = [](auto& future) { return future.get(); };
    if (std::find_if(pings.begin(), pings.end(), available) != pings.end())
        std::cout << Color::Green << "Some servers available\n" << Color::None;
    else
        std::cout << Color::Red << "No available servers\n" << Color::None;
}
