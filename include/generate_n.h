#pragma once

#include <string>
#include <vector>
#include <experimental/optional>

struct stream_error{};

// Tries to read @n lines from input stream @in.
// Returns vector with @n strings of input stream on success.
// Returns vector with less (possibly 0) strings of input stream if @in goes to bad/fail state
std::vector<std::string> get_n_lines(std::istream& in, size_t n);

struct Page{};
using Results = std::vector<Page>;
using GroupBy = size_t;
using PageNum = size_t;

// Pagination: return @pagenum page of results vector, @n results per page
// Returns @n results from page @pagenum if there are enough results
// Returns less then @n values or std::experimental::nullopt, if there are not enough results
std::experimental::optional<Results> get_page(const Results& all_results, GroupBy n, PageNum pagenum);
