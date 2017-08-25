#include <functional>
#include <iostream>

struct Point {
    int x = 0;
    int y = 0;
};

struct Point3d {
    Point p;
    int z = 0;
};

template<typename T, typename GetFieldFunction, typename Value>
void setField(T& object, GetFieldFunction f, const Value& value)
{
    f(object) = value;
}

int main()
{
    auto p2d = Point{};
    auto p3d = Point3d{};

    setField(p2d, std::mem_fn(&Point::x), 1);
    setField(p3d, std::mem_fn(&Point3d::z), 3);

    std::cout << p2d.x << ' ' << p2d.y << '\n';
    std::cout << p3d.p.x << ' ' << p3d.p.y << ' ' << p3d.z << '\n';
}
