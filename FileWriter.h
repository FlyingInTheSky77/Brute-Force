#pragma once
#include "IDataWriter.h"
class FileWriter :
    public IDataWriter
{
public:
    virtual void WriteData(const std::string& filePath, const std::vector<unsigned char>& buf);
};

