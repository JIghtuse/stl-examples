#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <print_container.h>

struct Component {
    bool broken;
};
std::ostream& operator<<(std::ostream& out, const Component& component)
{
    return out << (component.broken ? '-' : '+');
}

struct Machine {
    std::string name;
    std::vector<Component> components;
};
std::ostream& operator<<(std::ostream& out, const Machine& machine)
{
    out << "Machine [" << std::setw(8) << machine.name << "] components: ";
    for (const auto& component : machine.components) {
        out << component;
    }
    return out;
}

int main()
{
    std::vector<Machine> machines{
        { "alpha",   { { false }, { false }, { false }, { false } } },
        { "beta",    { { false }, { false }, { false }, { false } } },
        { "gamma",   { { false }, { true  }, { false }, { false } } },
        { "delta",   { { false }, { false }, { true  }, { false } } },
        { "epsilon", { { true  }, { false }, { true  }, { false } } },
        { "zeta",    { { false }, { false }, { false }, { false } } },
    };

    auto broken = [](auto& component) {
        return component.broken;
    };

    print_container(machines, "Initially:\n", "\n");

    const auto broken_machine = "gamma";
    const auto it = std::find_if(machines.begin(), machines.end(), [broken_machine](auto& machine) {
        return machine.name == broken_machine;
    });
    if (it != machines.end()) {
        auto& components = it->components;
        std::replace_if(components.begin(), components.end(), broken, Component{ false });
    }
    print_container(machines, "After std::replace_if on 'gamma':\n", "\n");

    auto has_broken_component = [broken](auto& machine) {
        const auto& components = machine.components;
        return std::any_of(components.begin(), components.end(), broken);
    };
    std::replace_if(machines.begin(), machines.end(), has_broken_component,
        Machine{ "shiny", { { false }, { false }, { false }, { false } } });
    print_container(machines, "After 'global' std::replace_if:\n", "\n");
}
