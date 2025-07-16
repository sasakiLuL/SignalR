#pragma once
#include "../../Core/Types/Error/Error.h"

using namespace Core::Types;

namespace SyntacticAnalysis
{
	struct SyntacticErrors
	{
		static Error ExpectedEndLine(uint64_t line, uint64_t column);
		static Error ExpectedDot(uint64_t line, uint64_t column);
		static Error ExpectedComa(uint64_t line, uint64_t column);
		static Error ExpectedBackslash(uint64_t line, uint64_t column);
		static Error ExpectedEqual(uint64_t line, uint64_t column);

		static Error ExpectedProgram(uint64_t line, uint64_t column);
		static Error ExpectedBegin(uint64_t line, uint64_t column);
		static Error ExpectedEnd(uint64_t line, uint64_t column);
		static Error ExpectedDeffunc(uint64_t line, uint64_t column);

		static Error OutsideBlock(uint64_t line, uint64_t column);
		static Error NotEmptyBlock(uint64_t line, uint64_t column);

		static Error ExpectedUnsignedInt(uint64_t line, uint64_t column);
		static Error ExpectedIdentifier(uint64_t line, uint64_t column);
	};
}