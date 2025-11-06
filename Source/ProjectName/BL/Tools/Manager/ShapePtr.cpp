#include "Manager/ShapePtr.h"
#include <utility>

namespace Messerli::Tools::Manager
{

ShapePtr::ShapePtr(Types::Shapes* ptr) : m_ptr(ptr)
{
}

ShapePtr::ShapePtr(const ShapePtr& other)
{
    if (other.m_ptr)
        m_ptr = other.m_ptr->Clone();
    else
        m_ptr = nullptr;
}

ShapePtr::ShapePtr(ShapePtr&& other) noexcept : m_ptr(other.m_ptr)
{
    other.m_ptr = nullptr;
}

ShapePtr::~ShapePtr()
{
    delete m_ptr;
    m_ptr = nullptr;
}

ShapePtr& ShapePtr::operator=(const ShapePtr& other)
{
    if (this != &other)
    {
        delete m_ptr;
        m_ptr = other.m_ptr ? other.m_ptr->Clone() : nullptr;
    }
    return *this;
}

ShapePtr& ShapePtr::operator=(ShapePtr&& other) noexcept
{
    if (this != &other)
    {
        delete m_ptr;
        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
    }
    return *this;
}

Types::Shapes* ShapePtr::operator->() const
{
    return m_ptr;
}

Types::Shapes& ShapePtr::operator*() const
{
    return *m_ptr;
}

}
