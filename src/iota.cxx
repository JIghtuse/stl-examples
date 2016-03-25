#include <numeric>
#include <string>
#include <vector>
#include <print_container.h>

int main()
{
    auto v{ std::vector<int>(10) };
    std::iota(v.begin(), v.end(), 0);
    print_container(v, "v: ");

    auto alphabet{ std::string(26, ' ') };
    std::iota(alphabet.begin(), alphabet.end(), 'a');
    print_container(alphabet, "alphabet: ");
}
