#include "stdafx.h"
#include "PassGenerator.h"
#include "BruteForceAttacker.h"
#include <chrono>

PassGenerator::PassGenerator(unsigned int number_in_cycle)
    :number_candidate_in_one_cycle_m(number_in_cycle)
{}

void PassGenerator::Crack()
{
    int n = new_chars_m.size();
    int i = 0;
    int cycle_counter = number_candidate_in_one_cycle_m;
    while (true)
    {
        i++;
        int N = 1;
        for (int j = 0; j < i; j++)
            N *= n;
        for (int j = 0; j < N; j++)
        {
            int K = 1;
            std::string candidate = "";
            for (int k = 0; k < i; k++)
            {
                candidate += new_chars_m[j / K % n];
                K *= n;
            }
            
            cycle_counter--;
            new_all_possible_pass_m.push_back(candidate);
            if (cycle_counter == 0)
            {
                ResetEvent(owner_m->getDecryptorEventHandle());
                SetEvent(owner_m->getVectorEventHandle());
                owner_m->ResetTriedPasscandidateInCycleMain();
                WaitForSingleObject(owner_m->getDecryptorEventHandle(), INFINITE);
                ResetEvent(owner_m->getVectorEventHandle());
                new_all_possible_pass_m.clear();
                cycle_counter = number_candidate_in_one_cycle_m;
            }
        }
    }
}
void PassGenerator::generatPossibleCharVector()
{
    for (char i = '0'; i <= '9'; i++)
    {
        new_chars_m.push_back(i);
    }
    for (char i = 'a'; i <= 'z'; i++)
    {
        new_chars_m.push_back(i);
    }
}

std::vector<std::string>& PassGenerator::getNewPassCandidateVector()
{
    WaitForSingleObject(owner_m->getVectorEventHandle(), INFINITE);
    return new_all_possible_pass_m;
}