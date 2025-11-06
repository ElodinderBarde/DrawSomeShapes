#pragma once
#include "Data/Strings.h"

#include <string>

namespace Messerli::Tools
{

struct Function
{
    static void InitializeApp();

    static void StringOutput(const std::string& str);

    static std::string TrimTrailingZeroKeepOne(std::string str);
};

}
