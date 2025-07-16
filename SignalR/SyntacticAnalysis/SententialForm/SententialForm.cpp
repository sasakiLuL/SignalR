#include "SententialForm.h"

#include <exception>

SyntacticAnalysis::SententialForm::SententialForm(const string& nodeInfo)
{
	_infoString = nodeInfo;
	_lexem = nullptr;
}

SyntacticAnalysis::SententialForm::SententialForm(const Lexem& lexem)
{
	_infoString = std::to_string(lexem.getCode()) + '-' + std::to_string((int)lexem.getType());
	_lexem = std::addressof(lexem);
}

string SyntacticAnalysis::SententialForm::getInfoString() const
{
	return _infoString;
}

const Lexem& SyntacticAnalysis::SententialForm::getLexem() const
{
	if (!isLexem())
	{
		throw std::exception::exception("Invalid operation: Cannot execute lexem from form");
	}
	return *_lexem;
}

bool SyntacticAnalysis::SententialForm::isLexem() const
{
	return _lexem != nullptr;
}
