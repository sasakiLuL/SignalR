#include "LexicalErrors.h"

Error LexicalAnalysis::LexicalErrors::WrongClosedComments(uint64_t line, uint64_t column, char currentChar)
{
    return Error(
        line,
        column,
        "L1001",
        "expected a \'*\' but finded \'" + string(1, currentChar) + '\'');
}

Error LexicalAnalysis::LexicalErrors::NotClosedComments(uint64_t line, uint64_t column)
{
    return Error(
        line,
        column,
        "L1002",
        "comment unclosed at end of file");
}

Error LexicalAnalysis::LexicalErrors::InvalidSymbol(uint64_t line, uint64_t column, char currentChar)
{
    return Error(
        line,
        column,
        "L1003",
        "invalid symbol \'" + string(1, currentChar) + '\'');
}
