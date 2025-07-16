#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <memory>
#include "../LexicalAnalysis/Lexer/Lexer.h"
#include "../LexicalAnalysis/Lexer/LexerConfiguration.h"
#include "../Core/Tables/Tables.h"
#include "Printer/Printer.h"
#include "../SyntacticAnalysis/Parser/Parser.h"

using
std::vector,
std::ifstream,
std::cout,
std::string,
LexicalAnalysis::Lexer::Lexer,
LexicalAnalysis::Lexer::LexerConfiguration,
SyntacticAnalysis::Parser,
Api::Printer::Printer;


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Compilation error: Path of file is required!");
        return EXIT_FAILURE;
    }

    ifstream stream = ifstream(argv[1], ifstream::binary);

    if (!stream.is_open())
    {
        printf("Compilation error: Wrong path of file or file is not exist!");
        return EXIT_FAILURE;
    }

    Tables tables = Tables();
    Printer printer = Printer(tables);
    
    auto lexerConfig = LexerConfiguration();
    lexerConfig.tabulationSize = 4;

    Lexer l = Lexer(tables, lexerConfig);

    auto lexerResult = l.Scan(stream);

    printer.PrintTables();
    printer.PrintLexems(lexerResult.first);
    printer.PrintErrors("Lexer", lexerResult.second);
    if (!lexerResult.second.empty())
    {
        return EXIT_SUCCESS;
    }

    Parser p = Parser(lexerResult.first);

    auto parserResult = p.Parse();

    printer.PrintTree(parserResult.first);
    printer.PrintErrors("Parser", parserResult.second);
    if (!parserResult.second.empty())
    {
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
