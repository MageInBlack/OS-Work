#include "Task.h"

int HPRN(std::vector<Process>& processes)
{
	size_t size = processes.size();
	double tmppen;
	double maxpen=0;
	int proc=-1;

	for (size_t t = 0; t < size; t++)
	{
		if (processes[t].get_state() != Process::stat::end && processes[t].get_state()!=Process::stat::not_active)
		{
			tmppen = double(double(processes[t].get_processing_time()) + processes[t].get_lost_time()) / processes[t].get_processing_time();
			if (tmppen > maxpen)
			{
				maxpen = tmppen;
				proc = t;
			}
		}
	}
	if (proc > -1)
	{
		for (size_t t = 0; t < size; t++)
		{
			if (t == proc) processes[t].work();
			else processes[t].wait();
		}
	}

	return 1;
}

int RR(std::vector<Process>& processes)
{
	size_t size = processes.size();
	static int lw = -1;
	int nw = -1;
	int tmp;
	
	/*tmp = lw;
	while (lw != (tmp-1)%size && processes[(lw+1)%size].get_state() != Process::stat::waiting && processes[(lw+1)%size].get_state() != Process::stat::processing)
	{
		lw = (lw + 1) % size;
	}*/

	for (int t = (lw+1)%size; t !=(lw==-1?size-1:lw); t=(t+1)%size)
	{
		if (processes[t].get_state() == Process::stat::waiting)
		{
			nw = t;
			break;
		}
	}
	if (nw != -1)
		lw = nw;
	if (lw != -1) 
	{
		processes[lw].work();
		/*if (processes[lw].get_state() == Process::stat::end)
		{
			tmp = lw;
			do 	
			{
				lw = (lw + 1) % size;
			} while (lw != tmp && processes[(lw + 1) % size].get_state() != Process::stat::waiting && processes[(lw + 1) % size].get_state() != Process::stat::processing);

			//for (int n = lw; lw != (n-1)%size&&processes[lw].get_state()==Process::stat::waiting&& processes[lw].get_state() == Process::stat::processing; lw = (lw + 1) % size);
		}*/
	}
	for (int t = 0; t < size; t++)
	{
		if (t != lw) processes[t].wait();
	}
	return 1;
}