#pragma once
#include "Manager/ShapePtr.h"
#include <list>

namespace Messerli::Tools::Manager
{

class ShapePtrList
{
    std::list<ShapePtr> m_shapes;

  public:
    ShapePtrList() = default;

    ~ShapePtrList();

    void Add(ShapePtr&& shape);

    void Remove(std::list<ShapePtr>::iterator pos);

    void Clear();

    bool Empty() const;

    size_t Size() const;

    std::list<ShapePtr>::iterator Begin();

    std::list<ShapePtr>::iterator End();

    std::list<ShapePtr>::const_iterator Begin() const;

    std::list<ShapePtr>::const_iterator End() const;

    void PrintAll() const;
};

}
