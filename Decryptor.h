#pragma once

class Decryptor
{
public:
	Decryptor(std::vector<unsigned char> chipher_text);	
	bool Decrypt(std::string& password);
	
private:
	unsigned char key_[EVP_MAX_KEY_LENGTH];
	unsigned char iv_[EVP_MAX_IV_LENGTH];

	std::vector<unsigned char> chipher_text_;
	std::vector<unsigned char> decrypt_text_;

	void PasswordToKey(std::string& password);
	bool CompareHASH(const std::vector<unsigned char>& hash1, const std::vector<unsigned char>& hash2);
	bool DecryptAes(const std::vector<unsigned char> plainText, std::vector<unsigned char>& chipherText);
	void WriteFile(const std::string& filePath, const std::vector<unsigned char>& buf);
	void CalculateHash(const std::vector<unsigned char>& data, std::vector<unsigned char>& hash);
};

