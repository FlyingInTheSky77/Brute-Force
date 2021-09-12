#pragma once
class Timer;
class Counter;

class Printer
{
public:
	Printer();
	void ShowInfo(std::shared_ptr<Counter> my_counter, Timer my_timer);
	void SetConsol();
	void ShowRightPass(std::string right_pass_m);

private:
	HANDLE hConsole;
	COORD myCoord;
	std::string show_time_line_m;
};

