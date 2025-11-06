#include "Types/Shapes/Polygon.h"
#include "Types/Point.h"
#include <cmath>
#include <sstream>

namespace Messerli::Types
{

Polygon::Polygon() : Polyline()
{
}

Polygon::Polygon(Point* arr, int amountLines) : Polyline(arr, amountLines)
{
}

Polygon::Polygon(const Point& anchor, int amountLines) : Polyline(anchor)
{
    m_amountLines = amountLines;
}

Polygon::Polygon(const Polygon& other) : Polyline(other)
{
}

Polygon& Polygon::operator=(const Polygon& other)
{
    if (this != &other)
        Polyline::operator=(other);
    return *this;
}

Polygon::Polygon(Polygon&& other) noexcept : Polyline(std::move(other))
{
}

Polygon& Polygon::operator=(Polygon&& other) noexcept
{
    if (this != &other)
        Polyline::operator=(std::move(other));
    return *this;
}

std::string Polygon::ToString() const
{
    if (m_amountLines == 0 || m_arr == nullptr)
        return "Polygon: No points";

    std::ostringstream ss;
    ss << "Polygon: ";
    for (auto i = 0; i < m_amountLines; ++i)
    {
        Point abs = m_Anchor + m_arr[i];
        ss << "(" << abs.x << ", " << abs.y << ")";
        if (i < m_amountLines - 1)
            ss << " -> ";
    }
    ss << " -> (" << (m_Anchor + m_arr[0]).x << ", " << (m_Anchor + m_arr[0]).y << ") (closed)";
    return ss.str();
}

int Polygon::GetAmountLines() const
{
    return m_amountLines;
}

double Polygon::GetTotalLength() const
{
    if (m_amountLines < 2 || m_arr == nullptr)
        return 0.0;

    auto length = 0.0;
    for (auto i = 0; i < m_amountLines - 1; ++i)
    {
        length += Point::Distance(m_arr[i], m_arr[i + 1]);
    }

    length += Point::Distance(m_arr[m_amountLines - 1], m_arr[0]);
    return length;
}

int Polygon::GetCornerCount() const
{
    return m_amountLines;
}

double Polygon::GetPerimeter() const
{
    return GetTotalLength();
}

void Polygon::ExportDevicePoints(POINT* outPoints, int& count) const
{
    if (m_arr == nullptr || m_amountLines <= 0)
    {
        count = 0;
        return;
    }

    for (auto i = 0; i < m_amountLines; ++i)
    {
        outPoints[i].x = static_cast<LONG>(m_Anchor.x + m_arr[i].x);
        outPoints[i].y = static_cast<LONG>(m_Anchor.y + m_arr[i].y);
    }

    outPoints[m_amountLines].x = static_cast<LONG>(m_Anchor.x + m_arr[0].x);
    outPoints[m_amountLines].y = static_cast<LONG>(m_Anchor.y + m_arr[0].y);

    count = m_amountLines + 1;
}
}
