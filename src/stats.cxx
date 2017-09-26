#include <print_container.h>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>

double mean(const std::vector<int>& data)
{
    assert(!data.empty());
    return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

double variance(const std::vector<int>& data, double mean_value)
{
    auto sum = std::accumulate(data.begin(), data.end(), 0.0, [mean_value](double& acc, int x) {
        return acc += (x - mean_value) * (x - mean_value);
    });
    return sum / data.size();
}

double standard_deviation(const std::vector<int>& data, double mean_value)
{
    return std::sqrt(variance(data, mean_value));
}

int main()
{
    const auto numbers = std::vector<int>{
         1,  2,  3,  4,  5,  6,  7,  8,  9,
        -1, -2, -3, -4, -5, -6, -7, -8, -9,
         0
    };
    print_container(numbers, "v: ");

    const auto [min, max] = std::minmax_element(cbegin(numbers), cend(numbers));
    std::cout << "minimum element:    " << *min << std::endl;
    std::cout << "maximum element:    " << *max << std::endl;

    auto mean_value = mean(numbers);
    std::cout << "mean value:         " << mean_value << std::endl;
    std::cout << "variance:           " << variance(numbers, mean_value) << std::endl;
    std::cout << "standard deviation: " << standard_deviation(numbers, mean_value) << std::endl;
}
