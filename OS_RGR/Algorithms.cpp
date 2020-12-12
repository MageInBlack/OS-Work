#include "Algorithms.h"

void secondChanceAlgorithm(const std::list<size_t>& referenced, size_t bufferSize)
{
	std::list<Page> pages;

	bool exist;
	for (auto i = referenced.begin(); i != referenced.end(); i++)
	{
		if (pages.size() < bufferSize)
		{
			exist = 0;
			for (auto j=pages.begin();j!=pages.end();j++)
				if ((*j).getId() == (*i))
				{
					exist = 1;
					(*j).setChance(true);
				}
			if (!exist) pages.push_back(*i);
		}
		else
		{
			exist = 0;
			for (auto j = pages.begin(); j != pages.end(); j++)
				if ((*j).getId() == (*i))
				{
					exist = 1;
					(*j).setChance(true);
				}
			if (!exist)
			{
				while (!exist)
				{
					if (pages.front().GetChance() == true)
					{
						Page tmp = pages.front();
						tmp.setChance(false);
						pages.pop_front();
						pages.push_back(tmp);
					}
					else
					{
						pages.pop_front();
						pages.push_back((*i));
						exist = 1;
					}
				}
			}
		}
		std::cout << "requesting " << (*i) << ": ";
		for (auto j = pages.begin(); j != pages.end(); j++)
			std::cout<< (*j) << " ";
		std::cout << std::endl;
	}
}

void clockAlgorithm(const std::list<size_t>& referenced, size_t bufferSize)
{
	std::list<Page> pages;
	bool exist;

	for (auto i = referenced.begin(); i != referenced.end(); i++)
	{
		auto iter = pages.begin();
		if (pages.size() < bufferSize)
		{
			exist = 0;
			for (auto j = pages.begin(); j != pages.end(); j++)
				if ((*j).getId() == (*i))
				{
					exist = 1;
					(*j).setChance(true);
				}
			if (!exist) 
			{
				
				pages.push_back(*i);
				iter = pages.end();
			}
		}
		else
		{
			if (iter != pages.end()) iter++;
			else iter = pages.begin();
			exist = 0;
			for (auto j = pages.begin(); j != pages.end(); j++)
				if ((*j).getId() == (*i))
				{
					exist = 1;
					(*j).setChance(true);
				}
			if (!exist)
			{
				while (!exist)
				{
					if ((*iter).GetChance() == true)
					{
						(*iter).setChance(false);
					}
					else
					{
						(*iter).setid((*i));
						exist = 1;
					}
					
				}
			}
		}
		std::cout << "requesting " << (*i) << ": ";
		for (auto j = pages.begin(); j != pages.end(); j++)
			std::cout << (*j) << " ";
		std::cout << std::endl;
	}
}