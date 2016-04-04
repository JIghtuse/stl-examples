#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>

// TODO: make some example with Compare argument
int main()
{
    std::string alphabet(26, ' ');
    std::iota(alphabet.begin(), alphabet.end(), 'a');
    std::string vowels{"aeiou"};
    std::string consonants;

    std::cout << "alphabet:   " << alphabet << std::endl;
    std::cout << "vowels:     " << vowels << std::endl;
    std::cout << "non-vowels: ";
    std::set_difference(alphabet.begin(), alphabet.end(), vowels.begin(), vowels.end(),
                        std::ostream_iterator<char>(std::cout));
    std::cout << std::endl;

    std::set_difference(alphabet.begin(), alphabet.end(), vowels.begin(), vowels.end(),
                        std::inserter(consonants, consonants.begin()));

    std::cout << "consonants: " << consonants << std::endl;
}
