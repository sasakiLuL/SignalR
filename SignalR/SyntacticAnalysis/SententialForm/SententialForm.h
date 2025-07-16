#pragma once
#include <string>
#include "../../Core/Types/Lexem/Lexem.h"

using std::string;
using namespace Core::Types;

namespace SyntacticAnalysis
{
	class SententialForm
	{
	public:
		SententialForm(const string& nodeInfo);
		SententialForm(const Lexem& lexem);
		string getInfoString() const;
		const Lexem& getLexem() const;
		bool isLexem() const;
	private:
		string _infoString;
		const Lexem* _lexem;
	};
}