#include "stdafx.h"
#include "Encryptor.h"
#include "FileReader.h"
#include "FileWriter.h"

const std::string default_encryption_password{"www"};

const std::string crypto_file_name{"my_crypto_file1"};

Encryptor::Encryptor(const std::string file_path)
    : pass_for_crypting_ (default_encryption_password )
    , file_path_( file_path )
    , crypto_file_path_(crypto_file_name)
{}

void Encryptor::start() {
    try {
        setPassForCrypting();
        Encrypt();
    }
    catch (const std::runtime_error& ex) {
        std::cerr << ex.what();
    }
}

void Encryptor::Encrypt()
{
    std::unique_ptr<IDataReader> data_reader = std::make_unique<FileReader>();
    plainText_ = data_reader->ReadData(file_path_);
    CalculateHash();
    EncryptAes();
    std::unique_ptr<IDataWriter> data_writer = std::make_unique<FileWriter>();
    chipherText_.insert(chipherText_.end(), hash_.begin(), hash_.end());
    data_writer->WriteData(crypto_file_path_, chipherText_);
}

void Encryptor::EncryptAes()
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key_m, iv_m))
    {
        throw std::runtime_error("EncryptInit error");
    }
    std::vector<unsigned char> chipherTextBuf(plainText_.size() + AES_BLOCK_SIZE);
    int chipherTextSize = 0;
    if (!EVP_EncryptUpdate(ctx, &chipherTextBuf[0], &chipherTextSize, &plainText_[0], plainText_.size())) {
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

    chipherText_.swap(chipherTextBuf);

    EVP_CIPHER_CTX_free(ctx);
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

void Encryptor::CalculateHash()
{
    std::vector<unsigned char> hashTmp(SHA256_DIGEST_LENGTH);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    
    SHA256_Update(&sha256, &plainText_[0], plainText_.size());
    SHA256_Final(&hashTmp[0], &sha256);

    hash_.swap(hashTmp);
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
        std::cin >> pass_for_crypting_;
    }
    PasswordToKey(pass_for_crypting_);
}