#pragma once

#include<string>
#include<vector>

class IDataWriter
{
public:
    virtual void WriteData(const std::string& filePath, const std::vector<unsigned char>& buf) = 0;
    virtual ~IDataWriter() {};

};

