#pragma once

#include<string>
#include<vector>

class IDataReader
{
public:
    virtual std::vector<unsigned char> ReadData(const std::string& filePath) = 0;
    virtual ~IDataReader() {};

protected:
    std::vector<unsigned char> data_;
};


