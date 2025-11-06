#include "Types/Shapes/Line.h"
#include "Types/Shapes/Polyline.h"
#include <sstream>

namespace Messerli::Types
{

Line::Line() : Polyline(), m_EndPoint(0, 0)
{
}

Line::Line(const Point& anchor, const Point& endpoint) : Polyline(anchor), m_EndPoint(endpoint)
{
}

std::string Line::ToString() const
{
    std::ostringstream ss;
    ss << "Line: Start (" << m_Anchor.x << ", " << m_Anchor.y << ")" << " -> End (" << m_EndPoint.x << ", "
       << m_EndPoint.y << ")";
    return ss.str();
}

Line& Line::operator+=(const Point& point)
{
    m_EndPoint.x += point.x;
    m_EndPoint.y += point.y;
    return *this;
}
}
