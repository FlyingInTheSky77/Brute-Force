#include "stdafx.h"
#include "OptionSelectionFunctions.h"
#include "Decryptor.h"
#include <chrono>


Decryptor::Decryptor()
{};
bool Decryptor::Decrypt(std::vector<unsigned char> chipher_text)
{
    std::vector<unsigned char> hashFromCryptoFile;
    std::vector<unsigned char> hashDecryptoFile;
    for (unsigned int i = 0; i < chipher_text.size(); ++i)
    {
        if (i >= (chipher_text.size() - 32))
        {
            hashFromCryptoFile.push_back(chipher_text[i]);
        }
    }
    chipher_text.resize(chipher_text.size() - hashFromCryptoFile.size());
    std::vector<unsigned char> DecryptText;
    if (DecryptAes(chipher_text, DecryptText))
    {
        CalculateHash(DecryptText, hashDecryptoFile);
        if (!CompareHASH(hashFromCryptoFile, hashDecryptoFile))
        {
            return false;//"Password is wrong!..."
        }
        WriteFile("my_decrypto_file1", DecryptText);
        return true;
    }
    else
    {
        return false;
    }
}


bool Decryptor::DecryptAes(const std::vector<unsigned char> plainText, std::vector<unsigned char>& chipherText)
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key_m, iv_m))
    {
        return false;
    }
    std::vector<unsigned char> chipherTextBuf(plainText.size() + AES_BLOCK_SIZE);
    int chipherTextSize = 0;
    if (!EVP_DecryptUpdate(ctx, &chipherTextBuf[0], &chipherTextSize, &plainText[0], plainText.size())) 
    {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    int lastPartLen = 0;
    if (!EVP_DecryptFinal_ex(ctx, &chipherTextBuf[0] + chipherTextSize, &lastPartLen)) 
    {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    chipherTextSize += lastPartLen;
    chipherTextBuf.erase(chipherTextBuf.begin() + chipherTextSize, chipherTextBuf.end());

    chipherText.swap(chipherTextBuf);

    EVP_CIPHER_CTX_free(ctx);
    return true;
}


void Decryptor::WriteFile(const std::string& filePath, const std::vector<unsigned char>& buf)
{
    std::basic_ofstream<unsigned char> fileStream(filePath, std::ios::binary);
    fileStream.write(&buf[0], buf.size());
}

void Decryptor::AppendToFile(const std::string& filePath, const std::vector<unsigned char>& buf)
{
    std::basic_ofstream<unsigned char> fileStream(filePath, std::ios::binary | std::ios::app);
    fileStream.write(&buf[0], buf.size());
}

void Decryptor::PasswordToKey(std::string& password)
{
    const EVP_MD* dgst = EVP_get_digestbyname("md5");
    if (!dgst)
    {
        throw std::runtime_error("no such digest");
    }
    const unsigned char* salt = NULL;
    if (!EVP_BytesToKey(EVP_aes_128_cbc(), EVP_md5(), salt,
        reinterpret_cast<unsigned char*>(&password[0]),
        password.size(), 1, key_m, iv_m))
    {
        throw std::runtime_error("EVP_BytesToKey failed");
    }
}

void Decryptor::CalculateHash(const std::vector<unsigned char>& data, std::vector<unsigned char>& hash)
{
    std::vector<unsigned char> hashTmp(SHA256_DIGEST_LENGTH);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, &data[0], data.size());
    SHA256_Final(&hashTmp[0], &sha256);
    hash.swap(hashTmp);
}

bool Decryptor::CompareHASH(const std::vector<unsigned char>& hash1, const std::vector<unsigned char>& hash2)
{
    return hash1 == hash2;
}

