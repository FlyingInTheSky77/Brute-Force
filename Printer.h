#pragma once
class Timer;
class Counter;

class Printer
{
public:
	Printer();
	void ShowInfo(Counter& counter, Timer& timer);
	void SetConsol();
	void ShowRightPass(const std::string& right_pass_m);

private:
	HANDLE hConsole_;
	COORD myCoord_;
};

