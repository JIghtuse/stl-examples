#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7};
    const auto n = v.size();
    const auto diff = 3;

    v.resize(n + diff);

    auto print = [](const auto& c){
        for (auto i : c) {
            std::cout << i << ' ';
        }
        std::cout << std::endl;
    };

    std::cout << "initially\n";
    std::cout << "v: ";
    print(v);

    // Shift all elements to the right
    std::copy_backward(v.begin(), v.end() - diff, v.end());
    std::cout << "after std::copy_backward\n";
    std::cout << "v: ";
    print(v);

    std::fill_n(v.begin(), diff, 0);
    std::cout << "after std::fill_n\n";
    std::cout << "v: ";
    print(v);

    // Shift all elements back to the left
    std::copy(v.begin() + diff, v.end(), v.begin());
    std::cout << "after std::copy\n";
    std::cout << "v: ";
    print(v);

    std::fill_n(v.end() - diff, diff, 0);
    std::cout << "after std::fill_n\n";
    std::cout << "v: ";
    print(v);
}
