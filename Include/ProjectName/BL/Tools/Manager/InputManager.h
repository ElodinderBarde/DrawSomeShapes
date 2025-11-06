#pragma once
#include <string>

namespace Messerli::Tools::Manager
{
class InputManager
{
  public:
    static void MainMenu();

    static void MainMenuSwitch(char prompt);

    static void SubMenuPolyline();

    static void SubMenuRectangle();

    static void SubMenuCircle();

    static void SubMenuTriangle();

    static void SubMenuEllipse();

    static void SubMenuLine();

    static void SubMenuPolygon();

    static double GetDouble(const std::string& prompt);

    static int GetInt(const std::string& prompt);

    static char GetChar(const std::string& prompt);

    static std::string GetString(const std::string& prompt);
};
}
