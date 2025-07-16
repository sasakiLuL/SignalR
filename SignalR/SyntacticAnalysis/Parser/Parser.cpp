#include "Parser.h"
#include <string>
#include "../../Core/Types/Lexem/LexemType.h"
#include "../../Core/Types/Lexem/LexicalCategory.h"
#include "../../SyntacticAnalysis/SententialForm/SententialForm.h"
#include "../../SyntacticAnalysis/SyntacticErrors/SyntacticErrors.h"

using
	std::make_unique,
	std::to_string, 
	SyntacticAnalysis::SententialForm,
	SyntacticAnalysis::SyntacticErrors;

namespace SyntacticAnalysis
{
	Parser::Parser(const vector<Lexem>& tokens)
	{
		_tokensIterator = tokens.begin();
		_tokensEnd = tokens.end();
		_errors = {};
	}

	bool Parser::scan()
	{
		if (_tokensIterator + 1 != _tokensEnd)
		{
			_tokensIterator++;
			return true;
		}

		return false;
	}

	pair<unique_ptr<ParseTreeNode>, vector<Error>> Parser::Parse()
	{
		return pair(
			signalProgram(),
			_errors);
	}

	unique_ptr<ParseTreeNode> Parser::signalProgram()
	{
		auto node = make_unique<ParseTreeNode>(SententialForm("<signal-program>"));

		node->insert(program());

		return node;
	}

	unique_ptr<ParseTreeNode> Parser::program()
	{
		auto program = make_unique<ParseTreeNode>(
			SententialForm("<program>"));

		if (_tokensIterator->getType() != LexemType::Keyword ||
			_tokensIterator->getCode() != 0) // PROGRAM
		{
			_errors.push_back(
				SyntacticErrors::ExpectedProgram(
					_tokensIterator->getLine(),
					_tokensIterator->getColumn()));

			program->insert(
				make_unique<ParseTreeNode>(
					SententialForm("<error>")));
		}
		else
		{
			program->insert(
				make_unique<ParseTreeNode>(*_tokensIterator));
		}

		scan();
		program->insert(procedureIdentifier());

		scan();
		if (_tokensIterator->getType() != LexemType::Delimiter ||
			_tokensIterator->getCode() != 0) // ;
		{
			_errors.push_back(
				SyntacticErrors::ExpectedEndLine(
					_tokensIterator->getLine(), 
					_tokensIterator->getColumn()));

			program->insert(
				make_unique<ParseTreeNode>(
					SententialForm("<error>")));
		}
		else
		{
			program->insert(
				make_unique<ParseTreeNode>(SententialForm(*_tokensIterator)));
			scan();
		}

		program->insert(block());

		scan();
		if (_tokensIterator->getType() != LexemType::Delimiter ||
			_tokensIterator->getCode() != 1) // .
		{
			_errors.push_back(
				SyntacticErrors::ExpectedDot(
					_tokensIterator->getLine(),
					_tokensIterator->getColumn()));

			program->insert(
				make_unique<ParseTreeNode>(
					SententialForm("<error>")));
		}
		else
		{
			program->insert(
				make_unique<ParseTreeNode>(SententialForm(*_tokensIterator)));
		}

		scan();
		if (++_tokensIterator != _tokensEnd)
		{
			_errors.push_back(
				SyntacticErrors::OutsideBlock(
					_tokensIterator->getLine(),
					_tokensIterator->getColumn()));

			program->insert(
				make_unique<ParseTreeNode>(
					SententialForm("<error>")));
		}

		return program;
	}

	unique_ptr<ParseTreeNode> Parser::block()
	{
		auto block = make_unique<ParseTreeNode>(SententialForm("<block>"));

		block->insert(declarations());

		if (_tokensIterator->getType() != LexemType::Keyword ||
			_tokensIterator->getCode() != 1) // BEGIN
		{
			_errors.push_back(
				SyntacticErrors::ExpectedBegin(
					_tokensIterator->getLine(),
					_tokensIterator->getColumn()));

			block->insert(
				make_unique<ParseTreeNode>(
					SententialForm("<error>")));
		}
		else
		{
			block->insert(
				make_unique<ParseTreeNode>(SententialForm(*_tokensIterator)));
		}

		scan();
		block->insert(statementsList());

		if (_tokensIterator->getType() != LexemType::Keyword ||
			_tokensIterator->getCode() != 2) // END
		{
			_errors.push_back(
				SyntacticErrors::ExpectedEnd(
					_tokensIterator->getLine(),
					_tokensIterator->getColumn()));

			block->insert(
				make_unique<ParseTreeNode>(
					SententialForm("<error>")));
		}
		else
		{
			block->insert(
				make_unique<ParseTreeNode>(SententialForm(*_tokensIterator)));
		}

		return block;
	}

	unique_ptr<ParseTreeNode> Parser::statementsList()
	{
		auto statementsList = make_unique<ParseTreeNode>(
			SententialForm("<statements-list>"));

		if (_tokensIterator->getType() != LexemType::Keyword ||
			_tokensIterator->getCode() != 2) // END
		{
			_errors.push_back(
				SyntacticErrors::NotEmptyBlock(
					_tokensIterator->getLine(),
					_tokensIterator->getColumn()));

			statementsList->insert(
				make_unique<ParseTreeNode>(
					SententialForm("<error>")));
		}
		else
		{
			statementsList->insert(empty());
		}

		return statementsList;
	}

	unique_ptr<ParseTreeNode> Parser::declarations()
	{
		auto declarations = make_unique<ParseTreeNode>(
			SententialForm("<declarations>"));

		declarations->insert(mathFunctionDeclaration());

		return declarations;
	}

	unique_ptr<ParseTreeNode> Parser::mathFunctionDeclaration()
	{
		auto mathFunctionDeclaration = make_unique<ParseTreeNode>(
			SententialForm("<math-function-declarations>"));

		if (_tokensIterator->getType() != LexemType::Keyword)
		{
			_errors.push_back(
					SyntacticErrors::ExpectedDeffunc(
						_tokensIterator->getLine(),
						_tokensIterator->getColumn()));

			mathFunctionDeclaration->insert(
				make_unique<ParseTreeNode>(
					SententialForm("<error>")));
		}
		
		if (_tokensIterator->getCode() == 3) // DEFFUNC
		{
			scan();
			mathFunctionDeclaration->insert(functionList());
		} 
		else if (_tokensIterator->getCode() == 1) // BEGIN
		{
			mathFunctionDeclaration->insert(empty());
		}

		return mathFunctionDeclaration;
	}

	unique_ptr<ParseTreeNode> Parser::functionList()
	{
		auto functionList = make_unique<ParseTreeNode>(
			SententialForm("<function-list>"));

		if (_tokensIterator->getType() == LexemType::Keyword &&
			_tokensIterator->getCode() == 1) // BEGIN
		{
			functionList->insert(empty());
			return functionList;
		}
		
		functionList->insert(function());

		while ((_tokensIterator->getType() != LexemType::Keyword ||
			_tokensIterator->getCode() != 1) && 
			_tokensIterator + 1 != _tokensEnd) // BEGIN
		{
			functionList->insert(function());
		}
		
		return functionList;
	}

	unique_ptr<ParseTreeNode> Parser::function()
	{
		auto function = make_unique<ParseTreeNode>(
			SententialForm("<function>"));

		function->insert(functionIdentifier());

		scan();
		if (_tokensIterator->getType() != LexemType::Delimiter ||
			_tokensIterator->getCode() != 2) // =
		{
			_errors.push_back(
				SyntacticErrors::ExpectedEqual(
					_tokensIterator->getLine(),
					_tokensIterator->getColumn()));

			function->insert(
				make_unique<ParseTreeNode>(
					SententialForm("<error>")));
		}
		else
		{
			function->insert(
				make_unique<ParseTreeNode>(SententialForm(*_tokensIterator)));
		}

		scan();
		function->insert(constant());

		scan();
		function->insert(functionCharacteristic());

		scan();
		if (_tokensIterator->getType() != LexemType::Delimiter ||
			_tokensIterator->getCode() != 0) // ;
		{
			_errors.push_back(
				SyntacticErrors::ExpectedEndLine(
					_tokensIterator->getLine(),
					_tokensIterator->getColumn()));

			function->insert(
				make_unique<ParseTreeNode>(
					SententialForm("<error>")));
		}
		else
		{
			function->insert(
				make_unique<ParseTreeNode>(SententialForm(*_tokensIterator)));
			scan();
		}

		return function;
	}

	unique_ptr<ParseTreeNode> Parser::functionCharacteristic() 
	{
		auto functionCharacteristic = make_unique<ParseTreeNode>(
			SententialForm("<function-characteristic>"));

		if (_tokensIterator->getType() != LexemType::Delimiter ||
			_tokensIterator->getCode() != 3) // /
		{
			_errors.push_back(
				SyntacticErrors::ExpectedBackslash(
					_tokensIterator->getLine(),
					_tokensIterator->getColumn()));

			functionCharacteristic->insert(
				make_unique<ParseTreeNode>(
					SententialForm("<error>")));
		}
		else
		{
			functionCharacteristic->insert(
				make_unique<ParseTreeNode>(SententialForm(*_tokensIterator)));
		}

		scan();
		if (_tokensIterator->getType() != LexemType::Constants) // unsigned-integer
		{
			_errors.push_back(
				SyntacticErrors::ExpectedUnsignedInt(
					_tokensIterator->getLine(),
					_tokensIterator->getColumn()));

			functionCharacteristic->insert(
				make_unique<ParseTreeNode>(
					SententialForm("<error>")));
		}
		else
		{
			functionCharacteristic->insert(
				make_unique<ParseTreeNode>(SententialForm(*_tokensIterator)));
		}

		scan();
		if (_tokensIterator->getType() != LexemType::Delimiter ||
			_tokensIterator->getCode() != 4) // ,
		{
			_errors.push_back(
				SyntacticErrors::ExpectedComa(
					_tokensIterator->getLine(),
					_tokensIterator->getColumn()));

			functionCharacteristic->insert(
				make_unique<ParseTreeNode>(
					SententialForm("<error>")));
		}
		else
		{
			functionCharacteristic->insert(
				make_unique<ParseTreeNode>(SententialForm(*_tokensIterator)));
		}

		scan();
		if (_tokensIterator->getType() != LexemType::Constants) // unsigned-integer
		{
			_errors.push_back(
				SyntacticErrors::ExpectedUnsignedInt(
					_tokensIterator->getLine(),
					_tokensIterator->getColumn()));

			functionCharacteristic->insert(
				make_unique<ParseTreeNode>(
					SententialForm("<error>")));
		}
		else
		{
			functionCharacteristic->insert(
				make_unique<ParseTreeNode>(SententialForm(*_tokensIterator)));
		}

		return functionCharacteristic;
	}

	unique_ptr<ParseTreeNode> Parser::constant()
	{
		auto constant = make_unique<ParseTreeNode>(SententialForm("<constant>"));

		if (_tokensIterator->getType() != LexemType::Constants) // unsigned-integer
		{
			_errors.push_back(
				SyntacticErrors::ExpectedUnsignedInt(
					_tokensIterator->getLine(),
					_tokensIterator->getColumn()));

			constant->insert(
				make_unique<ParseTreeNode>(
					SententialForm("<error>")));
		}
		else
		{
			constant->insert(
				make_unique<ParseTreeNode>(
					SententialForm(*_tokensIterator)));
		}

		return constant;
	}

	unique_ptr<ParseTreeNode> Parser::procedureIdentifier()
	{
		auto procedureIdentifier = make_unique<ParseTreeNode>(
			SententialForm("<procedure-identifier>"));

		if (_tokensIterator->getType() != LexemType::Identifier) // identifier
		{
			_errors.push_back(
				SyntacticErrors::ExpectedIdentifier(
					_tokensIterator->getLine(),
					_tokensIterator->getColumn()));

			procedureIdentifier->insert(
				make_unique<ParseTreeNode>(
					SententialForm("<error>")));
		}
		else
		{
			procedureIdentifier->insert(
				make_unique<ParseTreeNode>(SententialForm(*_tokensIterator)));
		}

		return procedureIdentifier;
	}

	unique_ptr<ParseTreeNode> Parser::functionIdentifier()
	{
		auto functionIdentifier = make_unique<ParseTreeNode>(
			SententialForm("<function-identifier>"));

		if (_tokensIterator->getType() != LexemType::Identifier) // unsigned-integer
		{
			_errors.push_back(
				SyntacticErrors::ExpectedIdentifier(
					_tokensIterator->getLine(),
					_tokensIterator->getColumn()));

			functionIdentifier->insert(
				make_unique<ParseTreeNode>(
					SententialForm("<error>")));
		}
		else
		{
			functionIdentifier->insert(
				make_unique<ParseTreeNode>(SententialForm(*_tokensIterator)));
		}

		return functionIdentifier;
	}

	unique_ptr<ParseTreeNode> Parser::empty()
	{
		auto empty = make_unique<ParseTreeNode>(SententialForm("<empty>"));

		return empty;
	}
}


