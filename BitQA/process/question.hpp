#ifndef question_hpp
#define question_hpp

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace BitQA
{
	class Question
	{
	public:
		Question();
		vector<int> getContentID();
		string getTitle();
		string getDetails();
		string getVotes();
		string getUsername();
		
	private:
		int ID;
	};
}

#endif
