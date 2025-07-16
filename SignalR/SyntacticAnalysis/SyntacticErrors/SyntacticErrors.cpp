#include "SyntacticErrors.h"

Error SyntacticAnalysis::SyntacticErrors::ExpectedEndLine(uint64_t line, uint64_t column)
{
    return Error(
        line,
        column,
        "S1001",
        "expected a \';\'");
}

Error SyntacticAnalysis::SyntacticErrors::ExpectedDot(uint64_t line, uint64_t column)
{
    return Error(
        line,
        column,
        "S1002",
        "expected a \'.\'");
}

Error SyntacticAnalysis::SyntacticErrors::ExpectedComa(uint64_t line, uint64_t column)
{
    return Error(
        line,
        column,
        "S1003",
        "expected a \',\'");
}

Error SyntacticAnalysis::SyntacticErrors::ExpectedBackslash(uint64_t line, uint64_t column)
{
    return Error(
        line,
        column,
        "S1004",
        "expected a \'\\\'");
}

Error SyntacticAnalysis::SyntacticErrors::ExpectedEqual(uint64_t line, uint64_t column)
{
    return Error(
        line,
        column,
        "S1005",
        "expected a \'=\'");
}


Error SyntacticAnalysis::SyntacticErrors::ExpectedProgram(uint64_t line, uint64_t column)
{
    return Error(
        line,
        column,
        "S1006",
        "expected a keyword \'PROGRAM\'");
}

Error SyntacticAnalysis::SyntacticErrors::ExpectedBegin(uint64_t line, uint64_t column)
{
    return Error(
        line,
        column,
        "S1007",
        "expected a keyword \'BEGIN\'");
}

Error SyntacticAnalysis::SyntacticErrors::ExpectedEnd(uint64_t line, uint64_t column)
{
    return Error(
        line,
        column,
        "S1008",
        "expected a keyword \'END\'");
}

Error SyntacticAnalysis::SyntacticErrors::ExpectedDeffunc(uint64_t line, uint64_t column)
{
    return Error(
        line,
        column,
        "S1009",
        "expected a keyword \'DEFFUNC\'");
}


Error SyntacticAnalysis::SyntacticErrors::NotEmptyBlock(uint64_t line, uint64_t column)
{
    return Error(
        line,
        column,
        "S1010",
        "statements are in block");
}

Error SyntacticAnalysis::SyntacticErrors::OutsideBlock(uint64_t line, uint64_t column)
{
    return Error(
        line,
        column,
        "S1011",
        "statements are outside the block");
}


Error SyntacticAnalysis::SyntacticErrors::ExpectedUnsignedInt(uint64_t line, uint64_t column)
{
    return Error(
        line,
        column,
        "S1012",
        "expected constant of the type <unsigned-integer>");
}

Error SyntacticAnalysis::SyntacticErrors::ExpectedIdentifier(uint64_t line, uint64_t column)
{
    return Error(
        line,
        column,
        "S1013",
        "expected an identifier");
}