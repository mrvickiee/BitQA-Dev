#include "vote.hpp"
#include "../includes/database.hpp"

using namespace std;

vector<BitQA::Voter> BitQA::Vote::getContentIDVoted(string userID)
{
	vector<BitQA::Voter> contentList;
	
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	
	
	driver = get_driver_instance();
	con = driver->connect(BitQA::Database::HOST,
						  BitQA::Database::USERNAME,
						  BitQA::Database::PASSWORD
						  );
	
	con->setSchema(BitQA::Database::SCHEMA);
	
	stmt = con->createStatement();
	
	Voter voter;
	
	res = stmt->executeQuery("SELECT contentId FROM tblUpvotes WHERE userId = '" + userID + "'");
	
	
	while (res->next()) {
		
		voter.Type = 'U';
		voter.ContentId = res->getInt("contentId");
		
		contentList.push_back(voter);
	}
	
	res = stmt->executeQuery("SELECT contentId FROM tblDownvotes WHERE userId = '" + userID + "'");
	
	
	while (res->next()) {
		
		voter.Type = 'D';
		voter.ContentId = res->getInt("contentId");
		
		contentList.push_back(voter);
	}
	
	delete res;
	delete stmt;
	delete con;
	
	return contentList;
}

bool BitQA::Vote::searchContentIDVoted(vector<BitQA::Voter> voterList, BitQA::Voter search)
{
	for (int i = 0; i < voterList.size(); i++) {
		
		if ((voterList[i].Type == search.Type) &&
			(voterList[i].ContentId == search.ContentId)
		) {
			return true;
		}
	}
	
	return false;
}
