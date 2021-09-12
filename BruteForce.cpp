#include "stdafx.h"
#include "BruteForceAttacker.h"
#include "Encryptor.h"
#include "Decryptor.h"
#include "OptionSelectionFunctions.h"

int main(int argc, char* argv[])
{
    //std::string crypto_file_path = std::string(argv[1]);
    //std::string is_log = std::string(argv[2]);

    //std::string file_path = "C:\\repos\\Brute-Force\\1";

    std::string file_path = "C:\\repos\\Brute-Force\\my_crypto_file1";
    std::string is_log{ "--log_passwords" };

    try {
        InitialDataChecker DataChecker(file_path, is_log);
        if ( DataChecker.isDataOkey() ) {
            const int whatToDo = DataChecker.WriteWhatToDoWithFile();
            switch (whatToDo)
            {                
                case 1: {
                    Encryptor myEncryptor( DataChecker.getFilePath() );
                    myEncryptor.start();
                    break;
                };
                case 2: {
                    const int numner_of_threads{ 2 };
                    BruteForceAttacker Worker(DataChecker.getLogStatus(), numner_of_threads, DataChecker.getFilePath());
                    Worker.startDecrypt();
                    break;
                }
                case 0: {
                    std::cout << "Program is closed";
                    break;
                }
            }
        }
    }
    catch (std::exception& ex) {
        std::cout << "ERROR: we got an exception: "<< ex.what();        
    }
    return 0;
}