#include <charconv>
#include <iostream>
#include <limits>
#include <optional>
#include <string>

struct SomeId
{
    unsigned value;
};

std::ostream& operator<<(std::ostream& out, SomeId some_id)
{
    return out << some_id.value;
}

std::optional<SomeId> FromString(const std::string & s)
{
    SomeId id;

    if (auto [p, ec] = std::from_chars(s.data(), s.data() + s.length(), id.value); std::errc{} == ec) {
        return id;
    } else {
        const auto error_message = std::error_condition{ec}.message();
        std::cerr << "Failed to parse id from: " << s << ": " << error_message << '\n';
        return std::nullopt;
    }
}

std::string ToString(SomeId some_id)
{
    std::string s(std::numeric_limits<decltype(SomeId::value)>().digits10, 0);
    std::to_chars(s.data(), s.data() + s.length(), some_id.value);
    return s;
}

int main()
{
    for (std::string s : {"123456789", "123456789012345", "abcdef"}) {
        if (auto id = FromString(s)) {
            std::cout << "Read id: " << *id << '\n';
        }
    }

    for (auto n : {0l, 12345l, 123456789012345l}) {
        std::string s(10, 0);
        if (auto [p, ec] = std::to_chars(s.data(), s.data() + s.length(), n); std::errc{} == ec) {
            std::cout << "Id as a string: '" << s << "'\n";
        } else {
            const auto error_message = std::error_condition{ec}.message();
            std::cerr << "Failed to convert number: " << n << " into string : " << error_message << '\n';
        }
    }
}
