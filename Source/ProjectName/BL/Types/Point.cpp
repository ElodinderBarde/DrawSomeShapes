#include "./Types/Point.h"

#include "Tools/Function.h"

#include <iostream>

namespace Messerli::Types
{
Point::Point() = default;

Point::Point(double x, double y) : x(x), y(y)
{
}

Point::~Point()
{
}

std::string Point::ToString() const
{
    return "(" + Tools::Function::TrimTrailingZeroKeepOne(std::to_string(x)) + ", " +
           Tools::Function::TrimTrailingZeroKeepOne(std::to_string(y)) + ")";
}

double Point::Distance(const Point& a, const Point& b)
{
    const double dx = b.x - a.x;
    const double dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
}

Point& Point::operator*=(double factor)
{
    x *= factor;
    y *= factor;
    return *this;
}

// Global operators

double Point::GetX() const
{
    return x;
}

double Point::GetY() const
{
    return y;
}

Point operator+(const Point& a, const Point& b)
{
    return {a.x + b.x, a.y + b.y};
}

Point operator-(const Point& a, const Point& b)
{
    return {a.x - b.x, a.y - b.y};
}

bool operator==(const Point& a, const Point& b)
{
    return a.x == b.x && a.y == b.y;
}

bool operator!=(const Point& a, const Point& b)
{
    return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}
}
