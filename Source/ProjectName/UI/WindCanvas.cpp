#define NOMINMAX
#include "Types/Shapes/Ellipse.h"
#include "UI/WinCanvas.h"

#include <iostream>
#include <windows.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

namespace Messerli::Draw
{

// Hilfsstruktur zur Typdifferenzierung
struct WindowData
{
    bool isList = false;
    void* ptr = nullptr;
};

void WindCanvas::InitializeWindow(Types::Shapes* shape)
{
    HINSTANCE hInstance = GetModuleHandle(nullptr);
    constexpr wchar_t CLASS_NAME[] = L"ShapeWindow_Single";

    WNDCLASS wc{};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Shape Viewer", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1280,
                               720, nullptr, nullptr, hInstance, nullptr);

    if (!hwnd)
        return;

    auto* data = new WindowData{false, shape};
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(data));

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg{};
    BOOL ret;
    while ((ret = GetMessage(&msg, nullptr, 0, 0)) != 0)
    {
        if (ret == -1)
            break;
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (!IsWindow(hwnd))
            break;
    }

    delete data;
    HWND consoleHwnd = GetConsoleWindow();
    if (consoleHwnd)
    {
        SetForegroundWindow(consoleHwnd);
        ShowWindow(consoleHwnd, SW_RESTORE);
    }
}

void WindCanvas::InitializeWindowList(Tools::Manager::ShapePtrList* list)
{
    if (!list)
        return;

    HINSTANCE hInstance = GetModuleHandle(nullptr);
    constexpr wchar_t CLASS_NAME[] = L"ShapeWindow_List";

    WNDCLASS wc{};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Shape Viewer (List)", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                               1280, 720, nullptr, nullptr, hInstance, nullptr);

    if (!hwnd)
        return;

    auto* data = new WindowData{true, list};
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(data));

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg{};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if (!IsWindow(hwnd))
            break;
    }

    delete data;

    HWND consoleHwnd = GetConsoleWindow();
    if (consoleHwnd)
    {
        SetForegroundWindow(consoleHwnd);
        ShowWindow(consoleHwnd, SW_RESTORE);
    }
}

LRESULT CALLBACK WindCanvas::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        auto* data = reinterpret_cast<WindowData*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

        // Hintergrund löschen
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        if (data)
        {
            if (data->isList)
                DrawShapeList(hdc, reinterpret_cast<Tools::Manager::ShapePtrList*>(data->ptr));
            else
                DrawShape(hdc, reinterpret_cast<Types::Shapes*>(data->ptr));
        }

        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

void WindCanvas::DrawShape(HDC hdc, Types::Shapes* shape)
{
    if (!shape)
        return;

    // Ellipse
    if (auto* ellipse = dynamic_cast<Types::Ellipse*>(shape))
    {
        const auto& anchor = ellipse->GetAnchor();
        double a = ellipse->GetHalfAxleA();
        double b = ellipse->GetHalfAxleB();

        HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
        HGDIOBJ oldPen = SelectObject(hdc, pen);
        auto brush = static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
        HGDIOBJ oldBrush = SelectObject(hdc, brush);

        Ellipse(hdc, anchor.x - a, anchor.y - b, anchor.x + a, anchor.y + b);

        SelectObject(hdc, oldPen);
        SelectObject(hdc, oldBrush);
        DeleteObject(pen);
        return;
    }

    // Generische Shapes mit Punkten
    POINT pts[256];
    auto count = 0;
    shape->ExportDevicePoints(pts, count);
    if (count < 2)
        return;

    HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
    HGDIOBJ oldPen = SelectObject(hdc, pen);
    Polyline(hdc, pts, count);

    HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
    HGDIOBJ oldBrush = SelectObject(hdc, brush);
    constexpr auto r = 4;
    for (auto i = 0; i < count; ++i)
    {
        Ellipse(hdc, pts[i].x - r, pts[i].y - r, pts[i].x + r, pts[i].y + r);
    }

    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(pen);
    DeleteObject(brush);
}

void WindCanvas::DrawShapeList(HDC hdc, Tools::Manager::ShapePtrList* list)
{
    if (!list)
        return;

    for (auto it = list->Begin(); it != list->End(); ++it)
    {
        auto* shape = it->operator->();
        if (shape)
            DrawShape(hdc, shape);
    }
}

}
