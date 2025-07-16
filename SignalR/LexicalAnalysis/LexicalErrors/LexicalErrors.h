#pragma once
#include "../../Core/Types/Error/Error.h"

using namespace Core::Types;

namespace LexicalAnalysis
{
	struct LexicalErrors
	{
		static Error WrongClosedComments(uint64_t line, uint64_t column, char currentChar);
		static Error NotClosedComments(uint64_t line, uint64_t column);
		static Error InvalidSymbol(uint64_t line, uint64_t column, char currentChar);
	};
}


