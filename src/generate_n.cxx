#include <algorithm>
#include <iostream>
#include <generate_n.h>

using std::experimental::optional;
using std::experimental::nullopt;

// Tries to read @n lines from input stream @in.
// Returns vector with @n strings of input stream on success.
// Returns vector with less (possibly 0) strings of input stream if @in goes to bad/fail state
std::vector<std::string> get_n_lines(std::istream& in, size_t n)
{
    auto result = std::vector<std::string>{};
    auto read_line = [&in]() {
        if (!in) {
            throw stream_error{};
        }
        std::string s;
        while (in && s.empty()) {
            std::getline(in, s);
        }
        if (in.bad() || in.fail()) { // eof is fine here, it can be the last line
            throw stream_error{};
        }
        return s;
    };
    try {
        std::generate_n(std::back_inserter(result), n, read_line);
    } catch (stream_error&) {
        return result;
    }
    return result;
}

// Pagination: return @pagenum page of results vector, @n results per page
// Returns @n results from page @pagenum if there are enough results
// Returns less then @n values or std::experimental::nullopt, if there are not enough results
optional<Results> get_page(const Results& all_results, GroupBy n, PageNum pagenum)
{
    auto last_nonrelevant_idx = n * pagenum;
    if (0 == n || last_nonrelevant_idx >= all_results.size()) {
        return nullopt;
    }
    auto nresults = all_results.size() - last_nonrelevant_idx;
    auto result = Results{};

    struct genResult {
        genResult(const Results& r, size_t start)
            : current{start}
            , m_results{r}
        {}
        const Page& operator()()
        {
            return m_results[current++];
        }
    private:
        size_t current;
        const Results& m_results;
    };
    std::generate_n(std::back_inserter(result), nresults,
                    genResult{all_results, last_nonrelevant_idx + 1});
    return result;
}
