#pragma once
#include <fstream>
#include <vector>
#include "../../Core/Types/Error/Error.h"
#include "../../Core/Types/Lexem/Lexem.h"
#include "../../Core/Types/Lexem/LexicalCategory.h"
#include "../../Core/Tables/Tables.h"
#include "LexerConfiguration.h"

using std::ifstream, std::vector, std::pair, Core::Tables;
using namespace Core::Types;

namespace LexicalAnalysis::Lexer
{
	class Lexer
	{
	public:
		Lexer(Tables& tables, LexerConfiguration config) : _tables(tables), _config(config) 
		{
            _attributes = array<LexicalCategory, 128>();

            // Initializing all characters like invalid
            for (int i = 0; i < 128; i++)
            {
                _attributes[i] = LexicalCategory::Illegal;
            }

            // Whitespace category
            for (int i = 8; i <= 13; i++)
            {
                _attributes[i] = LexicalCategory::Whitespace;
            }
            _attributes[32] = LexicalCategory::Whitespace;

            // Comments opener category
            _attributes[40] = LexicalCategory::CommentsOpener;

            // Delimiter category
            _attributes[44] = LexicalCategory::Delimiter;
            _attributes[46] = LexicalCategory::Delimiter;
            _attributes[92] = LexicalCategory::Delimiter;
            _attributes[59] = LexicalCategory::Delimiter;
            _attributes[61] = LexicalCategory::Delimiter;

            // Number category
            for (int i = 48; i <= 57; i++)
            {
                _attributes[i] = LexicalCategory::Number;
            }

            // Identifier category
            for (int i = 65; i <= 90; i++)
            {
                _attributes[i] = LexicalCategory::Identifier;
            }
            for (int i = 97; i <= 122; i++)
            {
                _attributes[i] = LexicalCategory::Identifier;
            }
		};
		pair<vector<Lexem>, vector<Error>> Scan(ifstream& stream);
	private:
		LexerConfiguration _config;
		array<LexicalCategory, 128> _attributes;
		Tables& _tables;
	};
}



