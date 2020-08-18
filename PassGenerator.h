#pragma once
#include "mutex"
class BruteForceAttacker;

class PassGenerator
{
public: 
    PassGenerator(unsigned int number_in_cycle);
    void Crack();
    void generatPossibleCharVector();
    std::vector<std::string>& getNewPassCandidateVector();
private:
    std::vector<std::string> new_all_possible_pass_m;
    std::vector<char> new_chars_m;
    int number_candidate_in_one_cycle_m;
    
};
