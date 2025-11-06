#pragma once
#include "Polyline.h"

namespace Messerli::Types
{

class Line : public Polyline
{
  public:
    Point m_EndPoint;

    Line();

    Line(const Point& anchor, const Point& endpoint);

    ~Line() override = default;

    Line(const Line& other) = default;

    Line& operator=(const Line& other) = default;

    Line(Line&& other) noexcept = default;

    Line& operator=(Line&& other) noexcept = default;

    [[nodiscard]] std::string ToString() const override;

    Line& operator+=(const Point& point) override;

    [[nodiscard]] Line* Clone() const override
    {
        return new Line(*this);
    }
};
}
