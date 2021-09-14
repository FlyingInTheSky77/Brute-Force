#pragma once
#include "IDataReader.h"

class FileReader : public IDataReader
{
public:
	std::vector<unsigned char> ReadData(const std::string& filePath);
};

