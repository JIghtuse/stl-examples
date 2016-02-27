#include <algorithm>
#include <iostream>

int main()
{
    std::vector<int> v(9);

    auto print_container = [](const auto& c){
        for (auto i : c)
            std::cout << i << ' ';
        std::cout << std::endl;
    };

    std::cout << "initially:                              ";
    print_container(v);

    auto it = std::fill_n(v.begin(), v.size() / 2, -1);

    std::cout << "after std::fill_n half of the elements: ";
    print_container(v);

    std::fill(it, v.end(), 1);

    std::cout << "after std::fill remaining elements:     ";
    print_container(v);
}
