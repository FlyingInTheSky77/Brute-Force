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
    BruteForceAttacker(bool write_passcandidate_to_file, unsigned int number_thread_and_decryptors, std::string file_path, int number_in_cycle_main_m);
    ~BruteForceAttacker();
    void myEncryptFile();
    void startDecrypt();
    void FunctionForPrintInThread(std::shared_ptr<Counter> my_counter, std::shared_ptr <Timer> my_timer);
    void StartAsyncThreadsWithDecriporInside(unsigned short int number_thread_and_decryptors_m, std::string* array_all_pos_pass, std::shared_ptr<Counter> my_counter);
        
    void setDecryptStatus();
    bool GetDecryptStatus();
    std::vector<unsigned char> GetTextFromFileM();

    bool GetUserSolutionAboutWriteDownPasswords();
    std::string& GetFilePath();
    void WriteTriedCandidate(std::string current_pass_candidate);
private:
    std::unique_ptr<Encryptor>  encryptor_m;;
    std::shared_ptr<Timer> timer_m;
    unsigned int number_thread_and_decryptors_m;
    bool decrypt_status_m;
    std::mutex mutex_m;
    std::string password_that_opened_the_file_m;
    std::vector<std::string> all_tried_pass_m;
    bool write_to_file_all_tried_passcandidate_m;
    std::string file_path_m;
    std::vector<unsigned char> text_from_file_m;
    int number_in_cycle_main_m;
};

