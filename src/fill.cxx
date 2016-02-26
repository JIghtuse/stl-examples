#include <array>
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    auto print = [](const auto& c){
        for (auto& e : c)
            std::cout << e << ' ';
        std::cout << std::endl;
    };

    auto fill_container = [](auto& c, auto value){
        std::fill(std::begin(c), std::end(c), value);
    };

    std::array<int, 5> a;
    fill_container(a, 42);
    print(a);

    int raw_array[5];
    fill_container(raw_array, 11);
    print(raw_array);

    std::vector<int> v(5);
    fill_container(v, 3);
    print(v);

    // Actually, for vector this makes more sense
    std::vector<int> v2(5, 3);
    print(v2);
}
