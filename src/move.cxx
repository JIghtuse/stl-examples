#include <algorithm>
#include <iostream>
#include <vector>

class Moveable {
public:
    Moveable(int i_)
        : i{ i_ }
    {
    }
    Moveable(const Moveable&) = delete;
    Moveable& operator=(const Moveable&) = delete;
    Moveable(Moveable&& rhs)
        : i{ rhs.i }
    {
        rhs.i = 0;
    }
    Moveable& operator=(Moveable&& rhs)
    {
        this->i = rhs.i;
        rhs.i = 0;
        return *this;
    }
    int value() const { return i; }
private:
    int i;
};

int main()
{
    const auto n = 7;
    std::vector<Moveable> v;
    for (auto i = 1; i <= n; ++i)
        v.emplace_back(i);
    const auto diff = 3;
    for (auto i = n + 1; i <= n + diff; ++i)
        v.emplace_back(0);

    std::vector<int> v2(n + diff);

    auto print = [](const auto& c) {
        for (auto& i : c) {
            std::cout << i.value() << ' ';
        }
        std::cout << std::endl;
    };

    std::cout << "initially\n";
    std::cout << "v: ";
    print(v);

    // Shift all elements to the right
    std::move_backward(v.begin(), v.end() - diff, v.end());
    std::cout << "after std::move_backward\n";
    std::cout << "v: ";
    print(v);

    // Shift all elements back to the left
    std::move(v.begin() + diff, v.end(), v.begin());
    std::cout << "after std::move\n";
    std::cout << "v: ";
    print(v);
}
