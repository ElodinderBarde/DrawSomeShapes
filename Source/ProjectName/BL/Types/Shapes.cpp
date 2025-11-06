#include "Types/Shapes.h"
#include "Types/Point.h"
#include <sstream>

namespace Messerli::Types
{

Shapes::Shapes() : m_Anchor(0, 0)
{
}

Shapes::Shapes(const Point& anchor) : m_Anchor(anchor)
{
}

std::string Shapes::ToString() const
{
    std::ostringstream ss;
    ss << "Anchor: (" << m_Anchor.x << ", " << m_Anchor.y << ")";
    return ss.str();
}

const Point& Shapes::GetAnchor() const
{
    return m_Anchor;
}

void Shapes::SetAnchor(const Point& anchor)
{
    m_Anchor = anchor;
}

void Shapes::Move(double x, double y)
{
    m_Anchor.x += x;
    m_Anchor.y += y;
}

void Shapes::MoveNegate(double x, double y)
{
    m_Anchor.x -= x;
    m_Anchor.y -= y;
}

void Shapes::Scale(double factor)
{
    m_Anchor.x *= factor;
    m_Anchor.y *= factor;
}

void Shapes::ExportDevicePoints(POINT* points, int& count) const
{
    count = 0;
}

Shapes* Shapes::Clone() const
{
    return nullptr;
}
}
