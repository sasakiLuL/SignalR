#pragma once
#include <vector>
#include <array>
#include <string>
using std::vector, std::array, std::string;

namespace Core
{
    struct Tables
    {
        Tables();

        array<string, 4> keywords;

        array<string, 5> delimiters;

        vector<string> identifiers;

        vector<string> constants;
    };
}