#include "../process/question.hpp"
#include "../process/comment.hpp"
#include "../process/search.hpp"
#include "../process/post.hpp"
#include "../includes/html.hpp"
#include "../includes/database.hpp"

using namespace cgicc;
using namespace std;
using namespace BitQA;

int isUser(BitQA::Search *mySearch) {
		string check = mySearch->getSearchTerm();
		if(check.at(0) == '@') {
			return 0;
		}
		
		//Else check if question or tag
		return 1;
}

int main() {
		
	cgicc::Cgicc cgi;
	
	//Default sets searh term to @liam
	BitQA::Search mySearch();
	
	/*switch(isUser(mySearch))
	{
		case 0:
			mySearch.getUser();
		case 1:
		
		case 2:
		
		default:
			
	};
	*/
	//Search table
	
	
	//Return results
	
	
	}
	


//Main and functionality
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

