#pragma once
#include "ShapePtrList.h"
#include "Types/Shapes.h"

#include <windows.h>

namespace Messerli::Tools
{
class Shape;
}

namespace Messerli::Draw
{
class WindCanvas
{
  public:
    static void InitializeWindow(Types::Shapes* shape);

    static void InitializeWindowList(Tools::Manager::ShapePtrList* list);

  private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    static void DrawShape(HDC hdc, Types::Shapes* shape);

    static void DrawShapeList(HDC hdc, Tools::Manager::ShapePtrList* list);
};
}
