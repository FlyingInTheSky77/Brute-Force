#pragma once

class Timer
{
public:
	void startTimeCounting();
	unsigned int getCurrentTimeWorking();
	std::string GetShowTime();

private:
	time_t begin_time_m;
	time_t current_time_m;
};

