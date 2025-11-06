#include "SubMenuListDraw.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Function.h"
#include "InputManager.h"
#include "Polygon.h"
#include "Polyline.h"
#include "Rectangle.h"
#include "ShapePtrList.h"
#include "WinCanvas.h"
#include "Data/Strings.h"

#include <iostream>

namespace Messerli::Tools::Manager
{

void SubMenuAddShapes()
{

    ShapePtrList shapeList;
    auto running = true;

    while (running)
    {
        auto choice = 0;
        std::cout << "\n=== Shape-Hinzufuegen-Menue ===\n";
        std::cout << "1. Rechteck\n";
        std::cout << "2. Kreis\n";
        std::cout << "3. Ellipse\n";
        std::cout << "4. Polyline\n";
        std::cout << "5. Polygon\n";
        std::cout << "0. Abbrechen und zeichnen\n";
        std::cout << "--------------------------------\n";
        std::cout << "Ihre Auswahl: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1: {
            int x, y, w, h;
            std::cout << "Ecke oben links (x y): ";
            std::cin >> x >> y;
            std::cout << "Breite und Hoehe: ";
            std::cin >> w >> h;
            shapeList . Add(ShapePtr(new Types::Rectangle(Types::Point(x, y), w, h)));
            std::cout << "Rechteck hinzugefuegt.\n";
            break;
        }
        case 2: {
            int x, y, r;
            std::cout << "Mittelpunkt (x y): ";
            std::cin >> x >> y;
            std::cout << "Radius: ";
            std::cin >> r;
            shapeList . Add(ShapePtr(new Types::Circle(Types::Point(x, y), r)));
            std::cout << "Kreis hinzugefuegt.\n";
            break;
        }
        case 3: {
            int x, y, rx, ry;
            std::cout << "Mittelpunkt (x y): ";
            std::cin >> x >> y;
            std::cout << "Radius X / Y: ";
            std::cin >> rx >> ry;
            shapeList . Add(ShapePtr(new Types::Ellipse(Types::Point(x, y), rx, ry)));
            std::cout << "Ellipse hinzugefuegt.\n";
            break;
        }
        case 4: {
            std::cout << "\nPolyline-Erstellung:\n";
            int n;
            std::cout << "Wie viele Punkte? (min. 2): ";
            std::cin >> n;

            if (n < 2)
            {
                std::cout << "Zu wenige Punkte.\n";
                break;
            }

            auto* points = new Types::Point[n];

            for (auto i = 0; i < n; ++i)
            {
                double x, y;
                std::cout << "  Punkt " << i + 1 << " (x y): ";
                std::cin >> x >> y;
                points[i] = Types::Point(x, y);
            }

            auto* pline = new Types::Polyline(points[0], points[1]);
            for (auto i = 2; i < n; ++i)
            {
                *pline += points[i];
            }

            shapeList . Add(ShapePtr(pline));
            std::cout << "Polyline hinzugefuegt.\n";

            delete[] points;
            break;
        }
        case 5: {
            std::cout << "\nPolygon-Erstellung:\n";
            std::cout << "Soll das Polygon gleichmässig erzeugt werden (1) "
                "oder möchtest du die Punkte manuell setzen (2)? ";
            auto mode = 0;
            std::cin >> mode;

            if (mode == 1)
            {
                std::cout << "Wie viele Ecken? (min. 3): ";
                int edges;
                std::cin >> edges;

                if (edges < 3)
                {
                    std::cout << "Zu wenige Ecken.\n";
                    break;
                }

                double x, y;
                std::cout << "Ankerpunkt (x y): ";
                std::cin >> x >> y;
                auto anchor = new Types::Point(x, y);

                std::cout << "Zweiten Punkt (x y): ";
                double x2, y2;
                std::cin >> x2 >> y2;

                auto* points = new Types::Point[edges + 1];
                points[0] = *anchor;

                double dx = x2 - x;
                double dy = y2 - y;
                const double startAngle = atan2(dy, dx);
                const double r = sqrt(dx * dx + dy * dy);
                if (r == 0)
                {
                    std::cout << "Fehler: Der zweite Punkt darf nicht gleich dem Ankerpunkt sein!\n";
                    delete[] points;
                    delete anchor;
                    break;
                }

                constexpr auto PI = 3.14159265358979323846;
                const double angleStep = 2 * PI / edges;

                for (auto i = 0; i < edges; ++i)
                {
                    double angle = startAngle + i * angleStep;
                    double newX = x + r * cos(angle);
                    double newY = y + r * sin(angle);
                    points[i] = Types::Point(newX, newY);
                }

                // schließt das Polygon
                points[edges] = points[0];

                auto* poly = new Types::Polygon(points, edges + 1);
                shapeList . Add(ShapePtr(poly));
                std::cout << "Regelmässiges Polygon hinzugefuegt.\n";

                delete[] points;
                delete anchor;
            }
            else if (mode == 2)
            {
                int n;
                std::cout << "Wie viele Ecken? (min. 3): ";
                std::cin >> n;

                if (n < 3)
                {
                    std::cout << "Zu wenige Ecken.\n";
                    break;
                }

                auto* points = new Types::Point[n + 1];
                for (auto i = 0; i < n; ++i)
                {
                    double x, y;
                    std::cout << "  Ecke " << i + 1 << " (x y): ";
                    std::cin >> x >> y;
                    points[i] = Types::Point(x, y);
                }

                points[n] = points[0];

                auto* poly = new Types::Polygon(points, n + 1);
                shapeList . Add(ShapePtr(poly));
                std::cout << "Manuelles Polygon hinzugefuegt.\n";

                delete[] points;
            }
            else
            {
                std::cout << "Ungueltige Auswahl.\n";
            }

            break;
        }

        case 0:
            running = false;
            break;

        default:
            std::cout << "Ungueltige Auswahl!\n";
        }

        if (running)
        {
            char addMore;
            std::cout << "Weitere Shape hinzufuegen? (y/n): ";
            std::cin >> addMore;
            if (std::cin . fail())
            {
                std::cin . clear();
                std::cin . ignore(10000, '\n');
                addMore = 'n';
            }

            if (addMore == 'n' || addMore == 'N')
                running = false;
        }
    }

    std::cout << "\n=== Aktuelle Shape-Liste ===\n";
    shapeList . PrintAll();

    std::cout << "\n=== Zeichne alle Shapes ===\n";
    Draw::WindCanvas::InitializeWindowList(&shapeList);
}
}
