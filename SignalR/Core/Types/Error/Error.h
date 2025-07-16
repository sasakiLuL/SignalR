#pragma once
#include <string>
using std::string;

namespace Core::Types
{
    class Error
    {
        uint32_t _line;
        uint32_t _column;
        string _code;
        string _message;
    public:
        Error(
            uint32_t line,
            uint32_t column,
            string code, 
            string message);

        uint32_t getLine() const;

        uint32_t getColumn() const;

        string getCode() const;

        string getMessage() const;
    };
}