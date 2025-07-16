#include "Printer.h"
#include "../../Core/Tables/Tables.h"
#include <iostream>

using std::cout, std::printf;

string Api::Printer::Printer::LexemTypeToString(LexemType type)
{
    switch (type)
    {
    case LexemType::Constants:
        return "Constants";
        break;
    case LexemType::Delimiter:
        return "Delimiter";
        break;
    case LexemType::Identifier:
        return "Identifier";
        break;
    case LexemType::Keyword:
        return "Keyword";
        break;
    }
}

string Api::Printer::Printer::GetLexemString(Lexem lexem)
{
    switch (lexem.getType())
    {
    case LexemType::Constants:
        return _tables.constants[lexem.getCode()];
        break;
    case LexemType::Delimiter:
        return _tables.delimiters[lexem.getCode()];
        break;
    case LexemType::Identifier:
        return _tables.identifiers[lexem.getCode()];
        break;
    case LexemType::Keyword:
        return _tables.keywords[lexem.getCode()];
        break;
    }
}

void Api::Printer::Printer::PrintTables()
{
    cout << "Keywords table:\n";
    printf(
        "+----------+----------+\n|%10s|%10s|\n+----------+----------+\n",
        "Keyword",
        "Code");
    for (int i = 0; i < _tables.keywords.size(); i++)
    {
        printf(
            "|%10s|%10d|\n",
            _tables.keywords[i].c_str(),
            i);
    }
    cout << "+----------+----------+\n";
    cout << '\n';

    cout << "Identifiers table:\n";
    printf(
        "+--------------------+----------+\n|%20s|%10s|\n+--------------------+----------+\n",
        "Identifier",
        "Code");
    for (int i = 0; i < _tables.identifiers.size(); i++)
    {
        printf(
            "|%20s|%10d|\n",
            _tables.identifiers[i].c_str(),
            i);
    }
    cout << "+--------------------+----------+\n";
    cout << '\n';

    cout << "Constants table:\n";
    printf(
        "+--------------------+----------+\n|%20s|%10s|\n+--------------------+----------+\n",
        "Constant",
        "Code");
    for (int i = 0; i < _tables.constants.size(); i++)
    {
        printf(
            "|%20s|%10d|\n",
            _tables.constants[i].c_str(),
            i);
    }
    cout << "+--------------------+----------+\n";
    cout << '\n';

    cout << "Delimiters table:\n";
    printf(
        "+----------+----------+\n|%10s|%10s|\n+----------+----------+\n",
        "Delimiter",
        "Code");
    for (int i = 0; i < _tables.delimiters.size(); i++)
    {
        printf(
            "|%10s|%10d|\n",
            _tables.delimiters[i].c_str(),
            i);
    }
    cout << "+----------+----------+\n";
    cout << '\n';
}

void Api::Printer::Printer::PrintLexems(const vector<Lexem>& lexems)
{
    cout << "Lexems string:\n";
    printf(
        "+----------+----------+----------+---------------+---------------+\n|%10s|%10s|%10s|%15s|%15s|\n+----------+----------+----------+---------------+---------------+\n",
        "Line",
        "Column",
        "Code",
        "Lexem type",
        "Lexem");
    for (const auto& lexem : lexems)
    {
        printf(
            "|%10d|%10d|%10d|%15s|%15s|\n",
            lexem.getLine(),
            lexem.getColumn(),
            lexem.getCode(),
            LexemTypeToString(lexem.getType()).c_str(),
            GetLexemString(lexem).c_str());
    }
    cout << "+----------+----------+----------+---------------+---------------+\n";
    cout << '\n';
}

void Api::Printer::Printer::PrintTree(const unique_ptr<TreeNode<SententialForm>>& root, uint64_t level)
{
    string gap = "";

    for (int i = 0; i < level; i++)
        gap += "|   ";

    if (root == nullptr)
        return;

    cout << gap << root->getData().getInfoString() + "  ";

    if (root->getData().isLexem())
    {
        cout << GetLexemString(root->getData().getLexem());
    }

    cout << '\n';

    for (const auto& leaf : root->getBranches())
    {
        level++;
        PrintTree(leaf, level);
        level--;
    }
}

void Api::Printer::Printer::PrintErrors(const string& stage, const vector<Error>& errors)
{
    cout << (errors.empty() ? "" : stage + " errors:\n");
    for (const auto& error : errors)
    {
        printf(
            "\t%s: Error %s (line: %d, column: %d): %s\n",
            stage.c_str(),
            error.getCode().c_str(),
            error.getLine(),
            error.getColumn(),
            error.getMessage().c_str());
    }
    cout << '\n';
}
