#include <catch/catch.hpp>
#include <generate_n.h>

TEST_CASE( "Extracts n lines from istream if there are enough", "[get_n_lines]" ) {
    std::istringstream iss{R"(a
b
c
d
e
f
g)"};
    auto zero = get_n_lines(iss, 0);
    REQUIRE(0 == zero.size());

    auto one = get_n_lines(iss, 1);
    REQUIRE(1 == one.size());
    REQUIRE("a" == one[0]);

    auto multiple = get_n_lines(iss, 3);
    REQUIRE(3 == multiple.size());
    REQUIRE("b" == multiple[0]);
    REQUIRE("c" == multiple[1]);
    REQUIRE("d" == multiple[2]);
}

TEST_CASE( "Extracts less then n lines if istream ends early", "[get_n_lines]" ) {
    std::istringstream iss{R"(a
b
c)"};

    auto too_many = get_n_lines(iss, 10);
    REQUIRE(3 == too_many.size());
    REQUIRE("a" == too_many[0]);
    REQUIRE("b" == too_many[1]);
    REQUIRE("c" == too_many[2]);
}

TEST_CASE( "Swallows empty newlines", "[get_n_lines]" ) {
    std::istringstream iss{R"(a
b

c
)"};

    auto lines = get_n_lines(iss, 3);
    REQUIRE(3 == lines.size());
    REQUIRE("a" == lines[0]);
    REQUIRE("b" == lines[1]);
    REQUIRE("c" == lines[2]);

    std::istringstream iss_two{R"(a
c)"};

    auto two = get_n_lines(iss_two, 2);
    REQUIRE(2 == two.size());
    REQUIRE("a" == two[0]);
    REQUIRE("c" == two[1]);
}
