#ifndef question_hpp
#define question_hpp

#include <string>
#include <vector>
#include "comment.hpp"

using std::string;
using std::vector;

namespace BitQA
{
	class Question
	{
	public:
		Question(int QuestionID);
		vector<int> getContentID();
		string getTitle();
		string getDetails();
		string getVotes();
		string getUsername();
		vector<Comment> getComments();
		string getQuestionContentID();
		string getQuestionID();
		string getQuestionOwner();
		
		
	private:
		Question();
		int QuestionID;
		int ContentID;
		string QuestionOwner;
	};
}

#endif
