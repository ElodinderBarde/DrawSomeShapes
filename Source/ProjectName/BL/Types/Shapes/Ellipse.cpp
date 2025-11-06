#include "Types/Shapes/Ellipse.h"
#include "Types/Point.h"

#include <cmath>
#include <iomanip>
#include <sstream>

namespace Messerli::Types
{

Ellipse::Ellipse() : Shapes(Point(0, 0)), m_halfAxleA(50.0), m_halfAxleB(25.0)
{
}

Ellipse::Ellipse(const Point& anchor, double halfAxleA, double halfAxleB)
    : Shapes(anchor), m_halfAxleA(halfAxleA), m_halfAxleB(halfAxleB)
{
}

void Ellipse::Scale(double factor)
{
    m_halfAxleA *= factor;
    m_halfAxleB *= factor;
}

void Ellipse::ExportDevicePoints(POINT* points, int& count) const
{
    constexpr auto segments = 36;
    count = segments;
    double angleStep = 2.0 * 3.14159 / segments;

    for (auto i = 0; i < segments; ++i)
    {
        double angle = i * angleStep;
        points[i].x = static_cast<LONG>(m_Anchor.x + m_halfAxleA * std::cos(angle));
        points[i].y = static_cast<LONG>(m_Anchor.y + m_halfAxleB * std::sin(angle));
    }
}

std::string Ellipse::ToString() const
{
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << Shapes::ToString() << " | Halfaxle A: " << m_halfAxleA << " | Halfaxle B: " << m_halfAxleB;
    return ss.str();
}

double Ellipse::GetCircumference() const
{
    constexpr auto pi = 3.14159;
    const double a = m_halfAxleA;
    const double b = m_halfAxleB;
    return pi * ((1.5 * (a + b)) - std::sqrt(a * b));
}
}
