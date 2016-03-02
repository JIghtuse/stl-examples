#include <catch/catch.hpp>
#include <generate_n.h>
#include <experimental/optional>
#include <vector>

using std::experimental::nullopt;
using std::experimental::optional;

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

TEST_CASE( "Returns nullopt if there are no enough results", "[get_page]" ) {
    REQUIRE(nullopt == get_page({}, 0, 1));
    REQUIRE(nullopt == get_page({}, 1, 1));
    REQUIRE(nullopt == get_page(Results(2), 2, 1));
    REQUIRE(nullopt == get_page(Results(2), 1, 2));
    REQUIRE(nullopt == get_page(Results(2), 1, 5));
    REQUIRE(nullopt == get_page(Results(2), 5, 1));
}

TEST_CASE( "Returns page if there are enough values", "[get_page]" ) {
    auto pages = get_page(Results(2), 1, 1);
    REQUIRE(nullopt != pages);
    REQUIRE(1 == pages->size());

    // first and last page with 4 results
    auto pages_all = get_page(Results(4), 4, 0);
    REQUIRE(nullopt != pages_all);
    REQUIRE(4 == pages_all->size());

    // last (4) page with one result
    auto pages_remaining = get_page(Results(10), 3, 3);
    REQUIRE(nullopt != pages_remaining);
    REQUIRE(1 == pages_remaining->size());
}
