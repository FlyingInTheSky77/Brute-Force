#include "PosSymbolGetter.h"

//PosSymbolGetter

void PosSymbolGetter::setPossibleSymbollsInVectorString()
{
    for (unsigned int i = 0; i < 10; i++)
    {
        possible_symbolls_in_string_ += std::to_string(i);
    }
    char letterS = 'a';
    for (char letterS = 'a'; letterS != '{'; letterS++)
    {
        std::string temp(1, letterS);
        possible_symbolls_in_string_ += temp;
    }
}

std::string PosSymbolGetter::getPossibleSymbollsInVectorString()
{
    return possible_symbolls_in_string_;
}