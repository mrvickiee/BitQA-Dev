#include "comment.hpp"

BitQA::Comment::Comment(int ContentID)
{
	this->ContentID = ContentID;
}

int BitQA::Comment::getContentID()
{
	return this->ContentID;
}

string BitQA::Comment::getDetails()
{
	return "Question Comment Question Comment Question Comment Question Comment Question Comment Question Comment Question Comment";
}

string BitQA::Comment::getVotes()
{
	return "4";
}

string BitQA::Comment::getUsername()
{
	return "Daniel West";
}

