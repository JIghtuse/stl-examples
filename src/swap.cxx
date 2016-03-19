#include <print_container.h>
#include <vector>

int main()
{
    auto v{ std::vector<int>{ 5, 2, 3, 1, 4 } };
    auto empty{ std::vector<int>{} };

    print_container(v, "<vector v>     initially:       ");
    print_container(empty, "<vector empty> initially:       ");
    std::swap(v, empty);
    print_container(v, "<vector v>     after std::swap: ");
    print_container(empty, "<vector empty> after std::swap: ");

    auto a{ 42 };
    auto b{ 13 };
    std::cout << "initially:       a == " << a << ", b == " << b << std::endl;
    std::swap(a, b);
    std::cout << "after std::swap: a == " << a << ", b == " << b << std::endl;
}
