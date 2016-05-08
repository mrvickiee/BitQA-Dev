#ifndef question_hpp
#define question_hpp

#include <string>

using std::string;

namespace BitQA
{
	class Question
	{
	public:
		Question();
		string getTitle();
		string getDetails();
		string getVotes();
		string getUsername();
		
	private:
		string Something;
	};
}

#endif
