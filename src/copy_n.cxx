#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <print_container.h>

int main()
{
    std::list<int> values{ 1, 2, 3, 4, 5 };
    std::vector<int> v;

    print_container(values, "list contents: ");

    // We are sure list have at least 3 values,
    // and we don't want to calculate list::end. Solution: use copy_n
    std::copy_n(values.begin(), 3, std::back_inserter(v));

    print_container(v, "vector contents (first 3 values of a list): ");

    std::cout << "Half of a vector: ";
    // We need half of a vector
    std::copy_n(v.begin(), v.size() / 2, std::ostream_iterator<int>(std::cout));
    std::cout << std::endl;
}
