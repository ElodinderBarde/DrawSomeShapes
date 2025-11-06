#include "Manager/ShapePtrList.h"
#include <iostream>

namespace Messerli::Tools::Manager
{

ShapePtrList::~ShapePtrList()
{
    Clear(); // ruft delete für jedes ShapePtr auf
}

void ShapePtrList::Add(ShapePtr&& shape)
{
    m_shapes.emplace_back(std::move(shape));
}

void ShapePtrList::Remove(std::list<ShapePtr>::iterator pos)
{
    m_shapes.erase(pos);
}

void ShapePtrList::Clear()
{
    m_shapes.clear(); // ShapePtr-Destruktoren werden hier automatisch aufgerufen
}

bool ShapePtrList::Empty() const
{
    return m_shapes.empty();
}

size_t ShapePtrList::Size() const
{
    return m_shapes.size();
}

std::list<ShapePtr>::iterator ShapePtrList::Begin()
{
    return m_shapes.begin();
}

std::list<ShapePtr>::iterator ShapePtrList::End()
{
    return m_shapes.end();
}

std::list<ShapePtr>::const_iterator ShapePtrList::Begin() const
{
    return m_shapes.begin();
}

std::list<ShapePtr>::const_iterator ShapePtrList::End() const
{
    return m_shapes.end();
}

void ShapePtrList::PrintAll() const
{
    for (const auto& shape : m_shapes)
    {
        if (!shape.IsNull())
            std::cout << shape->ToString() << std::endl;
    }
}

}
