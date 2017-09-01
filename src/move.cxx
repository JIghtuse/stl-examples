#include <print_container.h>
#include <algorithm>
#include <iostream>
#include <vector>

class Moveable {
public:
    explicit Moveable(int i_)
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

std::ostream& operator<<(std::ostream& out, const Moveable& m)
{
    return out << m.value();
}

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

    std::cout << "initially\n";
    print_container(v, "v: ");

    // Shift all elements to the right
    std::move_backward(v.begin(), v.end() - diff, v.end());
    std::cout << "after std::move_backward\n";
    print_container(v, "v: ");

    // Shift all elements back to the left
    std::move(v.begin() + diff, v.end(), v.begin());
    std::cout << "after std::move\n";
    print_container(v, "v: ");
}
