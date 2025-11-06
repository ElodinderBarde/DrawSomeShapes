#define _CRTDBG_MAP_ALLOC

#include "Circle.h"
#include "Function.h"
#include "Point.h"
#include "Rectangle.h"
#include "ShapePtrList.h"

#include <iostream>
#include <windows.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
using namespace Messerli;

int main()
{
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    Tools::Manager::ShapePtrList myShapes;

    myShapes . Add(Tools::Manager::ShapePtr(new Types::Rectangle(Types::Point(100, 100), 1000, 50)));
    myShapes . Add(Tools::Manager::ShapePtr(new Types::Circle(Types::Point(200, 100), 80)));
    myShapes . Add(Tools::Manager::ShapePtr(new Types::Ellipse(Types::Point(300, 200), 60, 100)));

    myShapes . PrintAll();

    Tools::Function::InitializeApp();
    std::wcout << L"WinAPI Test" << std::endl;

    std::wcout << L"Fenster geschlossen" << std::endl;

    _CrtDumpMemoryLeaks();
    return 0;
}

/*
int main()
{

    std::cout << "=== Polyline Test ===\n";

    // Test 1: Default Konstruktor
    Types::Polyline p0;
    std::cout << p0.ToString() << std::endl;

    // Test 2: Konstruktor mit zwei Punkten
    Types::Point a(0, 0);
    Types::Point b(3, 4);
    Types::Polyline p1(a, b);
    std::cout << "p1: " << p1.ToString() << std::endl;
    std::cout << "p1 Linienanzahl: " << p1.GetAmountLines() << std::endl;
    std::cout << "p1 Laenge: " << p1.GetTotalLength() << std::endl;

    // Test 3: += Punkt
    Types::Point c(6, 8);
    p1 += c;
    std::cout << "p1 nach += c: " << p1.ToString() << std::endl;
    std::cout << "p1 Linienanzahl: " << p1.GetAmountLines() << std::endl;
    std::cout << "p1 Laenge: " << p1.GetTotalLength() << std::endl;

    // Test 4: += Polyline
    Types::Point arr[] = {Types::Point(0, 0), Types::Point(2, 2), Types::Point(4, 2)};
    Types::Polyline p2(arr, 3);
    std::cout << "p2: " << p2.ToString() << std::endl;

    p1 += p2;
    std::cout << "p1 nach += p2: " << p1.ToString() << std::endl;
    std::cout << "p1 neue Laenge: " << p1.GetTotalLength() << std::endl;

    // Test 5: Skalierung
    p1.Scale(2.0);
    std::cout << "p1 nach Skalierung (x2): " << p1.ToString() << std::endl;

    // Test 6: Copy Konstruktor
    Types::Polyline p3 = p1;
    std::cout << "p3 (Kopie von p1): " << p3.ToString() << std::endl;

    // Test 7: Move Konstruktor
    Types::Polyline p4 = std::move(p3);
    std::cout << "p4 (Move von p3): " << p4.ToString() << std::endl;
    std::cout << "p3 nach Move: " << p3.ToString() << std::endl;

    return 0;
}*/
