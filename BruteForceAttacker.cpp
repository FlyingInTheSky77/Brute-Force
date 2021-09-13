#include "stdafx.h"
#include "BruteForceAttacker.h"
#include "Decryptor.h"
#include "Encryptor.h"
#include "OptionSelectionFunctions.h"
#include "PassGenerateFunction.h"
#include <thread>
#include "Counter.h"

const int number_of_candidate_passwords_for_one_run{ 10000 };

BruteForceAttacker::BruteForceAttacker(bool write_passcandidate_to_file, unsigned int number_thread_and_decryptors, std::string file_path)
    : number_thread_and_decryptors_m(number_thread_and_decryptors)
    , decrypt_status_m(false)
    , number_in_cycle_main_m(number_of_candidate_passwords_for_one_run)
    , write_to_file_all_tried_passcandidate_m(write_passcandidate_to_file)
    , file_path_m(file_path)
{
    myReadFile(file_path_m, text_from_file_m);
}

void BruteForceAttacker::StartAsyncThreadsWithDecriporInside(unsigned short int number_thread_and_decryptors_m, std::string* array_all_pos_pass, std::shared_ptr<Counter> my_counter)
{
    int size_array_for_one_thread= number_in_cycle_main_m/number_thread_and_decryptors_m;
    int start_index_in_array;
    std::future<std::string>* future_assync_array = new std::future<std::string>[number_thread_and_decryptors_m];
    for (unsigned i = 0; i < number_thread_and_decryptors_m; i++)
    {
        start_index_in_array = i * size_array_for_one_thread;
        future_assync_array[i] = std::async(std::launch::async, FreeFunctionToDecrypt, array_all_pos_pass, start_index_in_array, size_array_for_one_thread, std::ref(write_to_file_all_tried_passcandidate_m), std::ref(text_from_file_m), std::ref(my_counter));
     }
    for (unsigned i = 0; i < number_thread_and_decryptors_m; i++)
    {
        std::string current_candadate = future_assync_array[i].get();
        if ( !current_candadate.empty() )
        {
            decrypt_status_m = true;
            password_that_opened_the_file_m = current_candadate;
            break;
        }
    }
}

void BruteForceAttacker::FunctionForPrintInThread(std::shared_ptr<Counter> my_counter, Timer my_timer)
{
    Printer free_printer;
    while (!decrypt_status_m)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        free_printer.ShowInfo(my_counter, my_timer);
    }
    free_printer.ShowRightPass(password_that_opened_the_file_m);
}

void BruteForceAttacker::startDecrypt()
{    
    timer_.startTimeCounting();
    std::shared_ptr<Counter> my_shp_counter= std::make_shared<Counter>();
    my_shp_counter->SetNumberInCycle(number_in_cycle_main_m);
    std::thread PrintInthread(&BruteForceAttacker::FunctionForPrintInThread, this, std::ref(my_shp_counter), std::ref(timer_));
    std::vector<char> pos_symbols_NEW = generatPossibleCharVectorNEW();

    int indexJ = 0;
    int indexN = 1;
    int indexI = 1;
    bool big_loop_end = false;
    int number_for_all_threads = number_in_cycle_main_m;
    int number_for_one_thread = number_for_all_threads / number_thread_and_decryptors_m;
    std::string* bunch_pass_candidates = new std::string[number_for_all_threads];
    bool start_first = true;
    while (!decrypt_status_m)
    { 
        int indexT = 0;
        bunch_pass_candidates = generatePasswordVariant(number_for_all_threads, std::ref(indexJ), std::ref(indexN), std::ref(pos_symbols_NEW), std::ref(bunch_pass_candidates), std::ref(indexI), std::ref(big_loop_end), std::ref(indexT), std::ref(start_first));
        StartAsyncThreadsWithDecriporInside(number_thread_and_decryptors_m, bunch_pass_candidates, my_shp_counter);
        my_shp_counter->ResetTriedPasscandidateInCycleMain();
    }
    PrintInthread.join();
}

std::string FreeFunctionToDecrypt(std::string* current_array_candidats_m, int start_index_in_array, const int& size_array_for_one_thread, const bool& write_cand_to_file, const std::vector<unsigned char>& text_from_file, std::shared_ptr<Counter> my_counter)
{
    Decryptor current_decryptor(text_from_file);
    int current_index = start_index_in_array;
    for (int i = start_index_in_array; i < size_array_for_one_thread + start_index_in_array; i++)
    {
        my_counter->Calculate();

        if (current_decryptor.Decrypt(current_array_candidats_m[i]))
        {
            if (write_cand_to_file)
            {
                WriteDownToFileTriedPassword(current_array_candidats_m, start_index_in_array, i, my_counter->GetMutex());
            }
            return current_array_candidats_m[i]; //we guess the password
        }
    }
    WriteDownToFileTriedPassword(current_array_candidats_m, start_index_in_array, size_array_for_one_thread, my_counter->GetMutex());
    return "";//we didn't guess the password
}