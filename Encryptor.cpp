#include "stdafx.h"
#include "Encryptor.h"

void Encryptor::Encrypt()
{
    std::vector<unsigned char> plainText;
    myReadFile("my_file", plainText);
    std::vector<unsigned char> hash;
    CalculateHash(plainText, hash);
    std::vector<unsigned char> chipherText;
    EncryptAes(plainText, chipherText);
    WriteFile("my_crypto_file1", chipherText);
    AppendToFile("my_crypto_file1", hash);
}

void Encryptor::EncryptAes(const std::vector<unsigned char> plainText, std::vector<unsigned char>& chipherText)
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key_m, iv_m))
    {
        throw std::runtime_error("EncryptInit error");
    }
    std::vector<unsigned char> chipherTextBuf(plainText.size() + AES_BLOCK_SIZE);
    int chipherTextSize = 0;
    if (!EVP_EncryptUpdate(ctx, &chipherTextBuf[0], &chipherTextSize, &plainText[0], plainText.size())) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Encrypt error");
    }

    int lastPartLen = 0;
    if (!EVP_EncryptFinal_ex(ctx, &chipherTextBuf[0] + chipherTextSize, &lastPartLen)) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("EncryptFinal error");
    }
    chipherTextSize += lastPartLen;
    chipherTextBuf.erase(chipherTextBuf.begin() + chipherTextSize, chipherTextBuf.end());

    chipherText.swap(chipherTextBuf);

    EVP_CIPHER_CTX_free(ctx);
}

void Encryptor::myReadFile(const std::string& filePath, std::vector<unsigned char>& buf)
{
    std::basic_fstream<unsigned char> fileStream(filePath, std::ios::binary | std::fstream::in);
    if (!fileStream.is_open())
    {
        throw std::runtime_error("Can not open file " + filePath);
    }

    buf.clear();
    buf.insert(buf.begin(), std::istreambuf_iterator<unsigned char>(fileStream), std::istreambuf_iterator<unsigned char>());

    fileStream.close();
}

void Encryptor::WriteFile(const std::string& filePath, const std::vector<unsigned char>& buf)
{
    std::basic_ofstream<unsigned char> fileStream(filePath, std::ios::binary);
    fileStream.write(&buf[0], buf.size());
    fileStream.close();
}

void Encryptor::AppendToFile(const std::string& filePath, const std::vector<unsigned char>& buf)
{
    std::basic_ofstream<unsigned char> fileStream(filePath, std::ios::binary | std::ios::app);
    fileStream.write(&buf[0], buf.size());
    fileStream.close();
}

void Encryptor::PasswordToKey(std::string& password)
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

void Encryptor::CalculateHash(const std::vector<unsigned char>& data, std::vector<unsigned char>& hash)
{
    std::vector<unsigned char> hashTmp(SHA256_DIGEST_LENGTH);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, &data[0], data.size());
    SHA256_Final(&hashTmp[0], &sha256);

    hash.swap(hashTmp);
}

bool Encryptor::CompareHASH(const std::vector<unsigned char>& hash1, const std::vector<unsigned char>& hash2)
{
    return hash1 == hash2;
}

void Encryptor::setPassForCrypting()
{
    std::cout << "What pass we should use to crypt file?" << std::endl;
    std::cout << " Enter 1 - to enter your password, enter any else - to us default password"<<std::endl;
    std::string line_what_pass_to_use;
    std::cin >> line_what_pass_to_use;
    if (line_what_pass_to_use == "1")
    {
        std::cout << "Enter your password:";
        std::cin >> pass_for_crypting_m;
    }
    else
    {
        pass_for_crypting_m = "ww";
    }    
    PasswordToKey(pass_for_crypting_m);
}
