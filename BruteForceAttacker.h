#pragma once

#include <mutex>
#include <thread>
#include "stdafx.h"
#include "Timer.h"
#include "Printer.h"

class BruteForceAttacker
{
public:
    BruteForceAttacker(bool is_log, unsigned int number_thread_and_decryptors, std::string file_path);
    void startDecrypt();
    void FunctionForPrintInThread(Counter& my_counter, Timer& my_timer);
    void StartAsyncThreadsWithDecriporInside(unsigned short int number_thread_and_decryptors_m, std::string* array_all_pos_pass, Counter& counter);

private:
    Timer timer_;
    unsigned int threads_number_;
    bool decrypt_status_;
    std::string password_that_opened_the_file_;
    bool is_log_{ false };
    std::vector<unsigned char> text_from_file_;
    int number_in_cycle_main_;
};

std::string FreeFunctionToDecrypt(std::string* current_array_candidats_m, int start_index_in_array, const int& size_array_for_one_thread, const bool is_log, const std::vector<unsigned char>& text_from_file, Counter& counter);