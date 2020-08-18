#include "stdafx.h"
#include "OptionSelectionFunctions.h"
#include "Decryptor.h"
#include "Printer.h"
#include "Counter.h"


int WriteWhatToDo()
{
    std::string symbol;
    std::cout << "Enter 1, if you want to crypto file" << std::endl;
    std::cout << "Enter 2, if you want to decrypto file" << std::endl;
    while (true)
    {
        std::cin >> symbol;
        if (symbol == "1")
        {
            return 1;
        }
        if (symbol == "2")
        {
            return 2;
        }
        else {
            std::cout << "Enter 1 or 2, please: ";
        }
    }
}

unsigned int SetNumberOfThreads()
{
    int number_of_threads;
    std::cout << "Enter number of threads: ";
    std::cin >> number_of_threads;
    return number_of_threads;
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