#include "stdafx.h"
#include "Printer.h"
#include "Timer.h"
#include "Counter.h"

Printer::Printer()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}
void Printer::SetConsol()
{
	myCoord.X = 0;
	myCoord.Y = 15;
	SetConsoleCursorPosition(hConsole, myCoord);
}
void Printer::ShowRightPass(std::string right_pass_m)
{
	myCoord.X = 10;
	myCoord.Y = 21;
	SetConsoleCursorPosition(hConsole, myCoord);
	std::cout << "We decrypt our file with pass: " << right_pass_m<<std::endl;
}

void Printer::ShowInfo(std::shared_ptr<Counter> my_counter, Timer my_timer)
{	
	SetConsol();
	std::lock_guard<std::mutex> loked(my_counter->GetMutex());
	const unsigned int Number_In_Main_Cycle{ my_counter->GetPresetNumberInMainCycle() };
	unsigned const int Tried_Passcandidate_In_Main_Cycle{ my_counter->GetTriedPasscandidateInCycleMain() };

	std::cout << Tried_Passcandidate_In_Main_Cycle << " from " << Number_In_Main_Cycle << " passwords checked [";
	std::cout<< ( Tried_Passcandidate_In_Main_Cycle * 100 / Number_In_Main_Cycle) << "%]             " << std::endl;
	std::cout << "Speed:" << my_counter->getTriedPasscandidateInShowCycle() << "pass/sec           "<<std::endl;

	std::cout << my_timer.GetShowTime() << std::endl;
	std::cout << "tried all passwords for now:" << my_counter->GetTriedPasscandidate() << std::endl;
	my_counter->ResetTriedPasscandidateInShowCycle();	
}