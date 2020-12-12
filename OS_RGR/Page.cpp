#include "Page.h"

Page::Page(size_t id) : id(id), chance(0)
{

}

Page::Page(const Page& toCopy) : id(toCopy.id), chance(toCopy.chance)
{

}

Page::Page(Page&& toCopy) : id(toCopy.id), chance(toCopy.chance)
{

}

Page& Page::operator =(const Page& toCopy)
{
	this->id = toCopy.id;
	this->chance = toCopy.chance;
	return *this;
}

Page& Page::operator =(Page&& toCopy)
{
	this->id = toCopy.id;
	this->chance = toCopy.chance;
	return *this;
}

Page::~Page()
{

}

bool Page::setChance(bool chance)
{
	this->chance = chance;
	return this->chance;
}

size_t Page::getId()
{
	return this->id;
}

void Page::setid(size_t id)
{
	this->id = id;
}

bool Page::GetChance()
{
	return this->chance;
}

bool operator==(const Page& page1, const Page& page2)
{
	return page1.id == page2.id;
}

std::ostream& operator <<(std::ostream& out, const Page& page)
{
	out << page.id <<"("<< page.chance<<")";
	return out;
}

