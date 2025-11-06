#include "Types/Shapes/Rectangle.h"
#include "Types/Point.h"
#include <sstream>

namespace Messerli::Types
{

Rectangle::Rectangle() : Polygon(), m_width(0.0), m_height(0.0)
{
    m_amountLines = 4;
    m_arr = new Point[4]{Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
}

Rectangle::Rectangle(const Point& anchor, double width, double height) : Polygon(), m_width(width), m_height(height)
{
    m_Anchor = anchor;
    m_amountLines = 4;
    m_arr = new Point[4]{Point(0, 0), Point(width, 0), Point(width, height), Point(0, height)};
}

Rectangle::Rectangle(const Point& pointA, const Point& pointB)
    : Polygon(), m_width(pointB.x - pointA.x), m_height(pointB.y - pointA.y)
{
    m_Anchor = pointA;
    m_amountLines = 4;
    m_arr = new Point[4]{Point(0, 0), Point(m_width, 0), Point(m_width, m_height), Point(0, m_height)};
}

Rectangle::Rectangle(const Rectangle& other) : Polygon(other), m_width(other.m_width), m_height(other.m_height)
{
}

Rectangle& Rectangle::operator=(const Rectangle& other)
{
    if (this != &other)
    {
        Polygon::operator=(other);
        m_width = other.m_width;
        m_height = other.m_height;
    }
    return *this;
}

std::string Rectangle::ToString() const
{
    std::ostringstream ss;
    ss << "Rectangle: Anchor " << m_Anchor.ToString() << " | Width: " << m_width << " | Height: " << m_height;
    return ss.str();
}

double Rectangle::GetPerimeter() const
{
    return 2 * (m_width + m_height);
}

double Rectangle::GetArea() const
{
    return m_width * m_height;
}

void Rectangle::ExportDevicePoints(POINT* outPoints, int& count) const
{
    if (!m_arr || m_amountLines != 4)
    {
        count = 0;
        return;
    }

    for (auto i = 0; i < 4; ++i)
    {
        outPoints[i].x = static_cast<LONG>(m_Anchor.x + m_arr[i].x);
        outPoints[i].y = static_cast<LONG>(m_Anchor.y + m_arr[i].y);
    }

    outPoints[4].x = outPoints[0].x;
    outPoints[4].y = outPoints[0].y;
    count = 5;
}
}
