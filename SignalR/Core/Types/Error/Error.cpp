#include "Error.h"
#include <cstdint>

namespace Core::Types
{
    Error::Error(
        uint32_t line,
        uint32_t column,
        string code, 
        string message)
    {
        _line = line;
        _column = column;
        _code = code;
        _message = message;
    }
    uint32_t Error::getLine() const
    {
        return _line;
    }
    uint32_t Error::getColumn() const
    {
        return _column;
    }
    string Error::getCode() const
    {
        return _code;
    }
    string Error::getMessage() const
    {
        return _message;
    }
}
