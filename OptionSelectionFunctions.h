#pragma once

class Counter;

int WriteWhatToDo();
void WriteDownToFileTriedPassword(std::string* current_vector_candidats_m, int start_index_in_array, const int& current_index, std::mutex& cur_mutex);
unsigned int SetNumberOfThreads();
void myReadFile(const std::string& filePath, std::vector<unsigned char>& buf);

std::string FreeFunctionToDecrypt(std::string* current_array_candidats_m, int start_index_in_array, const int& size_array_for_one_thread, const bool& write_cand_to_file, const std::vector<unsigned char>& text_from_file, std::shared_ptr<Counter> my_counter);