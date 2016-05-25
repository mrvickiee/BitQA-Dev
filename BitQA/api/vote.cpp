#include "../includes/html.hpp"
#include "../includes/json.hpp"
#include "../includes/database.hpp"

using namespace cgicc;
using namespace std;

int main()
{
	try {
		Cgicc cgicc;
		
		BitQA::JSON::getLoggedInStatus(cgicc);
		BitQA::JSON::displayHeader();
		
		string contentId = cgicc("contentId");
		string userId = cgicc("userId");
		string voteType = cgicc("voteType");
		string voteAction = cgicc("voteAction");
		
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

		if (voteAction == "vote") {
			
			if (voteType == "up") {
				res = stmt->executeQuery("CALL ProcUpvote(" + contentId + ", '" + userId + "');");
			} else if (voteType == "down") {
				res = stmt->executeQuery("CALL ProcDownvote(" + contentId + ", '" + userId + "');");
			}
			
		} else if (voteAction == "unvote") {
			
			if (voteType == "up") {
				res = stmt->executeQuery("CALL ProcUnUpvote(" + contentId + ", '" + userId + "');");
			} else if (voteType == "down") {
				res = stmt->executeQuery("CALL ProcUnDownvote(" + contentId + ", '" + userId + "');");
			}
			
		}
		
		res->next();
		// string qryResult = res->getString("result");
		
		cout << "{\"success\":\"true\"}";
		
	} catch (exception &e) {
		
		string error(e.what());
		
		BitQA::JSON::error("Exception pulled: ", error);
		
	}
	
	return 0;
}
