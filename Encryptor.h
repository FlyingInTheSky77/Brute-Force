#pragma once

class Encryptor
{
public:
	Encryptor(const std::string file_path);
	void Encrypt();
	void PasswordToKey(std::string& password);
	void setPassForCrypting();
	void start();

private:
	unsigned char key_m[EVP_MAX_KEY_LENGTH];
	unsigned char iv_m[EVP_MAX_IV_LENGTH];
	std::string pass_for_crypting_;
	std::string file_path_;
	std::string crypto_file_path_;
	std::vector<unsigned char> plainText_;
	std::vector<unsigned char> hash_;
	std::vector<unsigned char> chipherText_;

	void EncryptAes();
	void WriteFile();
	void AppendToFile();
	void CalculateHash();
};

