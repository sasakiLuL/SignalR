#pragma once
#include <string>
#include <vector>
#include "Column/Column.h"
#include "Row/Row.h"
#include "../../Core/Types/Lexem/LexemType.h"
#include "../../Core/Types/Lexem/Lexem.h"
#include "../../SyntacticAnalysis/TreeNode/TreeNode.h"
#include "../../SyntacticAnalysis/SententialForm/SententialForm.h"
#include "../../Core/Tables/Tables.h"
#include "../../Core/Types/Error/Error.h"

using std::string, 
std::vector, 
SyntacticAnalysis::SententialForm, 
SyntacticAnalysis::TreeNode,
Core::Tables;

using namespace Core::Types;

namespace Api::Printer
{
	class Printer
	{
	public:
		Printer(const Tables& tables) : _tables(tables) {}
		void PrintTables();
		void PrintLexems(const vector<Lexem>& lexems);
		void PrintTree(const unique_ptr<TreeNode<SententialForm>>& root, uint64_t level = 0);
		void PrintErrors(const string& stage, const vector<Error>& errors);
	private:
		const Tables& _tables;
		string LexemTypeToString(LexemType type);
		string GetLexemString(Lexem lexem);
	};
}



