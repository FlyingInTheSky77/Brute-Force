#pragma once
#include <string>

class Counter;

void WriteDownToFileTriedPassword(std::string* current_vector_candidats_m, int start_index_in_array, const int& current_index, std::mutex& cur_mutex);
void myReadFile(const std::string& filePath, std::vector<unsigned char>& buf);

std::string FreeFunctionToDecrypt(std::string* current_array_candidats_m, int start_index_in_array, const int& size_array_for_one_thread, const bool& write_cand_to_file, const std::vector<unsigned char>& text_from_file, std::shared_ptr<Counter> my_counter);

class InitialDataChecker {
public:
	InitialDataChecker(const std::string& file_path, const std::string& isLog);
	bool isDataOkey() { return is_data_okey; }
	bool getLogStatus() { return is_log_; }
	std::string getFilePath() { return file_path_; }
	int WriteWhatToDoWithFile();

private:
	std::string file_path_;

	bool is_log_;
	bool is_data_okey;

	void tryOpenFile(const std::string& filePath);
	bool OpenFile(const std::string& filePath);
};