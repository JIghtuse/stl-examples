#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include <experimental/iterator>

using std::experimental::make_ostream_joiner;

using Ingredients = std::vector<std::string>;

int main()
{
    std::vector<int> v{ 5, 4, 3, 2, 1 };
    std::cout << "{ ";
    std::copy(v.begin(), v.end(), make_ostream_joiner(std::cout, ", "));
    std::cout << " }\n";

    auto ingredients{ std::map<std::string, Ingredients>{
        { "Greek salad", { "tomatoes", "cucumbers", "onion", "feta cheese", "olives", "oregano", "olive oil" } },
        { "Blueberry pie", { "blueberries", "flour", "cinnamon", "sugar", "butter" } }
    } };

    std::cout << "Ingredients for some recipes:\n";
    for (const auto& recipe : ingredients) {
        std::cout << recipe.first << ": ";
        std::copy(recipe.second.begin(), recipe.second.end(), make_ostream_joiner(std::cout, ", "));
        std::cout << std::endl;
    }
}

