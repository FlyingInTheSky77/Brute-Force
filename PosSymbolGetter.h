#pragma once
#include "stdafx.h"
class PosSymbolGetter
{
public:
	void setPossibleSymbollsInVectorString();
	void setPossibleSymbollsInVectorString(std::string& line)
	{
		line = possible_symbolls_in_string_;
	}
	std::string getPossibleSymbollsInVectorString();
private:
	std::string possible_symbolls_in_string_;
};

