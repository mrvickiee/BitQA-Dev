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
		Comment(int CommentID);
		int getCommentID();
		string getDetails();
		string getVotes();
		string getUsername();
		string getCommentIDStr();
		
		string getContentID();
		string getOwnerID();
		
	private:
		Comment();
		int CommentID;
		int OwnerID;
		int ContentID;
		int CommentOwner;
	};
}

#endif
