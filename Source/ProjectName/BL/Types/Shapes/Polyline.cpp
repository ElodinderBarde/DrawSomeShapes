#include "Types/Shapes/Polyline.h"
#include "Types/Point.h"
#include <cmath>
#include <sstream>

namespace Messerli::Types
{

Polyline::Polyline() : Shapes(Point(0, 0)), m_arr(nullptr), m_amountLines(0)
{
}

Polyline::Polyline(const Point& anchor) : Shapes(anchor), m_arr(nullptr), m_amountLines(0)
{
}

Polyline::Polyline(const Point& pointA, const Point& pointB) : Shapes(pointA), m_amountLines(2)
{
    m_arr = new Point[m_amountLines];
    m_arr[0] = Point(0, 0);
    m_arr[1] = pointB - m_Anchor;
}

Polyline::Polyline(Point* arr, int amountLines)
    : Shapes(amountLines > 0 ? arr[0] : Point(0, 0)), m_arr(nullptr), m_amountLines(amountLines)
{
    if (amountLines > 0)
    {
        m_arr = new Point[amountLines];
        for (auto i = 0; i < amountLines; ++i)
        {
            m_arr[i] = arr[i] - m_Anchor;
        }
    }
}

Polyline::~Polyline()
{
    delete[] m_arr;
    m_arr = nullptr;
}

Polyline::Polyline(const Polyline& other) : Shapes(other.m_Anchor), m_arr(nullptr), m_amountLines(other.m_amountLines)
{
    if (m_amountLines > 0)
    {
        m_arr = new Point[m_amountLines];
        for (auto i = 0; i < m_amountLines; ++i)
        {
            m_arr[i] = other.m_arr[i];
        }
    }
}

Polyline& Polyline::operator=(const Polyline& other)
{
    if (this != &other)
    {
        delete[] m_arr;
        m_amountLines = other.m_amountLines;
        m_Anchor = other.m_Anchor;

        if (m_amountLines > 0)
        {
            m_arr = new Point[m_amountLines];
            for (auto i = 0; i < m_amountLines; ++i)
            {
                m_arr[i] = other.m_arr[i];
            }
        }
        else
        {
            m_arr = nullptr;
        }
    }
    return *this;
}

Polyline::Polyline(Polyline&& other) noexcept
    : Shapes(other.m_Anchor), m_arr(other.m_arr), m_amountLines(other.m_amountLines)
{
    other.m_arr = nullptr;
    other.m_amountLines = 0;
}

Polyline& Polyline::operator=(Polyline&& other) noexcept
{
    if (this != &other)
    {
        delete[] m_arr;

        m_Anchor = other.m_Anchor;
        m_arr = other.m_arr;
        m_amountLines = other.m_amountLines;

        other.m_arr = nullptr;
        other.m_amountLines = 0;
    }
    return *this;
}

std::string Polyline::ToString() const
{
    if (m_amountLines == 0 || !m_arr)
        return "Polyline: No points";

    std::ostringstream ss;
    ss << "Polyline: ";
    for (auto i = 0; i < m_amountLines; ++i)
    {
        Point abs = m_Anchor + m_arr[i];
        ss << "(" << abs.x << ", " << abs.y << ")";
        if (i < m_amountLines - 1)
            ss << " -> ";
    }
    return ss.str();
}

void Polyline::Scale(double factor)
{
    for (auto i = 0; i < m_amountLines; ++i)
    {
        m_arr[i] *= factor;
    }
}

int Polyline::GetAmountLines() const
{
    return (m_amountLines > 1) ? m_amountLines - 1 : 0;
}

Polyline& Polyline::operator+=(const Point& point)
{
    auto newArr = new Point[m_amountLines + 1];
    for (auto i = 0; i < m_amountLines; ++i)
    {
        newArr[i] = m_arr[i];
    }
    newArr[m_amountLines] = point - m_Anchor;

    delete[] m_arr;
    m_arr = newArr;
    ++m_amountLines;

    return *this;
}

Polyline& Polyline::operator+=(const Polyline& other)
{
    if (other.m_amountLines == 0)
        return *this;
    if (m_amountLines == 0)
    {
        m_amountLines = other.m_amountLines;
        m_arr = new Point[m_amountLines];
        for (auto i = 0; i < m_amountLines; ++i)
        {
            m_arr[i] = other.m_arr[i];
        }
        return *this;
    }

    auto newArr = new Point[m_amountLines + other.m_amountLines];

    for (auto i = 0; i < m_amountLines; ++i)
    {
        newArr[i] = m_arr[i];
    }

    Point last = m_arr[m_amountLines - 1];
    for (auto j = 0; j < other.m_amountLines; ++j)
    {
        newArr[m_amountLines + j] = other.m_arr[j] + last;
    }

    delete[] m_arr;
    m_arr = newArr;
    m_amountLines += other.m_amountLines;

    return *this;
}

double Polyline::GetTotalLength() const
{
    if (m_amountLines < 2)
        return 0.0;

    auto length = 0.0;
    for (auto i = 0; i < m_amountLines - 1; ++i)
    {
        length += Point::Distance(m_arr[i], m_arr[i + 1]);
    }

    return length;
}

void Polyline::ExportDevicePoints(POINT* outPoints, int& count) const
{
    count = 0;
    if (!m_arr || m_amountLines <= 0)
        return;

    for (auto i = 0; i < m_amountLines; ++i)
    {
        outPoints[i].x = static_cast<LONG>(m_Anchor.x + m_arr[i].x);
        outPoints[i].y = static_cast<LONG>(m_Anchor.y + m_arr[i].y);
        ++count;
    }
}

}
