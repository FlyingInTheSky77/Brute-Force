#pragma once
class Counter
{
public:
    Counter();
    void Calculate();
    
    // 100millisec-cycle
    void IncreaseByOneNumberTriedPasscandidateInShowCycle();
    unsigned int& getTriedPasscandidateInShowCycle();
    void ResetTriedPasscandidateInShowCycle();
    
    // all pass candidate from start decrypting
    void IncreaseByOneNumberTriedPasscandidate();
    unsigned int& GetTriedPasscandidate();
    
    // 10000-cycle
    void IncreaseTriedPasscandidateInCycleMain();
    unsigned int& GetTriedPasscandidateInCycleMain();
    void ResetTriedPasscandidateInCycleMain();
    unsigned int GetPresetNumberInMainCycle();
    void SetNumberInCycle(unsigned int number_in_cycle_main);
    std::mutex& GetMutex();

private:
    unsigned int number_tried_passcandidate_in_show_cycle_;
    unsigned int number_all_tried_passcandidate_;
    unsigned int number_for_now_in_cycle_main_;
    std::mutex mutex_counter_;

    unsigned int number_in_cycle_main_;
};

