#include <print_container.h>
#include <cassert>
#include <algorithm>
#include <vector>

template <typename ForwardIt,
          typename Compare>
void insertion_sort(ForwardIt begin, ForwardIt end, Compare comp)
{
    for (auto it = begin; it != end; ++it) {
        auto first_larger_it = std::upper_bound(begin, it, *it, comp);
        std::rotate(first_larger_it, it, it + 1);
    }
}

template <typename Container,
          typename Value=typename Container::value_type,
          typename Compare=std::less<Value>>
void insertion_sort(Container& container, Compare comp=Compare{})
{
    insertion_sort(container.begin(), container.end(), comp);
    assert(std::is_sorted(container.begin(), container.end(), comp));
}

int main()
{
    std::vector<int> empty;
    std::vector<int> one{ 1 };
    std::vector<int> few{ 1, 3, 2 };
    std::vector<int> many{ 3, 2, 4, 1, 5 };

    auto print_sort_print = [](auto& container) {
        print_container(container, "initially:            ");
        insertion_sort(container);
        print_container(container, "after insertion_sort: ");
    };

    print_sort_print(empty);
    print_sort_print(one);
    print_sort_print(few);
    print_sort_print(many);
}
