#ifndef vote_hpp
#define vote_hpp

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace BitQA
{
	struct Voter
	{
		char Type;
		int ContentId;
	};
	
	class Vote
	{
	public:
		static vector<Voter> getContentIDVoted(string userID);
		static bool searchContentIDVoted(vector<Voter> voterList, Voter search);
	};
}

#endif
