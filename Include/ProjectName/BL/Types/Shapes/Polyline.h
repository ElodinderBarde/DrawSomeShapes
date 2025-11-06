#pragma once
#include "Types/Shapes.h"
#include <windows.h>

namespace Messerli::Types
{
class Polyline : public Shapes
{
  protected:
    Point* m_arr;
    int m_amountLines;

  public:
    Polyline();

    explicit Polyline(const Point& anchor);

    Polyline(const Point* pointA, const Point& pointB) : Polyline(*pointA, pointB)
    {
    }

    Polyline(const Point& pointA, const Point& pointB);

    Polyline(Point* arr, int amountLines);

    ~Polyline() override;

    Polyline(const Polyline& other);

    Polyline& operator=(const Polyline& other);

    Polyline(Polyline&& other) noexcept;

    Polyline& operator=(Polyline&& other) noexcept;

    std::string ToString() const override;

    void Scale(double factor) override;

    [[nodiscard]] virtual int GetAmountLines() const;

    virtual Polyline& operator+=(const Point& point);

    Polyline& operator+=(const Polyline& other);

    virtual double GetTotalLength() const;

    void ExportDevicePoints(POINT* outPoints, int& count) const override;

    Polyline* Clone() const override
    {
        return new Polyline(*this);
    }
};
}
