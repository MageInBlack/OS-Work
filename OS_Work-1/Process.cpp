#include "Process.h"

Process::Process()
{

}

Process::Process(int appear_time, int processing_time)
{
	try
	{
		if (appear_time < 0) throw "appear time";
		this->appear_time = appear_time;
		if (processing_time < 1) throw "processing time";
		this->processing_time = processing_time;
	}
	catch (std::string a)
	{
		std::cout << "Invalid value of " << a<<std::endl;
	}
}

int Process::print(std::ostream& out)
{
	out << "Appear time: " << this->appear_time << " Processing time: " << this->processing_time<<std::endl;
	return 1;
}

int Process::work()
{
	
	if (this->state!=stat::not_active&&this->state != stat::end)
	{
		this->state = stat::processing;
		this->system_time++;
		if (this->system_time - this->lost_time == this->processing_time)
			this->state = stat::end;
	}
	return 1;
}

int Process::wait()
{
	if (this->state != stat::not_active && this->state != stat::end)
	{
		this->state = stat::waiting;
		this->system_time++;
		this->lost_time++;
	}
	return 1;
}

int Process::get_appear_time()
{
	return this->appear_time;
}

int Process::get_processing_time()
{
	return this->processing_time;
}

int Process::get_system_time()
{
	return this->system_time;
}

int Process::get_lost_time()
{
	return this->lost_time;
}

Process::stat Process::get_state()
{
	return this->state;
}

int Process::activate()
{
	if (this->state == Process::stat::not_active) this->state = Process::stat::waiting;
	return 1;
}

std::ostream& operator<<(std::ostream& out, Process::stat state)
{
	switch (state)
	{
	case Process::stat::not_active:
		out << 'X';
		break;
	case Process::stat::waiting:
		out << 'W';
		break;
	case Process::stat::processing:
		out << 'P';
		break;
	case Process::stat::end:
		out << 'E';
		break;
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, Process& process)
{
	out << "System time: " << process.system_time << " Lost time: " << process.lost_time << " Reactivity: " << (double(process.system_time) - process.lost_time) / process.system_time<<" Loss: "<<double(process.system_time)/(double(process.system_time)-process.lost_time);
	return out;
}