#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <print_container.h>

using Words = std::vector<std::string>;

// Taken from http://en.cppreference.com/w/cpp/algorithm/remove
void erase_remove_idiom()
{
    std::string s = "Text  with     some    spaces";
    print_container(s, "initially        : ", "");

    // erase-remove idiom

    auto new_end = std::remove(s.begin(), s.end(), ' ');
    print_container(s, "after std::remove: ", "");

    s.erase(new_end, s.end());
    print_container(s, "after s.erase    : ", "");
}

// It is probably not efficient for too many @should_be_censored
void censor(Words& words, const Words& should_be_censored)
{
    for (const auto& unacceptable : should_be_censored) {
        words.erase(std::remove(words.begin(), words.end(), unacceptable), words.end());
    }
}

void test_censor()
{
    auto words = Words{"lorem", "ipsum", "dolor", "sit", "amet", "consetetur",
                       "sadipscing", "elitr", "sed", "diam", "nonumy", "eirmod"};
    print_container(words, "words before censorship: ");

    censor(words, {"dolor", "diam", "consetetur", "sadipscing"});
    print_container(words, "words after censorship:  ");
}

int main()
{
    erase_remove_idiom();
    test_censor();
}
