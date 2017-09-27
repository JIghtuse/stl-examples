#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
// Will soon be in std
#include <boost/algorithm/clamp.hpp>

namespace alg = boost::algorithm;

constexpr char kEmptySymbol{' '};
constexpr char kFieldSymbol{'*'};
constexpr char kHeroSymbol{'U'};

struct Position {
    int x;
    int y;
};

bool operator==(const Position& a, const Position& b)
{
    return a.x == b.x && a.y == b.y;
}

enum class Direction : int {
    North,
    West,
    South,
    East,
};

std::ostream& operator<<(std::ostream& out, const Direction& d)
{
    switch (d) {
    case Direction::North:
        return out << "North";
    case Direction::West:
        return out << "West";
    case Direction::South:
        return out << "South";
    case Direction::East:
        return out << "East";
    }
    return out;
}

struct Hero {
    explicit Hero(Position pos)
        : m_pos{pos}
    {}
    Position pos() const { return m_pos; }
    void set_pos(Position new_pos);
    Position m_pos;
};

void Hero::set_pos(Position new_pos)
{
    this->m_pos = new_pos;
}

struct Field {
    bool try_to_move_hero(Direction d);
    int width;
    int height;
    Hero hero;
};

bool Field::try_to_move_hero(Direction d)
{
    auto new_pos = hero.pos();

    switch (d) {
    case Direction::East:
        new_pos.x = alg::clamp(new_pos.x - 1, 0, width - 1);
        break;
    case Direction::West:
        new_pos.x = alg::clamp(new_pos.x + 1, 0, width - 1);
        break;
    case Direction::North:
        new_pos.y = alg::clamp(new_pos.y - 1, 0, height - 1);
        break;
    case Direction::South:
        new_pos.y = alg::clamp(new_pos.y + 1, 0, height - 1);
        break;
    }

    auto old_pos = hero.pos();
    hero.set_pos(new_pos);
    return !(new_pos == old_pos);
}

std::ostream& operator<<(std::ostream& out, const Field& f) {
    for (int x = 0; x < f.width + 2; ++x) {
        out << kFieldSymbol;
    }
    out << '\n';

    for (int y = 0; y < f.height; ++y) {

        out << kFieldSymbol;
        for (int x = 0; x < f.width; ++x) {
            if (f.hero.m_pos == Position{x, y}) {
                out << kHeroSymbol;
            } else {
                out << kEmptySymbol;
            }
        }
        out << kFieldSymbol;

        out << '\n';
    }

    for (int x = 0; x < f.width + 2; ++x) {
        out << kFieldSymbol;
    }
    out << '\n';

    return out;
}

Direction random_direction()
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 3);
    std::mt19937 gen(rd());
    return static_cast<Direction>(dist(gen));
}

int main()
{
    using namespace std::chrono_literals;
    auto field = Field{12, 6, Hero{{  5, 2 }}};

    auto direction = random_direction();
    std::cout << "Going to " << direction << std::endl;
    while (field.try_to_move_hero(direction)) {
        std::cout << field << std::endl;
        std::this_thread::sleep_for(500ms);
    }
}
