#include "Tools/Function.h"

#include "..//UI/WinCanvas.h"
#include "Tools/Manager/InputManager.h"

#include <iostream>
#include <windows.h>

namespace Messerli::Tools
{
void Function::InitializeApp()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Manager::InputManager::MainMenu();

    std::wcout << L"App wird initialisiert..." << std::endl;
    Manager::InputManager::MainMenu();

    std::wcout << L" Fenster geschlossen -> Programmende" << std::endl;
}

void Function::StringOutput(const std::string& str)
{
    std::cout << str;
}

std::string Function::TrimTrailingZeroKeepOne(std::string str)
{

    std::size_t dotPos = str.find('.');
    if (dotPos == std::string::npos)
    {
        return str;
    }
    std::size_t lastNonZeroPos = str.find_last_not_of('0');
    if (lastNonZeroPos == std::string::npos || lastNonZeroPos < dotPos)
    {
        return str.substr(0, dotPos);
    }

    if (lastNonZeroPos == dotPos)
    {
        lastNonZeroPos++;
    }
    return str.substr(0, lastNonZeroPos + 1);
}
}
