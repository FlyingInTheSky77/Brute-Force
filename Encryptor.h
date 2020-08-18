#pragma once

class Encryptor

{
public:
	void Encrypt();
	void EncryptAes(const std::vector<unsigned char> plainText, std::vector<unsigned char>& chipherText);
	void myReadFile(const std::string& filePath, std::vector<unsigned char>& buf);
	void WriteFile(const std::string& filePath, const std::vector<unsigned char>& buf);
	void AppendToFile(const std::string& filePath, const std::vector<unsigned char>& buf);
	void PasswordToKey(std::string& password);
	void CalculateHash(const std::vector<unsigned char>& data, std::vector<unsigned char>& hash);
	bool CompareHASH(const std::vector<unsigned char>& hash1, const std::vector<unsigned char>& hash2);
	void setPassForCrypting();
private:
	unsigned char key_m[EVP_MAX_KEY_LENGTH];
	unsigned char iv_m[EVP_MAX_IV_LENGTH];
	std::string pass_for_crypting_m;
};

