#include "Types/Shapes/Circle.h"
#include "Types/Point.h"
#include <cmath>

namespace Messerli::Types
{

Circle::Circle() : Ellipse(Point(0, 0), 50.0, 50.0)
{
}

Circle::Circle(const Point& center, double radius) : Ellipse(center, radius, radius)
{
}

Circle::~Circle() = default;

double Circle::GetRadius() const
{
    return GetHalfAxleA();
}

void Circle::SetRadius(double radius)
{
    SetHalfAxleA(radius);
    SetHalfAxleB(radius);
}

void Circle::ExportDevicePoints(POINT* points, int& count) const
{
    constexpr auto SEGMENTS = 64;
    constexpr auto PI = 3.14159265358979323846;
    const Point& center = GetAnchor();
    const double r = GetHalfAxleA();

    count = SEGMENTS + 1;
    for (auto i = 0; i <= SEGMENTS; ++i)
    {
        double angle = (2.0 * PI * i) / SEGMENTS;
        points[i].x = static_cast<LONG>(center.x + r * std::cos(angle));
        points[i].y = static_cast<LONG>(center.y + r * std::sin(angle));
    }
}
}
