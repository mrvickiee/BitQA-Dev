#include "post.h"

using namespace std;

Post::Post()
{
	FirstName = "Default";
}

string Post::getFirstName()
{
	return "Asjad";
}

void Post::setFirstName(string Name)
{
	this->FirstName = Name;
}
