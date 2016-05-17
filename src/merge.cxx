#include <print_container.h>
#include <cassert>
#include <algorithm>
#include <functional>
#include <vector>

template<typename ForwardIt,
         typename Compare>
void merge_sort(ForwardIt begin, ForwardIt end,
                ForwardIt aux_begin, ForwardIt aux_end,
                Compare comp)
{
    auto dst = std::distance(begin, end);
    if (dst < 2) {
        return;
    }
    std::copy(begin, end, aux_begin);
    auto half = dst / 2;

    merge_sort(aux_begin, aux_begin + half,
               begin, begin + half, comp);
    merge_sort(aux_begin + half, aux_end,
               begin + half, end, comp);

    assert(std::is_sorted(aux_begin, aux_begin + half, comp));
    assert(std::is_sorted(aux_begin + half, aux_end, comp));

    std::merge(aux_begin, aux_begin + half,
               aux_begin + half, aux_end,
               begin, comp);
}

template<typename Container,
         typename Value=typename Container::value_type,
         typename Compare=std::less<Value>>
void merge_sort(Container& container, Compare comp=Compare{})
{
    auto aux = container;

    merge_sort(container.begin(), container.end(), aux.begin(), aux.end(), comp);
    assert(std::is_sorted(container.begin(), container.end(), comp));
}

int main()
{
    auto print_sort_print = [](auto& container) {
        print_container(container, "initially:                ");
        merge_sort(container);
        print_container(container, "after merge_sort:         ");
    };

    auto empty = std::string{};
    print_sort_print(empty);
    auto word = std::string{"banana"};
    print_sort_print(word);
    merge_sort(word, [](char a, char b) { return b < a; });
    print_container(word, "after reverse merge_sort: ");

    print_sort_print(word);
    auto v_one = std::vector<int>{1};
    print_sort_print(v_one);
    auto v_even = std::vector<int>{1, 3, 2, 5};
    print_sort_print(v_even);
    auto v_odd = std::vector<int>{3, 2, 5, 1, 4};
    print_sort_print(v_odd);
}
