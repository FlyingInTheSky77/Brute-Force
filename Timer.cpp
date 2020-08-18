#include "stdafx.h"
#include "Timer.h"

unsigned int Timer::getCurrentTimeWorking()
{
	current_time_m = clock();
	return static_cast<unsigned int> ((current_time_m - begin_time_m)/ CLOCKS_PER_SEC);
}
void Timer::startTimeCounting()
{
	begin_time_m = clock();
}

void Timer::GetShowTime(std::string& show_time_line)
{
	unsigned int cur_time = getCurrentTimeWorking();
	if (cur_time < 60)
	{
		show_time_line = "Time elapsed:" + std::to_string(cur_time) + "s   ";
	}
	else if (cur_time < 3600)
	{
		unsigned int cur_min = cur_time / 60;
		unsigned int cur_sec = cur_time % 60;
		show_time_line = "Time elapsed:" + std::to_string(cur_min) + "m" + std::to_string(cur_sec) + "s   ";
	}
	else
	{
		unsigned int cur_hours = cur_time / 3600;
		unsigned int cur_min = (cur_time - cur_hours * 3600) / 60;
		unsigned int cur_sec = (cur_time - cur_hours * 3600) % 60;
		show_time_line = "Time elapsed:" + std::to_string(cur_hours) + "h " + std::to_string(cur_min) +"m " + std::to_string(cur_sec) + "s     ";
	}
}


