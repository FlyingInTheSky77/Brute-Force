#include "stdafx.h"
#include "Counter.h"

Counter::Counter()
    : number_all_tried_passcandidate_(0)
    , number_for_now_in_cycle_main_(0)
{ }

void Counter::Calculate()
{
    std::mutex cur_mutex;
    std::lock_guard<std::mutex> locked(cur_mutex);
    IncreaseByOneNumberTriedPasscandidate();
    IncreaseByOneNumberTriedPasscandidateInShowCycle();
    IncreaseTriedPasscandidateInCycleMain();    
}

void Counter::IncreaseByOneNumberTriedPasscandidateInShowCycle()
{
    number_tried_passcandidate_in_show_cycle_++;
}
unsigned int& Counter::getTriedPasscandidateInShowCycle()
{
    return number_tried_passcandidate_in_show_cycle_;
}
void Counter::ResetTriedPasscandidateInShowCycle()
{
    number_tried_passcandidate_in_show_cycle_ = 0;
}

void Counter::IncreaseTriedPasscandidateInCycleMain()
{
    number_for_now_in_cycle_main_++;
}
void Counter::ResetTriedPasscandidateInCycleMain()
{
    number_for_now_in_cycle_main_ = 0;
}
unsigned int& Counter::GetTriedPasscandidateInCycleMain()
{
    return number_for_now_in_cycle_main_;
}

void Counter::IncreaseByOneNumberTriedPasscandidate()
{
    number_all_tried_passcandidate_++;
}
unsigned int& Counter::GetTriedPasscandidate()
{
    return number_all_tried_passcandidate_;
}

unsigned int Counter::GetPresetNumberInMainCycle()
{
    return number_in_cycle_main_;
}

void Counter::SetNumberInCycle(unsigned int number_in_cycle_main)
{
    number_in_cycle_main_ = number_in_cycle_main;
}

std::mutex& Counter::GetMutex()
{
    return mutex_counter_;
}