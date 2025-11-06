#pragma once
#include <string>

namespace Messerli::Types
{
class Point
{
public:
    double x = 0.0;
    double y = 0.0;

    Point();

    Point(double x, double y);

    ~Point();

    [[nodiscard]] std::string ToString() const;

    double GetX() const;

    double GetY() const;

    [[nodiscard]] static double Distance(const Point& a, const Point& b);

    Point& operator*=(double factor);
};

Point operator+(const Point& a, const Point& b);

Point operator-(const Point& a, const Point& b);

bool operator==(const Point& a, const Point& b);

bool operator!=(const Point& a, const Point& b);

std::ostream& operator<<(std::ostream& os, const Point& p);
}
