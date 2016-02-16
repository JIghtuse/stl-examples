#include <array>
#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>

int main()
{
    std::array<double, 10> values{
        { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0,
            -1.0 / 0.0, 1.0 / 0.0,
            std::sqrt(-1), NAN },
    };

    std::cout << "Number of nan values: "
              << std::count_if(values.begin(), values.end(), isnan)
              << std::endl;

    std::cout << "Number of infinite values: "
              << std::count_if(values.begin(), values.end(), isinf)
              << std::endl;


    std::string lorem{
R"(Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod
 tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At
 vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren,
 no sea takimata sanctus est Lorem ipsum dolor sit amet.)"
    };

    std::cout << "Number of spaces in 50-words 'Lorem': "
              << std::count(lorem.begin(), lorem.end(), ' ')
              << std::endl;
}
