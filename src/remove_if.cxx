#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Processor {
    double MHz;
    size_t ncores;
};
std::ostream& operator<<(std::ostream& out, const Processor& proc)
{
    return out << "cores: " << proc.ncores << "; frequency: " << proc.MHz;
}

struct RAM {
    double gigabytes;
};
std::ostream& operator<<(std::ostream& out, const RAM& memory)
{
    return out << "capacity: " << memory.gigabytes << " GB";
}

struct Computer {
    Processor processor;
    RAM memory;
};

double getPrice(const Computer& computer)
{
    auto price = 0.0;
    if (computer.memory.gigabytes > 32) {
        price += 200;
    }
    else if (computer.memory.gigabytes > 8) {
        price += 150;
    }
    else if (computer.memory.gigabytes > 4) {
        price += 100;
    }
    else {
        price += 50;
    }
    if (computer.processor.ncores > 4 || computer.processor.MHz > 4000.0) {
        price += 999999;
    }
    else if (computer.processor.ncores > 2) {
        price += 150;
    }
    else {
        price += 80;
    }
    return price;
}

std::ostream& operator<<(std::ostream& out, const Computer& computer)
{
    return out << "Computer\n"
               << "\t[Processor]  " << computer.processor << "\n"
               << "\t[RAM      ]  " << computer.memory
               << "\t[Price    ]  " << getPrice(computer);
}

int main()
{
    auto computers = std::vector<Computer>{
        { Processor{ 1644.332, 2 }, RAM{ 8.0 } },
        { Processor{ 3400.0, 4 }, RAM{ 8.0 } },
        { Processor{ 2100.0, 2 }, RAM{ 4.0 } },
        { Processor{ 3400.0, 4 }, RAM{ 32.0 } },
        { Processor{ 2400.0, 4 }, RAM{ 2.0 } },
    };

    auto print_computers = [&computers](const std::string& header) {
        std::cout << header << std::endl;
        for (const auto& computer : computers)
            std::cout << computer << std::endl;
    };

    print_computers("initially: ");

    auto unacceptable = [](const Computer& computer) {
        return computer.processor.ncores < 4
            || computer.memory.gigabytes < 8
            || getPrice(computer) > 250;
    };
    computers.erase(std::remove_if(computers.begin(), computers.end(), unacceptable),
                    computers.end());

    print_computers("after remove_if: ");
}
