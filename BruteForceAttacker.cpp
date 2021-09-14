#include "stdafx.h"
#include "BruteForceAttacker.h"
#include "Decryptor.h"
#include "Encryptor.h"
#include "InitialDataChecker.h"
#include "PassGenerateFunction.h"
#include <thread>
#include "Counter.h"
#include "FileReader.h"
#include <memory>

const int number_of_candidate_passwords_for_one_run{ 10000 };

BruteForceAttacker::BruteForceAttacker(bool is_log, unsigned int number_thread_and_decryptors, std::string file_path)
    : threads_number_(number_thread_and_decryptors)
    , decrypt_status_(false)
    , number_in_cycle_main_(number_of_candidate_passwords_for_one_run)
    , is_log_(is_log)
{
    std::unique_ptr<FileReader> file_reader = std::make_unique<FileReader>();
    text_from_file_ = file_reader->ReadData(file_path);
}

void BruteForceAttacker::StartAsyncThreadsWithDecriporInside(unsigned short int number_thread_and_decryptors_m, std::string* array_all_pos_pass, Counter& counter)
{
    int size_array_for_one_thread= number_in_cycle_main_/number_thread_and_decryptors_m;
    int start_index_in_array;
    std::future<std::string>* future_assync_array = new std::future<std::string>[number_thread_and_decryptors_m];
    for (unsigned i = 0; i < number_thread_and_decryptors_m; i++)
    {
        start_index_in_array = i * size_array_for_one_thread;
        future_assync_array[i] = std::async(std::launch::async, FreeFunctionToDecrypt, array_all_pos_pass, start_index_in_array, size_array_for_one_thread, std::ref(is_log_), std::ref(text_from_file_), std::ref(counter));
     }
    for (unsigned i = 0; i < number_thread_and_decryptors_m; i++)
    {
        std::string current_candadate = future_assync_array[i].get();
        if ( !current_candadate.empty() )
        {
            decrypt_status_ = true;
            password_that_opened_the_file_ = current_candadate;
            break;
        }
    }
}

void BruteForceAttacker::FunctionForPrintInThread(Counter& my_counter, Timer& my_timer)
{
    Printer free_printer;
    while (!decrypt_status_)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        free_printer.ShowInfo(my_counter, my_timer);
    }
    free_printer.ShowRightPass(password_that_opened_the_file_);
}

void BruteForceAttacker::startDecrypt()
{    
    timer_.startTimeCounting();
    Counter counter;
    counter.SetNumberInCycle(number_in_cycle_main_);
    std::thread PrintInthread(&BruteForceAttacker::FunctionForPrintInThread, this, std::ref(counter), std::ref(timer_));
    std::vector<char> pos_symbols_NEW = generatPossibleCharVectorNEW();

    int indexJ = 0;
    int indexN = 1;
    int indexI = 1;
    bool big_loop_end = false;
    int number_for_all_threads = number_in_cycle_main_;
    std::string* bunch_pass_candidates = new std::string[number_for_all_threads];
    bool start_first = true;
    while (!decrypt_status_)
    { 
        int indexT = 0;
        bunch_pass_candidates = generatePasswordVariant(number_for_all_threads, std::ref(indexJ), std::ref(indexN), std::ref(pos_symbols_NEW), std::ref(bunch_pass_candidates), std::ref(indexI), std::ref(big_loop_end), std::ref(indexT), std::ref(start_first));
        StartAsyncThreadsWithDecriporInside(threads_number_, bunch_pass_candidates, counter);
        counter.ResetTriedPasscandidateInCycleMain();
    }
    PrintInthread.join();
}

std::string FreeFunctionToDecrypt(std::string* current_array_candidats_m, int start_index_in_array, const int& size_array_for_one_thread, const bool is_log, const std::vector<unsigned char>& text_from_file, Counter& counter)
{
    Decryptor current_decryptor(text_from_file);
    int current_index = start_index_in_array;
    for (int i = start_index_in_array; i < size_array_for_one_thread + start_index_in_array; i++)
    {
        counter.Calculate();

        if (current_decryptor.Decrypt(current_array_candidats_m[i]))
        {
            if (is_log)
            {
                WriteDownToFileTriedPassword(current_array_candidats_m, start_index_in_array, i, counter.GetMutex());
            }
            return current_array_candidats_m[i]; //we guess the password
        }
    }
    if (is_log)
    {
        WriteDownToFileTriedPassword(current_array_candidats_m, start_index_in_array, size_array_for_one_thread, counter.GetMutex());
    }
    return "";//we didn't guess the password
}