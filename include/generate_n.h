#pragma once

#include <string>
#include <vector>

struct stream_error{};

// Tries to read @n lines from input stream @in.
// Returns vector with @n strings of input stream on success.
// Returns vector with less (possibly 0) strings of input stream if @in goes to bad/fail state
std::vector<std::string> get_n_lines(std::istream& in, size_t n);
