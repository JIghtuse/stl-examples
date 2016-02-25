#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

template <typename Container>
void print_container(const Container& c, std::ostream& out = std::cout, const char* delim = " ")
{
    using ValueType = typename Container::value_type;
    std::copy(c.begin(), c.end(), std::ostream_iterator<ValueType>(out, delim));
    out << std::endl;
}

int main()
{
    std::list<int> values{ 1, 2, 3, 4, 5 };
    std::vector<int> v;

    std::cout << "List contents: ";
    print_container(values);

    // We are sure list have at least 3 values,
    // and we don't want to calculate list::end. Solution: use copy_n
    std::copy_n(values.begin(), 3, std::back_inserter(v));

    std::cout << "Vector contents (first 3 values of a list): ";
    print_container(v);

    std::cout << "Half of a vector: ";
    // We need half of a vector
    std::copy_n(v.begin(), v.size() / 2, std::ostream_iterator<int>(std::cout));
    std::cout << std::endl;
}
