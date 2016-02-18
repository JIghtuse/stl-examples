#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>
#include <experimental/optional>

using std::experimental::optional;

struct Line {
    Line()
        : data{}
    {
    }
    Line(const std::string& s)
        : data{ s }
    {
    }
    bool matches_pattern(const Line& needle) const
    {
        auto re_search = std::regex(needle.data, std::regex_constants::icase);
        return std::regex_search(this->data, re_search);
    }
    bool operator==(const Line& other) const { return other.data == data; }
    auto begin() { return data.begin(); }
    auto end() { return data.end(); }
    std::string data;
};

using Log = std::vector<Line>;

std::istream& operator>>(std::istream& in, Line& line)
{
    std::getline(in, line.data);
    return in;
}
std::ostream& operator<<(std::ostream& out, const Line& line)
{
    return out << line.data;
}

optional<Log> read_log(const char* fname)
{
    auto result = optional<Log>{};
    std::ifstream in{ fname };
    if (!in)
        return result;

    Log log;
    std::copy(std::istream_iterator<Line>{ in },
        std::istream_iterator<Line>{},
        std::back_inserter(log));

    return log;
}

// Reads "log file" and looks for last line matching error pattern
int main(int argc, char* argv[])
{
    auto usage = [argv](std::ostream& out) {
        out << "usage: " << argv[0] << "/path/to/file.log\n";
    };

    if (argc != 2) {
        usage(std::cerr);
        return 1;
    }

    auto log = read_log(argv[1]);
    if (!log) {
        std::cerr << "Cannot read log from file '" << argv[1] << "'\n";
        return 1;
    }

    auto error_pattern = Log{ Line{ "error" } };
    auto re_error = [](const Line& haystack, const Line& needle) {
        return haystack.matches_pattern(needle);
    };
    auto last_error_pos = std::find_end(log->begin(), log->end(),
        error_pattern.begin(), error_pattern.end(), re_error);
    if (last_error_pos != log->end())
        std::cout << "Last line matching error pattern: "
                  << std::endl
                  << 1 + std::distance(log->begin(), last_error_pos) << ": "
                  << last_error_pos->data
                  << std::endl;
    else
        std::cout << "Error pattern not found\n";
}
