#pragma once

#include <mutex>
#include <thread>
#include "stdafx.h"
#include "Encryptor.h"
#include "Decryptor.h"
#include "Timer.h"
#include "Printer.h"

class BruteForceAttacker
{
public:
    BruteForceAttacker(bool write_passcandidate_to_file, unsigned int number_thread_and_decryptors, std::string file_path);
    void startDecrypt();
    void FunctionForPrintInThread(std::shared_ptr<Counter> my_counter, Timer my_timer);
    void StartAsyncThreadsWithDecriporInside(unsigned short int number_thread_and_decryptors_m, std::string* array_all_pos_pass, std::shared_ptr<Counter> my_counter);

private:
    Timer timer_;
    unsigned int number_thread_and_decryptors_m;
    bool decrypt_status_m;
    std::string password_that_opened_the_file_m;
    bool write_to_file_all_tried_passcandidate_m;
    std::string file_path_m;
    std::vector<unsigned char> text_from_file_m;
    int number_in_cycle_main_m;
};

std::string FreeFunctionToDecrypt(std::string* current_array_candidats_m, int start_index_in_array, const int& size_array_for_one_thread, const bool& write_cand_to_file, const std::vector<unsigned char>& text_from_file, std::shared_ptr<Counter> my_counter);