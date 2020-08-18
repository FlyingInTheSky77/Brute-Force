#include "stdafx.h"
#include "DecryptFunction.h"

void Crack(std::string password, std::vector<char> Chars)
{
    std::cout << "PASSWORD TO CRACK: " << password << std::endl;
    int n = Chars.size();
    int i = 0;
    while (true)
    {
        i++;
        int N = 1;
        for (int j = 0; j < i; j++)
            N *= n;
        for (int j = 0; j < N; j++)
        {
            int K = 1;
            std::string crack = "";
            for (int k = 0; k < i; k++)
            {
                crack += Chars[j / K % n];
                K *= n;
            }
            std::cout << "Testing PASS: " << crack << " " << "against " << password << std::endl;
            if (password.compare(crack) == 0) 
            {
                std::cout << "Cracked password: " << crack << std::endl;
                return;
            }
        }
    }
}