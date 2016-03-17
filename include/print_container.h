#pragma once

#include <algorithm>
#include <iostream>
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

template <typename Container, typename Predicate>
void print_container_if(const Container& c, Predicate p,
                        const char* header="", const char* delim = " ",
                        std::ostream& out = std::cout)
{
    out << header;
    using ValueType = typename Container::value_type;
    std::copy_if(c.begin(), c.end(), std::ostream_iterator<ValueType>(out, delim), p);
    out << std::endl;
}

template <typename Container, typename Predicate>
void print_container_if_not(const Container& c, Predicate p,
                        const char* header="", const char* delim = " ",
                        std::ostream& out = std::cout)
{
    out << header;
    using ValueType = typename Container::value_type;
    std::remove_copy_if(c.begin(), c.end(), std::ostream_iterator<ValueType>(out, delim), p);
    out << std::endl;
}
