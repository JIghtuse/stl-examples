#ifndef COLOR_H
#define COLOR_H

#include <iostream>

enum class Color {
    None,
    Grey = 30,
    Red,
    Green,
    Yellow,
    Blue,
    Violet,
    LightBlue,
};

std::ostream& operator<<(std::ostream& out, const Color& c)
{
    out << "\33[";
    if (c == Color::None)
        out << "0";
    else
        out << "1;" << static_cast<int>(c);
    return out << "m";
}

#endif // COLOR_H
