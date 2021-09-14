#include "stdafx.h"
#include "Printer.h"
#include "Timer.h"
#include "Counter.h"

Printer::Printer()
{
	hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);
}
void Printer::SetConsol()
{
	myCoord_.X = 0;
	myCoord_.Y = 15;
	SetConsoleCursorPosition(hConsole_, myCoord_);
}
void Printer::ShowRightPass(const std::string& right_pass_m)
{
	myCoord_.X = 10;
	myCoord_.Y = 21;
	SetConsoleCursorPosition(hConsole_, myCoord_);
	std::cout << "We decrypt our file with pass: " << right_pass_m<<std::endl;
}

void Printer::ShowInfo(Counter& counter, Timer& timer)
{	
	SetConsol();
	std::lock_guard<std::mutex> loked(counter.GetMutex());
	const unsigned int Number_In_Main_Cycle{ counter.GetPresetNumberInMainCycle() };
	unsigned const int Tried_Passcandidate_In_Main_Cycle{ counter.GetTriedPasscandidateInCycleMain() };

	std::cout << Tried_Passcandidate_In_Main_Cycle << " from " << Number_In_Main_Cycle << " passwords checked [";
	std::cout<< ( Tried_Passcandidate_In_Main_Cycle * 100 / Number_In_Main_Cycle) << "%]             " << std::endl;
	std::cout << "Speed:" << counter.getTriedPasscandidateInShowCycle() << "pass/sec           "<<std::endl;

	std::cout << timer.GetShowTime() << std::endl;
	std::cout << "tried all passwords for now:" << counter.GetTriedPasscandidate() << std::endl;
	counter.ResetTriedPasscandidateInShowCycle();	
}