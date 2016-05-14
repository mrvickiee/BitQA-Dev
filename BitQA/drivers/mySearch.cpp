#include "../process/question.hpp"
#include "../process/comment.hpp"
#include "../process/mySearch.hpp"
#include "../process/post.hpp"
#include "../includes/html.hpp"
#include "../includes/database.hpp"


using namespace cgicc;
using namespace std;
using namespace BitQA;

int parseTerm(string searchTerm) {
		
		if(searchTerm.at(0) == '@') {
			return 0;
		}
		
		//Else check if question
		return 1;
		
		//If not question bring up any content related
}

int main() {
		
	cgicc::Cgicc cgi;
	
	
	//Get search term from search bar
	string searchTerm;
	
	//Determine what it is
	int type = -1;
	type = parseTerm(searchTerm);
	
	//Create search object with term
	mySearch searchObj(searchTerm);
	
	
	switch(type)
	{
		case 0:
			//Directs to user page
			searchObj.getUser();
			break;
		case 1:
			//Directs to question page
			searchObj.getQuestion();
			break;
		case 2:
			//Brings up search results page as no user or question was found
			//mySearch.getContentID();
			break;
		default:
			break;
			
	};
	
	
	
	}
	

/*
void selectFromDB() {
		try {
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
		
		cout << "<p>Query: <code>SELECT 'Hello World!' AS _message</code>:</p>";
		res = stmt->executeQuery("SELECT 'Hello World!' AS _message");
		
		while (res->next()) {
			cout << "<p>Response: <span class=\"label label-success\">" << res->getString("_message") << "</span></p>" << endl;
		}
		
		delete res;
		delete stmt;
		delete con;
		
	} catch (sql::SQLException &e) {
		cout << "<p>Response Test Change: <span class=\"label label-danger\">Error " << e.getErrorCode() << "</span></p>" << endl;
	}
}
*/ 

