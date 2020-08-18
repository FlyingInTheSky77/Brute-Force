#include "stdafx.h"
#include "BruteForceAttacker.h"
#include "Decryptor.h"
#include "Encryptor.h"
#include "OptionSelectionFunctions.h"
#include "PassGenerateFunction.h"
#include <thread>
#include "Counter.h"

BruteForceAttacker::BruteForceAttacker(bool write_passcandidate_to_file, unsigned int number_thread_and_decryptors, std::string file_path, int number_in_cycle_main)
    :encryptor_m(std::make_unique<Encryptor>()),
    timer_m(std::make_shared <Timer>()),
    number_thread_and_decryptors_m(number_thread_and_decryptors),
    decrypt_status_m(false),
    number_in_cycle_main_m(number_in_cycle_main),
    write_to_file_all_tried_passcandidate_m(write_passcandidate_to_file),
    file_path_m(file_path)
{}

BruteForceAttacker::~BruteForceAttacker()
{}

void BruteForceAttacker::myEncryptFile()
{ 
    try
    {
        encryptor_m->setPassForCrypting();
        encryptor_m -> Encrypt();
    }
    catch (const std::runtime_error& ex)
    {
        std::cerr << ex.what();
    }    
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
        if (current_candadate != "")
        {
            decrypt_status_m = true;
            password_that_opened_the_file_m = current_candadate;
        }
    }
}

void BruteForceAttacker::FunctionForPrintInThread(std::shared_ptr<Counter> my_counter, std::shared_ptr <Timer> my_timer)
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
    myReadFile(file_path_m, text_from_file_m);
    timer_m->startTimeCounting();
    std::shared_ptr<Counter> my_shp_counter= std::make_shared<Counter>();
    my_shp_counter->SetNumberInCycle(number_in_cycle_main_m);
    std::thread PrintInthread(&BruteForceAttacker::FunctionForPrintInThread, this, std::ref(my_shp_counter), std::ref(timer_m));
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
        bunch_pass_candidates = CrackNEW2(number_for_all_threads, std::ref(indexJ), std::ref(indexN), std::ref(pos_symbols_NEW), std::ref(bunch_pass_candidates), all_tried_pass_m, std::ref(indexI), std::ref(big_loop_end), std::ref(indexT),std::ref(start_first));
        StartAsyncThreadsWithDecriporInside(number_thread_and_decryptors_m, bunch_pass_candidates, my_shp_counter);
        my_shp_counter->ResetTriedPasscandidateInCycleMain();
    }
    PrintInthread.join();
}

void BruteForceAttacker::setDecryptStatus()
{
    decrypt_status_m = true;
}
bool BruteForceAttacker::GetDecryptStatus()
{
    return decrypt_status_m;
}

void BruteForceAttacker::WriteTriedCandidate(std::string current_pass_candidate)
{
    all_tried_pass_m.push_back(current_pass_candidate);
}

bool BruteForceAttacker::GetUserSolutionAboutWriteDownPasswords()
{
    return write_to_file_all_tried_passcandidate_m;
}

std::string& BruteForceAttacker::GetFilePath()
{
    return file_path_m;
}

std::vector<unsigned char> BruteForceAttacker::GetTextFromFileM()
{
    return text_from_file_m;
}





