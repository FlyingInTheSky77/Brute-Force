#pragma once
#include "stdafx.h"
#include "PassGenerateFunction.h"
#include "Counter.h"
#include <stdio.h>

std::string* generatePasswordVariant(int cycle, int& indexJ, int& indexN, const std::vector<char>& chars, std::string* bunch_pass_candidates, int& indexI, bool& big_loop_end, int& indexT, bool& start_first)
{   
    int n = chars.size();
    int i = indexI;
    int N = indexN;
    int j = indexJ;
        int number_candidate_in_one_cycle_m = cycle;
        while (true)
        {  
            if (start_first)
            {
                for (int jt = 0; jt < i; jt++)
                    N *= n;
                start_first = false;
            }
            if (big_loop_end)
            {
                big_loop_end = false;
                i++;
                N = 1;
                for (int jk = 0; jk < i; jk++)
                    N *= n;
            }
            for (j= indexJ; j < N; j++)
            {
                int K = 1;
                std::string candidate = "";
                for (int k = 0; k < i; k++)               
                {
                    candidate += chars[j / K % n];
                    int temp = j / K % n;
                    K *= n;
                }
                bunch_pass_candidates[indexT] = candidate;
                indexT++;
                number_candidate_in_one_cycle_m--;
                if (number_candidate_in_one_cycle_m == 0)                
                {
                    j++;
                    indexJ = j;
                    indexN = N;
                    indexI = i;
                    indexT = 0;
                    return bunch_pass_candidates;
                }
            }
            big_loop_end = true;
        }  
}
std::vector<char>  generatPossibleCharVectorNEW()
{
    std::vector<char> possible_symbols;
    for (char i = '0'; i <= '9'; i++)
    {
        possible_symbols.push_back(i);
    }
    for (char i = 'a'; i <= 'z'; i++)
    {
        possible_symbols.push_back(i);
    }
    return possible_symbols;
}