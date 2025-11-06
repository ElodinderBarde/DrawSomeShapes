#pragma once
#include "Polygon.h"

namespace Messerli::Types
{

class Rectangle : public Polygon
{
    double m_width{};
    double m_height{};

  public:
    Rectangle();

    Rectangle(const Point& anchor, double width, double height);

    Rectangle(const Point& pointA, const Point& pointB);

    ~Rectangle() override = default;

    Rectangle(const Rectangle& other);

    Rectangle& operator=(const Rectangle& other);

    [[nodiscard]] std::string ToString() const override;

    [[nodiscard]] double GetPerimeter() const override;

    [[nodiscard]] double GetArea() const;

    void ExportDevicePoints(POINT* outPoints, int& count) const override;

    [[nodiscard]] Rectangle* Clone() const override
    {
        return new Rectangle(*this);
    }
};
}
