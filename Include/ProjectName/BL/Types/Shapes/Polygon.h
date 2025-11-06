#pragma once
#include "Polyline.h"

namespace Messerli::Types
{

class Polygon : public Polyline
{
  public:
    Polygon();

    Polygon(Point* arr, int amountLines);

    Polygon(const Point& anchor, int amountLines);

    ~Polygon() override = default;

    Polygon(const Polygon& other);

    Polygon& operator=(const Polygon& other);

    Polygon(Polygon&& other) noexcept;

    Polygon& operator=(Polygon&& other) noexcept;

    [[nodiscard]] std::string ToString() const override;

    [[nodiscard]] int GetAmountLines() const override;

    [[nodiscard]] double GetTotalLength() const override;

    [[nodiscard]] int GetCornerCount() const;

    [[nodiscard]] virtual double GetPerimeter() const;

    void ExportDevicePoints(POINT* outPoints, int& count) const override;

    [[nodiscard]] Polygon* Clone() const override
    {
        return new Polygon(*this);
    }
};
}
