#ifndef answer_hpp
#define answer_hpp

#include <string>
#include <vector>
#include "comment.hpp"

using std::string;
using std::vector;

namespace BitQA
{
	class Answer
	{
		
	public:
		Answer(int AnswerID);
		int getAnswerID();
		string getDetails();
		string getVotes();
		string getUsername();
		vector<Comment> getComments();
		
	private:
		Answer();
		int AnswerID;
		int ContentID;
		int AnswerOwner;
		
		
	};
};

#endif
