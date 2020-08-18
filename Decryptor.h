#pragma once

class Decryptor
{
public:
	Decryptor();
	bool CompareHASH(const std::vector<unsigned char>& hash1, const std::vector<unsigned char>& hash2);
	//methods from home task:
	bool Decrypt(std::vector<unsigned char> chipher_text);//change
	bool DecryptAes(const std::vector<unsigned char> plainText, std::vector<unsigned char>& chipherText);
	void WriteFile(const std::string& filePath, const std::vector<unsigned char>& buf);
	void AppendToFile(const std::string& filePath, const std::vector<unsigned char>& buf);
	void PasswordToKey(std::string& password);
	void CalculateHash(const std::vector<unsigned char>& data, std::vector<unsigned char>& hash);
private:
	unsigned char key_m[EVP_MAX_KEY_LENGTH];
	unsigned char iv_m[EVP_MAX_IV_LENGTH];
	unsigned int index_m;
	std::string current_pass_m;
};

