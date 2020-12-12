#pragma once
#include <iostream>

class Page
{
private:
	size_t id;
	bool chance = 0;
protected:
public:
	Page(size_t id);
	Page(const Page&);
	Page(Page&&);
	Page& operator =(const Page&);
	Page& operator =(Page&&);
	~Page();

	bool setChance(bool chance);
	size_t getId();
	bool GetChance();
	void setid(size_t id);

	friend bool operator==(const Page&, const Page&);

	friend std::ostream& operator <<(std::ostream&, const Page&);
};

