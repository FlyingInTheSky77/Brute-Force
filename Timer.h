#pragma once

class Timer
{
public:
	void startTimeCounting();
	unsigned int getCurrentTimeWorking();
	void GetShowTime(std::string& show_time_line);
private:
	time_t begin_time_m;
	time_t current_time_m;
};

