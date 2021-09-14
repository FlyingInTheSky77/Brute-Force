#include "FileReader.h"
#include <fstream>

std::vector<unsigned char> FileReader::ReadData(const std::string& filePath)
{
    std::basic_fstream<unsigned char> fileStream(filePath, std::ios::binary | std::fstream::in);
    if (!fileStream.is_open())
    {
        throw std::runtime_error("Can not open file " + filePath);
    }
    data_.clear();
    data_.insert(data_.begin(), std::istreambuf_iterator<unsigned char>(fileStream), std::istreambuf_iterator<unsigned char>());
    return data_;
}
