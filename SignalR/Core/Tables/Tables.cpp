#include "Tables.h"

namespace Core
{
    Tables::Tables()
    {
        constants = {};
        identifiers = {};
        delimiters =
        {
                ";",
                ".",
                "=",
                "\\",
                ",",
        };
        keywords =
        {
                "PROGRAM",
                "BEGIN",
                "END",
                "DEFFUNC",
        };
    }
}