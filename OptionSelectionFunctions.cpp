#include "stdafx.h"
#include "OptionSelectionFunctions.h"
#include "Decryptor.h"
#include "Printer.h"
#include "Counter.h"

InitialDataChecker::InitialDataChecker(const std::string& file_path, const std::string& isLog)
    : file_path_(file_path)
    , is_log_ (false)
    , is_data_okey( false)
{
    if (isLog == "--log_passwords")
        is_log_ = true;
    tryOpenFile(file_path);
}

void InitialDataChecker::tryOpenFile(const std::string& filePath)
{    
    file_path_ = filePath;
    if (!OpenFile(file_path_)) {
        std::cin >> file_path_;
        if (!OpenFile(file_path_))
            std::cout << "wrong file name or/and  filepath. There is no more try. " << std::endl;        
    }    
}

bool InitialDataChecker::OpenFile(const std::string& filePath)
{
    std::ifstream f1;
    f1.open(filePath);
    if (f1.is_open()) {
        is_data_okey = true;
        return true;
    }
    return false;
}

int InitialDataChecker::WriteWhatToDoWithFile()
{
    std::string symbol;
    bool try_choose_what_to_do{ true };
    do {
        std::cout << "Enter number:\n1, if you want to crypto file" << std::endl;
        std::cout << "2, if you want to decrypto file" << std::endl;
        std::cout << "any number or symbol - to exit" << std::endl;
    
        std::cin >> symbol;
        if (symbol == "1" || symbol == "2")
            return std::stoi(symbol);

        std::cout << "do you really want to exit the program?\n enter \"0\" if want to exit: ";
        std::cin >> symbol;
        if ( symbol != "0" )
            try_choose_what_to_do = false;
    } while (try_choose_what_to_do);

    return 0;
}

void WriteDownToFileTriedPassword(std::string* current_vector_candidats_m, int start_index_in_array, const int& current_index, std::mutex& cur_mutex)
{
    std::lock_guard<std::mutex> locked(cur_mutex);
    std::ofstream out;
    out.open("AllTriedPass", std::ios_base::app);
    
    for (int i = start_index_in_array; i < current_index; i++)
    {
        std::string temp_for_debuging = current_vector_candidats_m[i];
        out << current_vector_candidats_m[i] << std::endl;
    }
    out.close();
}

void myReadFile(const std::string& filePath, std::vector<unsigned char>& buf)
{
    std::basic_fstream<unsigned char> fileStream(filePath, std::ios::binary | std::fstream::in);
    if (!fileStream.is_open())
    {
        throw std::runtime_error("Can not open file " + filePath);
    }
    buf.clear();
    buf.insert(buf.begin(), std::istreambuf_iterator<unsigned char>(fileStream), std::istreambuf_iterator<unsigned char>());
}


std::string FreeFunctionToDecrypt(std::string* current_array_candidats_m, int start_index_in_array, const int& size_array_for_one_thread, const bool& write_cand_to_file, const std::vector<unsigned char>& text_from_file, std::shared_ptr<Counter> my_counter)
{
    Decryptor current_decryptor;
    int current_index = start_index_in_array;
    for (int i = start_index_in_array; i < size_array_for_one_thread + start_index_in_array; i++)
    {
        std::string temp = current_array_candidats_m[i];
        current_decryptor.PasswordToKey(current_array_candidats_m[i]);
        my_counter->Calculate();
        
        if (current_decryptor.Decrypt(text_from_file))
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