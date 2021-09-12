#include "stdafx.h"
#include "Counter.h"

Counter::Counter()
    :number_all_tried_passcandidate_m(0),
    number_for_now_in_cycle_main_m(0)
{ }

void Counter::Calculate()
{
    std::lock_guard<std::mutex> locked(mutex_counter_m);
    IncreaseByOneNumberTriedPasscandidate();
    IncreaseByOneNumberTriedPasscandidateInShowCycle();
    IncreaseTriedPasscandidateInCycleMain();    
}

void Counter::IncreaseByOneNumberTriedPasscandidateInShowCycle()
{
    number_tried_passcandidate_in_show_cycle_m++;
}
unsigned int& Counter::getTriedPasscandidateInShowCycle()
{
    return number_tried_passcandidate_in_show_cycle_m;
}
void Counter::ResetTriedPasscandidateInShowCycle()
{
    number_tried_passcandidate_in_show_cycle_m = 0;
}

void Counter::IncreaseTriedPasscandidateInCycleMain()
{
    number_for_now_in_cycle_main_m++;
}
void Counter::ResetTriedPasscandidateInCycleMain()
{
    number_for_now_in_cycle_main_m = 0;
}
unsigned int& Counter::GetTriedPasscandidateInCycleMain()
{
    return number_for_now_in_cycle_main_m;
}

void Counter::IncreaseByOneNumberTriedPasscandidate()
{
    number_all_tried_passcandidate_m++;
}
unsigned int& Counter::GetTriedPasscandidate()
{
    return number_all_tried_passcandidate_m;
}

unsigned int Counter::GetPresetNumberInMainCycle()
{
    return number_in_cycle_main_m;
}

void Counter::SetNumberInCycle(unsigned int number_in_cycle_main)
{
    number_in_cycle_main_m = number_in_cycle_main;
}

std::mutex& Counter::GetMutex()
{
    return mutex_counter_m;
}

void Counter::WriteTriedCandidateToVector(std::string current_pass_candidate)
{
    std::lock_guard<std::mutex> locked(mutex_counter_m);
    vector_tried_pass.push_back(current_pass_candidate);
}