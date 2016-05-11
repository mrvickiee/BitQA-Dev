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
		Comment(int CommentID, string CommentType);
		int getCommentID();
		string getDetails();
		string getVotes();
		string getUsername();
		
	private:
		Comment();
		int CommentID;
		int OwnerID;
		int ContentID;
		int CommentOwner;
		string CommentType;
	};
}

#endif
