#pragma once
#include <vector>
#include <functional>
#include <memory>
#include "../../Core/Tables/Tables.h"
#include "../../Core/Types/Error/Error.h"
#include "../../Core/Types/Lexem/Lexem.h"
#include "../TreeNode/TreeNode.h"
#include "../SententialForm/SententialForm.h"

using std::vector, std::pair, std::function, std::unique_ptr;
using namespace Core::Types;
using ParseTreeNode = SyntacticAnalysis::TreeNode<SyntacticAnalysis::SententialForm>;

namespace SyntacticAnalysis
{
	class Parser
	{
	public:
		Parser(const vector<Lexem>& tokens);
		pair<unique_ptr<ParseTreeNode>, vector<Error>> Parse();
	private:
		vector<Lexem>::const_iterator _tokensIterator;
		vector<Lexem>::const_iterator _tokensEnd;
		vector<Error> _errors;

		bool scan();
		unique_ptr<ParseTreeNode> signalProgram();
		unique_ptr<ParseTreeNode> program();
		unique_ptr<ParseTreeNode> block();
		unique_ptr<ParseTreeNode> statementsList();
		unique_ptr<ParseTreeNode> declarations();
		unique_ptr<ParseTreeNode> mathFunctionDeclaration();
		unique_ptr<ParseTreeNode> functionList();
		unique_ptr<ParseTreeNode> function();
		unique_ptr<ParseTreeNode> functionCharacteristic();
		unique_ptr<ParseTreeNode> constant();
		unique_ptr<ParseTreeNode> procedureIdentifier();
		unique_ptr<ParseTreeNode> functionIdentifier();
		unique_ptr<ParseTreeNode> empty();
	};
}