#include <algorithm>
#include <iostream>
#include <generate_n.h>

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
