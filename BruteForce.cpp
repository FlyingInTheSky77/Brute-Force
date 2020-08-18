#include "stdafx.h"
#include "BruteForceAttacker.h"
#include "Encryptor.h"
#include "Decryptor.h"
#include "OptionSelectionFunctions.h"

int main(int argc, char* argv[])
{
    std::string str = std::string(argv[2]);
    bool DoWeShouldSaveAllTriedPass = false;
    if (str == "--log_passwords")
    {
        DoWeShouldSaveAllTriedPass = true;
    }
    std::string crypto_file_path;
    crypto_file_path = std::string(argv[1]);    
    int whatToDo = WriteWhatToDo();
    int numner_of_threads = SetNumberOfThreads();
    BruteForceAttacker newOne(DoWeShouldSaveAllTriedPass, numner_of_threads, crypto_file_path, 10000);
    switch (whatToDo)
    {
    case 1://file encryption
    {
        newOne.myEncryptFile();
        break;
    };
    case 2: //file decryption
    {
        newOne.startDecrypt();
        break;
    }
    }
    return 0;
}