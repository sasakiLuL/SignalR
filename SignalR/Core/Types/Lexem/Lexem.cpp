#include "Lexem.h"

namespace Core::Types
{
    Lexem::Lexem(
        uint64_t line, 
        uint64_t column, 
        uint64_t code, 
        LexemType type)
    {
        _line = line;
        _column = column;
        _code = code;
        _type = type;
    }

    uint64_t Lexem::getLine()
        const
    {
        return _line;
    }

    uint64_t Lexem::getColumn()
        const
    {
        return _column;
    }

    uint64_t Lexem::getCode()
        const
    {
        return _code;
    }

    LexemType Lexem::getType()
        const
    {
        return _type;
    }
}
