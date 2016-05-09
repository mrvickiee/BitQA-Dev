#ifndef comment_hpp
#define comment_hpp

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace BitQA
{
	class Comment
	{
	public:
		Comment(int ContentID);
		int getContentID();
		string getDetails();
		string getVotes();
		string getUsername();
		
	private:
		Comment();
		int ContentID;
	};
}

#endif
