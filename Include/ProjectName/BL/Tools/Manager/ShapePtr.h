#pragma once
#include "Types/Shapes.h"

namespace Messerli::Tools ::Manager
{

class ShapePtr
{
    Types::Shapes* m_ptr;

  public:
    explicit ShapePtr(Types::Shapes* ptr = nullptr);

    ShapePtr(const ShapePtr& other);

    ShapePtr(ShapePtr&& other) noexcept;

    ~ShapePtr();

    ShapePtr& operator=(const ShapePtr& other);

    ShapePtr& operator=(ShapePtr&& other) noexcept;

    Types::Shapes* operator->() const;

    Types::Shapes& operator*() const;

    Types::Shapes* Get() const
    {
        return m_ptr;
    }

    bool IsNull() const
    {
        return m_ptr == nullptr;
    }

    operator Messerli::Types::Shapes*() const
    {
        return m_ptr;
    }
};

}
