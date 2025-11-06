#pragma once
#include "Types/Shapes.h"
#include <string>
#include <windows.h>

namespace Messerli::Types
{
class Ellipse : public Shapes
{
    double m_halfAxleA;
    double m_halfAxleB;

  public:
    Ellipse();

    Ellipse(const Point& anchor, double halfAxleA, double halfAxleB);

    ~Ellipse() override = default;

    void Scale(double factor) override;

    void ExportDevicePoints(POINT* points, int& count) const override;

    [[nodiscard]] double GetHalfAxleA() const
    {
        return m_halfAxleA;
    }

    [[nodiscard]] double GetHalfAxleB() const
    {
        return m_halfAxleB;
    }

    void SetHalfAxleA(double a)
    {
        m_halfAxleA = a;
    }

    void SetHalfAxleB(double b)
    {
        m_halfAxleB = b;
    }

    [[nodiscard]] const Point& GetAnchor() const override
    {
        return m_Anchor;
    }

    [[nodiscard]] std::string ToString() const override;

    [[nodiscard]] double GetCircumference() const;

    [[nodiscard]] Ellipse* Clone() const override
    {
        return new Ellipse(*this);
    }
};
}
