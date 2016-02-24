#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

enum class TestResult {
    Fail,
    Skip,
    Success,
};

using TestHistory = std::vector<TestResult>;

struct Test {
    std::string name;
    TestHistory results;
};

using Tests = std::vector<Test>;

bool has_n_failing_tests(const TestHistory& history, size_t n)
{
    return std::search_n(history.begin(), history.end(), n, TestResult::Fail) != history.end();
}

bool n_last_tests_failed(const TestHistory& history, size_t n)
{
    auto it = std::search_n(history.begin(), history.end(), n, TestResult::Fail);
    return std::distance(it, history.end()) == static_cast<int>(n);
}

bool has_n_non_successful_results(const TestHistory& history, size_t n)
{
    return std::search_n(history.begin(), history.end(), n, TestResult::Fail,
               [](const TestResult& hist_result, const TestResult&) {
                   return hist_result != TestResult::Success;
               })
        != history.end();
}

int main()
{
    Tests tests{
        { "test_init", { TestResult::Success,
                           TestResult::Success,
                           TestResult::Success,
                           TestResult::Success,
                           TestResult::Success } },
        { "test_run", { TestResult::Success,
                          TestResult::Success,
                          TestResult::Fail,
                          TestResult::Fail,
                          TestResult::Fail } },
        { "test_connect", { TestResult::Success,
                              TestResult::Fail,
                              TestResult::Skip,
                              TestResult::Fail,
                              TestResult::Success } },
        { "test_cleanup", { TestResult::Success,
                              TestResult::Success,
                              TestResult::Success,
                              TestResult::Success,
                              TestResult::Success } },
    };

    for (auto& test : tests) {
        if (has_n_failing_tests(test.results, 3))
            std::cout << "Test " << test.name << " has 3 consecutive failing invocations\n";
    }

    for (auto& test : tests) {
        if (n_last_tests_failed(test.results, 3))
            std::cout << "Test " << test.name << " failed last 3 times\n";
    }

    for (auto& test : tests) {
        if (has_n_non_successful_results(test.results, 3))
            std::cout << "Test " << test.name << " has been skipped or failed 3 times consecutively\n";
    }
}
