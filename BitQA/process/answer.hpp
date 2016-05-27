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
		string getUserID();
		string getDetails();
		string getVotes();
		string getUsername();
		int getContentID();
		vector<Comment> getComments();
		bool isAcceptedAnswer();
		
	private:
		Answer();
		int AnswerID;
		int ContentID;
		string AnswerOwner;
		
		
	};
};

#endif
