#pragma once
#include "Point.h"
#include <string>
#include <windows.h>

namespace Messerli::Types
{

class Shapes
{
  protected:
    Point m_Anchor;

  public:
    Shapes();

    explicit Shapes(const Point& anchor);

    virtual ~Shapes() = default;

    [[nodiscard]] virtual std::string ToString() const;

    [[nodiscard]] virtual const Point& GetAnchor() const;

    void SetAnchor(const Point& anchor);

    void Move(double x, double y);

    void MoveNegate(double x, double y);

    virtual void Scale(double factor);

    virtual void ExportDevicePoints(POINT* points, int& count) const = 0;

    [[nodiscard]] virtual Shapes* Clone() const;
};

}
