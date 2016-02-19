#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    auto print_element = [](auto& e) {
        std::cout << e << ' ';
    };

    auto print_container = [print_element](const auto& container) {
        std::for_each(container.begin(), container.end(), print_element);
        std::cout << std::endl;
    };
    auto print_unique = [print_element](const auto& container) {
        for (auto pos = container.begin(); pos != container.end();) {
            // Print all elements up to first in repeating group (including)
            auto adj_pos = std::adjacent_find(pos, container.end());
            std::for_each(pos, std::min(container.end(), 1 + adj_pos), print_element);

            // Jump to the next group
            auto next_non_equal = std::find_if_not(adj_pos, container.end(),
                [adj_pos](int i) { return i == *adj_pos; });
            std::advance(pos, std::distance(pos, next_non_equal));
        }
        std::cout << std::endl;
    };

    std::vector<std::vector<int> > vs{
        { 1, 2, 2, 3, 4, 4, 5, 2, 2, 2, 0, 9, 9 },
        { 1, 2, 2, 3, 4, 4, 5, 2, 2, 2, 0, 9 },
        { 1, 1, 2, 3, 4, 4, 5, 2, 2, 2, 0, 9 },
        { 1, 1, 1, 1 },
        {},
    };
    for (const auto& v : vs) {
        std::cout << "v elements:        ";
        print_container(v);
        std::cout << "v unique elements: ";
        print_unique(v);
    }
}
