#pragma once
#include <iostream>
class Process
{
public:
	enum stat
	{
		not_active,
		waiting,
		processing,
		end
	};
private:
	int appear_time=0;
	int processing_time=0;
	int system_time=0;
	int lost_time=0;
	stat state=Process::stat::not_active;
public:
	Process();
	Process(int appear_time, int processing_time);
	int print(std::ostream&);
	int work();
	int wait();
	int get_appear_time();
	int get_processing_time();
	int get_system_time();
	int get_lost_time();
	stat get_state();
	int activate();
	friend std::ostream& operator<<(std::ostream&, stat);
	friend std::ostream& operator<<(std::ostream&, Process&);
};

