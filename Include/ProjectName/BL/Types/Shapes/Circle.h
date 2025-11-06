#pragma once
#include "Ellipse.h"

namespace Messerli::Types
{
class Circle : public Ellipse
{
public:
    Circle();

    Circle(const Point& center, double radius);

    ~Circle() override;

    double GetRadius() const;

    void SetRadius(double radius);

    void ExportDevicePoints(POINT* points, int& count) const override;

    Circle* Clone() const override
    {
        return new Circle(*this);
    }
};
}
