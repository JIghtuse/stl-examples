#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using Function = std::vector<int>;

void plot(const Function& data, unsigned width, const std::string& title)
{
    const auto title_padding = (width - title.length()) / 2;
    std::cout << "   "
              << std::string(title_padding, ' ')
              << title
              << std::string(title_padding, ' ')
              << '\n';
    std::cout << "  +" << std::string(width, '-') << '\n';

    const auto max = *std::max_element(data.begin(), data.end());
    const auto scaling_factor = width / (double)max;

    for (auto i = 0u; i < data.size(); ++i) {
        std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                  << i << '|' << std::string(scaling_factor * data[i], '*')
                  << '\n';
    }
    std::cout << '\n';
}

// Plots empirical functions for normal distribution
// Paritally based on http://en.cppreference.com/w/cpp/numeric/random/normal_distribution
int main()
{
    std::random_device rd;
    std::mt19937 gen{ rd() };
    std::normal_distribution<> d(15, 3);

    const auto nsamples = 100000;
    Function histogram(30);
    for (auto i = 0; i < nsamples; ++i) {
        ++histogram[std::round(d(gen))];
    }

    plot(histogram, 40, "Empirical probability density function");

    Function distribution(30);
    std::partial_sum(histogram.begin(), histogram.end(), distribution.begin());

    plot(distribution, 40, "Empirical distribution function");
}
