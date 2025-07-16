#pragma once
#include <cstdint>
#include "LexemType.h"

namespace Core::Types
{
    class Lexem
    {
        uint64_t _line;
        uint64_t _column;
        uint64_t _code;
        LexemType _type;
    public:
        Lexem(
            uint64_t line, 
            uint64_t column, 
            uint64_t code, 
            LexemType type);

        uint64_t getLine() const;

        uint64_t getColumn() const;

        uint64_t getCode() const;

        LexemType getType() const;
    };
}
