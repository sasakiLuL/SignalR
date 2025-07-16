#include "Lexer.h"
#include "../../Core/Tables/Tables.h";
#include "../../LexicalAnalysis/LexicalErrors/LexicalErrors.h"

using std::string, LexicalAnalysis::LexicalErrors;

std::pair<vector<Lexem>, vector<Error>> LexicalAnalysis::Lexer::Lexer::Scan(ifstream& stream)
{
    uint64_t currentColumn = 1,
        currentLine = 1;
    uint8_t currentChar = stream.get();
    uint64_t lexemColumn, lexemLine;
    string buffer = "";
    vector<Lexem> lexems = {};
    vector<Error> errors = {};

    while (stream)
    {
        switch (_attributes[currentChar])
        {
        case LexicalCategory::Whitespace:
        {
            while (stream)
            {
                if (_attributes[currentChar] == LexicalCategory::Illegal)
                {
                    break;
                }

                if (_attributes[currentChar] != LexicalCategory::Whitespace)
                {
                    break;
                }

                if (currentChar == '\t')
                {
                    currentColumn += _config.tabulationSize;
                }
                else
                {
                    currentColumn++;
                }
                if (currentChar == '\n')
                {
                    currentLine++;
                    currentColumn = 1;
                }
                currentChar = stream.get();
            }
            break;
        }
        case LexicalCategory::Number:
        {
            lexemColumn = currentColumn;
            lexemLine = currentLine;
            while (stream)
            {
                if (_attributes[currentChar] == LexicalCategory::Illegal)
                {
                    break;
                }

                if (_attributes[currentChar] != LexicalCategory::Number)
                {
                    break;
                }
                buffer += currentChar;

                currentColumn++;
                currentChar = stream.get();
            }

            uint64_t code;

            auto constant = std::find(
                _tables.constants.begin(),
                _tables.constants.end(),
                buffer);

            if (constant != _tables.constants.end())
            {
                code = constant - _tables.constants.begin();
            }
            else
            {
                code = _tables.constants.size();
                _tables.constants.push_back(buffer);
            }

            lexems.push_back(Lexem(
                lexemLine,
                lexemColumn,
                code,
                LexemType::Constants));
            buffer.clear();
            break;
        }
        case LexicalCategory::Identifier:
        {
            lexemColumn = currentColumn;
            lexemLine = currentLine;
            while (stream)
            {
                if (_attributes[currentChar] == LexicalCategory::Illegal)
                {
                    break;
                }

                if (_attributes[currentChar] != LexicalCategory::Number &&
                    _attributes[currentChar] != LexicalCategory::Identifier)
                {
                    break;
                }
                buffer += currentChar;

                currentColumn++;
                currentChar = stream.get();
            }

            uint64_t code;
            LexemType type = LexemType::Identifier;

            auto keywordcode = std::find(
                _tables.keywords.begin(),
                _tables.keywords.end(),
                buffer);

            if (keywordcode != _tables.keywords.end())
            {
                code = keywordcode - _tables.keywords.begin();
                type = LexemType::Keyword;
            }
            else
            {
                auto identifier = std::find(
                    _tables.identifiers.begin(),
                    _tables.identifiers.end(),
                    buffer);

                if (identifier != _tables.identifiers.end())
                {
                    code = identifier - _tables.identifiers.begin();
                }
                else
                {
                    code = _tables.identifiers.size();
                    _tables.identifiers.push_back(buffer);
                }
            }

            lexems.push_back(Lexem(
                lexemLine,
                lexemColumn,
                code,
                type));
            buffer.clear();
            break;
        }
        case LexicalCategory::Delimiter:
        {
            lexems.push_back(Lexem(
                currentLine,
                currentColumn,
                std::find(
                    _tables.delimiters.begin(),
                    _tables.delimiters.end(),
                    string(1, currentChar)) - _tables.delimiters.begin(),
                LexemType::Delimiter));
            if (stream)
            {
                currentColumn++;
                currentChar = stream.get();
            }
            break;
        }
        case LexicalCategory::CommentsOpener:
        {
            currentColumn++;
            if (currentChar == '\n')
            {
                currentLine++;
                currentColumn = 1;
            }
            currentChar = stream.get();

            if (currentChar != '*')
            {
                errors.push_back(
                    LexicalErrors::WrongClosedComments(
                        currentLine, 
                        currentColumn, 
                        currentChar));
                break;
            }

            currentColumn++;
            if (currentChar == '\n')
            {
                currentLine++;
                currentColumn = 1;
            }
            currentChar = stream.get();

            while (stream)
            {
                if (currentChar == '*')
                {
                    while (stream)
                    {
                        if (currentChar == ')')
                        {
                            currentColumn++;
                            if (currentChar == '\n')
                            {
                                currentLine++;
                                currentColumn = 1;
                            }
                            currentChar = stream.get();
                            goto loopend;
                        }
                        if (currentChar != '*')
                        {
                            break;
                        }

                        currentColumn++;
                        if (currentChar == '\n')
                        {
                            currentLine++;
                            currentColumn = 1;
                        }
                        currentChar = stream.get();
                    }
                }

                currentColumn++;
                if (currentChar == '\n')
                {
                    currentLine++;
                    currentColumn = 1;
                }
                currentChar = stream.get();
            }
            if (!stream)
            {
                errors.push_back(
                    LexicalErrors::NotClosedComments(
                        currentLine, 
                        currentColumn));
            }
        loopend:
            break;
        }
        case LexicalCategory::Illegal:
        {
            errors.push_back(
                LexicalErrors::InvalidSymbol(
                    currentLine, 
                    currentColumn,
                    currentChar));
            if (stream)
            {
                currentColumn++;
                if (currentChar == '\n')
                {
                    currentLine++;
                    currentColumn = 1;
                }
                currentChar = stream.get();
            }
            break;
        }
        }
    }

    return { lexems, errors };
}

