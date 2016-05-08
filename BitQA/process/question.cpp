#include "question.hpp"

BitQA::Question::Question()
{
	
}

vector<int> BitQA::Question::getContentID()
{
	vector<int> contentID;
	
	for (int i = 0; i < 5; i++) {
		contentID.push_back(i);
	}
	
	return contentID;
}

string BitQA::Question::getTitle()
{
	return "Question Title";
}

string BitQA::Question::getDetails()
{
	return "Question DetailsQuestion DetailsQuestion DetailsQuestion DetailsQuestion DetailsQuestion DetailsQuestion DetailsQuestion DetailsQuestion DetailsQuestion DetailsQuestion";
}

string BitQA::Question::getVotes()
{
	return "17";
}

string BitQA::Question::getUsername()
{
	return "Liam Frappell";
}
