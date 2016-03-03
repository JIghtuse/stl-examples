#pragma once

#include <iterator>

template <typename Container>
void print_container(const Container& c,
                     const char* header="", const char* delim = " ",
                     std::ostream& out = std::cout)
{
    using ValueType = typename Container::value_type;
    out << header;
    std::copy(c.begin(), c.end(), std::ostream_iterator<ValueType>(out, delim));
    out << std::endl;
}

