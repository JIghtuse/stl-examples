#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// TODO: more appropriate example. Now it more fits for std::search_n

using TestHistory = std::vector<bool>;
using TestResults = std::map<std::string, TestHistory>;

bool has_n_failing_tests(const TestHistory& history, size_t n)
{
    TestHistory n_failing(n, false);
    return std::search(history.begin(), history.end(), n_failing.begin(), n_failing.end()) != history.end();
}

bool n_last_tests_failed(const TestHistory& history, size_t n)
{
    TestHistory n_failing(n, false);
    auto it = std::search(history.begin(), history.end(), n_failing.begin(), n_failing.end());
    return std::distance(it, history.end()) == static_cast<int>(n);
}

// Stolen from http://en.cppreference.com/w/cpp/algorithm/search
template <typename Container>
bool contains(const Container& cont, const std::string& s)
{
    return std::search(cont.begin(), cont.end(), s.begin(), s.end()) != cont.end();
}

int main()
{
    TestResults test_results{
        { "test_init", TestHistory{ true, true, true, true, true } },
        { "test_run", TestHistory{ true, true, false, false, false } },
        { "test_connect", TestHistory{ true, false, false, false, true } },
        { "test_cleanup", TestHistory{ true, true, true, true, true } },
    };

    for (auto& test : test_results) {
        if (has_n_failing_tests(test.second, 3))
            std::cout << "Test " << test.first << " has 3 consecutive failing invocations\n";
    }

    for (auto& test : test_results) {
        if (n_last_tests_failed(test.second, 3))
            std::cout << "Test " << test.first << " failed last 3 times\n";
    }

    const std::string quote = "There is no spoon";
    std::cout << "Quote \"" << quote << "\" contains word \"spoon\": "
              << std::boolalpha << contains(quote, "spoon") << std::endl;
    std::cout << "Quote \"" << quote << "\" contains word \"fork\":  "
              << std::boolalpha << contains(quote, "fork") << std::endl;
}
