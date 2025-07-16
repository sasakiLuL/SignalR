#pragma once
#include <string>

using std::string;

namespace Api::Printer
{
	struct Column
	{
		Column(string text, string format);
		string Text;
		string Format;
	};
}



