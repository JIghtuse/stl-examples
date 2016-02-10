#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <string>

template <typename Container>
class Histogram {
public:
    Histogram()
        : max{}
        , hist{}
    {
    }
    void operator()(const Container& c)
    {
        auto size = c.size();
        max = std::max(max, size);
        ++hist[size];
    }
    void print(const size_t width, std::ostream& out=std::cout) const
    {
        auto printer = [&](auto& pair) {
            out << std::setw(3) << pair.first << " | ";
            auto current_width = width * pair.second / max;
            for (size_t i = 0; i < current_width; ++i)
                out << '*';
            out << std::endl;
        };
        std::for_each(hist.begin(), hist.end(), printer);
    }

private:
    size_t max;
    std::map<size_t, size_t> hist;
};

// Plots histogram of word lengths
int main(int argc, char* argv[])
{
    if (argc == 1) {
        std::cerr << "usage: " << argv[0] << " filename1.txt [filename2.txt ..]\n";
        return 1;
    }
    Histogram<std::string> histogram;
    for (int i = 1; i < argc; ++i) {
        std::ifstream in{ argv[i] };
        histogram = std::for_each(std::istream_iterator<std::string>{ in },
                                  std::istream_iterator<std::string>{},
                                  histogram);
    }
    histogram.print(80);
}
