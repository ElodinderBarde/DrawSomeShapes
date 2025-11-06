#include "Tools/Manager/InputManager.h"

#include "../UI/WinCanvas.h"
#include "Data/Strings.h"
#include "SubMenuListDraw.h"
#include "Tools/Function.h"
#include "Types/Shapes/Circle.h"
#include "Types/Shapes/Ellipse.h"
#include "Types/Shapes/Line.h"
#include "Types/Shapes/Polygon.h"
#include "Types/Shapes/Polyline.h"
#include "Types/Shapes/Rectangle.h"

#include <iostream>

namespace Messerli::Tools::Manager
{

void InputManager::MainMenu()
{
    Function::StringOutput(Data::Menu::MenuHeader);
    Function::StringOutput(Data::Menu::MenuQuestionMode);
    Function::StringOutput(Data::Menu::MenuOptionPolyline + "\n");
    Function::StringOutput(Data::Menu::MenuOptionRectangle + "\n");
    Function::StringOutput(Data::Menu::MenuOptionCircle + "\n");
    Function::StringOutput(Data::Menu::MenuOptionEllipse + "\n");
    Function::StringOutput(Data::Menu::MenuOptionLine + "\n");
    Function::StringOutput(Data::Menu::MenuOptionPolygon + "\n");
    Function::StringOutput("7. Multiple Shapes \n");
    Function::StringOutput(Data::Menu::MenuOptionExit + "\n");

    std::string input;
    std::cin >> input;

    char prompt = GetChar(input);
    MainMenuSwitch(prompt);
}

void InputManager::MainMenuSwitch(char prompt)
{
    switch (prompt)
    {
    case '1': {

        SubMenuPolyline();

        break;
    }
    case '2': {
        SubMenuRectangle();

        break;
    }
    case '3': {
        SubMenuCircle();
        break;
    }
    case '4': {
        SubMenuEllipse();
        break;
    }
    case '5': {

        SubMenuLine();
        break;
    }
    case '6': {
        SubMenuPolygon();
        break;
    }
    case '7':
        SubMenuAddShapes();
        break;

    default: {

        Function::StringOutput("\nExiting Application...\n");
        exit(0);
        break;
    }
    }
}

void InputManager::SubMenuPolyline()
{
    Function::StringOutput(Data::Polyline::PolylineHeader);

    Function::StringOutput(Data::Polyline::PolylineDef);
    const int amountLines = GetInt(Data::Polyline::PolylineInput);

    if (amountLines < 2)
    {
        Function::StringOutput(Data::Polyline::PolylineReturnMessage);
        MainMenu();
        return;
    }

    double x, y;
    x = GetDouble("  x: ");
    y = GetDouble("  y: ");
    auto anchor = new Types::Point(x, y);

    auto* points = new Types::Point[amountLines];
    points[0] = *anchor;

    for (auto i = 1; i < amountLines; ++i)
    {
        Function::StringOutput("Enter the coordinates for point " + std::to_string(i + 1) + ":\n");
        x = GetDouble("  x: ");
        y = GetDouble("  y: ");
        points[i] = Types::Point(x, y);
    }

    auto polyline = new Types::Polyline(anchor, points[1]);
    for (auto i = 2; i < amountLines; ++i)
    {
        *polyline += points[i];
    }

    Function::StringOutput("\nYou created the following polyline:\n");
    Function::StringOutput(polyline->ToString() + "\n");
    Function::StringOutput(
        "Total Length: " + Function::TrimTrailingZeroKeepOne(std::to_string(polyline->GetTotalLength())) + "\n");

    Draw::WindCanvas::InitializeWindow(polyline);

    delete[] points;
    delete anchor;

    MainMenu();
}

void InputManager::SubMenuRectangle()
{
    Function::StringOutput(Data::Rectangle::RectangleHeader);
    Function::StringOutput(Data::Rectangle::RectangleDefinition + "\n");
    Function::StringOutput(Data::Rectangle::RectangleInput + "\n");

    double width = GetDouble(" Width: ");
    double height = GetDouble("Height: ");

    Function::StringOutput(Data::Rectangle::RectangleAnchorPos + "\n");
    double x = GetDouble("X: ");
    double y = GetDouble("Y: ");

    auto anchor = new Types::Point(x, y);

    auto* new_rectangle = new Types::Rectangle(*anchor, width, height);
    Draw::WindCanvas::InitializeWindow(new_rectangle);
    delete anchor;
    MainMenu();
}

void InputManager::SubMenuCircle()
{
    Function::StringOutput(Data::Circle::CircleHeader);
    Function::StringOutput(Data::Circle::CircleDefinition);
    Function::StringOutput(Data::Ellipse::EllipseMiddlePoint);

    double x = GetDouble("X: ");
    double y = GetDouble("Y: ");

    Function::StringOutput(Data::Circle::CircleRadient);

    double radient = GetDouble("Radient: ");

    auto anchor = new Types::Point(x, y);
    auto* new_circle = new Types::Circle(*anchor, radient);
    Draw::WindCanvas::InitializeWindow(new_circle);
    delete anchor;
    MainMenu();
}

void InputManager::SubMenuEllipse()
{
    Function::StringOutput(Data::Ellipse::EllipseHeader + "\n");
    Function::StringOutput(Data::Ellipse::EllipseDefinition + "\n");
    Function::StringOutput(Data::Ellipse::EllipseMiddlePoint + "\n");

    double x = GetDouble("x: ");
    double y = GetDouble("y: ");
    Function::StringOutput(Data::Ellipse::EllipseRadient + "\n");
    double a = GetDouble("a: ");
    double b = GetDouble("b: ");

    auto anchor = new Types::Point(x, y);
    auto* new_ellipse = new Types::Ellipse(*anchor, a, b);
    Draw::WindCanvas::InitializeWindow(new_ellipse);
    delete anchor;
    MainMenu();
}

void InputManager::SubMenuLine()
{
    Function::StringOutput(Data::Line::LineHeader);
    Function::StringOutput(Data::Line::LineDef);
    Function::StringOutput(Data::UniversalMenu::Enter);
    double x, y;
    x = GetDouble("  x: ");
    y = GetDouble("  y: ");
    auto anchor = new Types::Point(x, y);

    auto* Points = new Types::Point[2];
    Points[0] = *anchor;

    for (auto i = 0; i < 1; ++i)
    {
        Function::StringOutput(Data::UniversalMenu::EnterEndpoint + std::to_string(i + 2) + ":\n");
        x = GetDouble("  x: ");
        y = GetDouble("  y: ");
        Points[i + 1] = Types::Point(x, y);
    }

    auto line = new Types::Line(*anchor, Points[1]);
    for (auto i = 0; i < 2; ++i)
    {
        *line += Points[i];
    }
    Draw::WindCanvas::InitializeWindow(line);
    delete[] Points;
    delete anchor;

    MainMenu();
}

void InputManager::SubMenuPolygon()
{
    Function::StringOutput(Data::Polygon::PolygonHeader);
    Function::StringOutput(Data::Polygon::PolygonDefine);
    Function::StringOutput(Data::UniversalMenu::Enter);

    double x, y;
    x = GetDouble("  x: ");
    y = GetDouble("  y: ");

    Function::StringOutput(Data::Polygon::PolygonEdges);
    const int edges = GetInt("");
    if (edges < 3)
    {
        Function::StringOutput(Data::Polygon::PolygonReturnMessage);
        MainMenu();
        return;
    }

    auto anchor = new Types::Point(x, y);

    Function::StringOutput(Data::Polygon::PolygonSecondEdge);
    double x2 = GetDouble("  x: ");
    double y2 = GetDouble("  y: ");

    auto* points = new Types::Point[edges + 1];
    points[0] = *anchor;

    double dx = x2 - x;
    double dy = y2 - y;

    const double r = sqrt(dx * dx + dy * dy);
    const double startAngle = atan2(dy, dx);

    constexpr auto PI = 3.14159265358979323846;
    const double angleStep = 2 * PI / edges;

    for (auto i = 0; i < edges; ++i)
    {
        double angle = startAngle + i * angleStep;
        double newX = x + r * cos(angle);
        double newY = y + r * sin(angle);
        points[i] = Types::Point(newX, newY);
    }

    points[edges] = points[0];

    auto polygon = new Types::Polygon(points, edges + 1);

    std::cout << polygon->ToString() << std::endl;

    std::cout << "Ecken gesamt: " << polygon->GetCornerCount() << std::endl;
    std::cout << "Umfang gesamt: " << polygon->GetPerimeter() << std::endl;

    Draw::WindCanvas::InitializeWindow(polygon);

    delete[] points;
    delete anchor;

    MainMenu();
}

double InputManager::GetDouble(const std::string& prompt)
{
    double value;
    while (true)
    {
        std::cout << prompt;
        std::string input;
        std::cin >> input;
        try
        {
            size_t pos;
            value = std::stod(input, &pos);
            if (pos == input.length())
            {
                break;
            }
            std::cout << "Invalid input. Please enter a valid number.\n";
        }
        catch (const std::invalid_argument&)
        {
            std::cout << "Invalid input. Please enter a valid number.\n";
        }
        catch (const std::out_of_range&)
        {
            std::cout << "Input is out of range. Please enter a smaller number.\n";
        }
    }

    Function::StringOutput("\n");
    return value;
}

int InputManager::GetInt(const std::string& prompt)
{
    int value;
    while (true)
    {
        std::cout << prompt;
        std::string input;
        std::cin >> input;
        try
        {
            size_t pos;
            value = std::stoi(input, &pos);
            if (pos == input.length())
            {
                break; // Erfolgreiche Konvertierung
            }
            std::cout << "Invalid input. Please enter a valid integer.\n";
        }
        catch (const std::invalid_argument&)
        {
            std::cout << "Invalid input. Please enter a valid integer.\n";
        }
        catch (const std::out_of_range&)
        {
            std::cout << "Input is out of range. Please enter a smaller integer.\n";
        }
    }
    return value;
}

char InputManager::GetChar(const std::string& prompt)
{
    if (prompt.length() != 1)
    {
        std::cout << "Invalid input. Please enter a single character.\n";
        return '\0'; // oder eine andere Fehlerbehandlung
    }
    return prompt[0];
}

std::string InputManager::GetString(const std::string& prompt)
{
    std::string input;
    std::cout << prompt;
    std::cin >> input;
    return input;
}

}
