#pragma once
class Counter
{
public:
    Counter();
    void Calculate();
    //100millisec-cycle
    void IncreaseByOneNumberTriedPasscandidateInShowCycle();
    unsigned int& getTriedPasscandidateInShowCycle();
    void ResetTriedPasscandidateInShowCycle();
    //all pass candidate from start decrypting
    void IncreaseByOneNumberTriedPasscandidate();
    unsigned int& GetTriedPasscandidate();
    //10000-cycle
    void IncreaseTriedPasscandidateInCycleMain();
    unsigned int& GetTriedPasscandidateInCycleMain();
    void ResetTriedPasscandidateInCycleMain();
    int GetPresetNumberInMainCycle();
    void SetNumberInCycle(int number_in_cycle_main);
    std::mutex& GetMutex();
    void WriteTriedCandidateToVector(std::string current_pass_candidate);
private:
    unsigned int number_tried_passcandidate_in_show_cycle_m;
    unsigned int number_all_tried_passcandidate_m;
    unsigned int number_for_now_in_cycle_main_m;
    std::mutex mutex_counter_m;

    std::vector<std::string> vector_tried_pass;//member for debug
    unsigned int number_in_cycle_main_m;
};

