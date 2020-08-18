#include "stdafx.h"
#include "Printer.h"
#include "Timer.h"
#include "Counter.h"
#include "myGuard.h"

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
	std::cout << "We decrypt our file with pass:" << right_pass_m<<std::endl;
}
void Printer::ShowInfo(std::shared_ptr<Counter> my_counter, std::shared_ptr <Timer> my_timer)
{
	
	SetConsol();
	std::lock_guard<std::mutex> loked(my_counter->GetMutex());
	std::cout << my_counter->GetTriedPasscandidateInCycleMain() << " from " << my_counter->GetPresetNumberInMainCycle() << " passwords checked [";
	std::cout<< (my_counter->GetTriedPasscandidateInCycleMain() * 100 / my_counter->GetPresetNumberInMainCycle()) << "%]             " << std::endl;
	std::cout << "Speed:" << my_counter->getTriedPasscandidateInShowCycle() << "pass/sec           "<<std::endl;
	my_timer->GetShowTime(show_time_line_m);
	std::cout << show_time_line_m<<std::endl;
	std::cout << "tried all passwords for now:" << my_counter->GetTriedPasscandidate() << std::endl;
	my_counter->ResetTriedPasscandidateInShowCycle();
	
}