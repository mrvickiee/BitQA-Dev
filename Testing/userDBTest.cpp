#include "../process/search.hpp"
#include "../includes/html.hpp"
#include "../includes/database.hpp"


using namespace cgicc;
using namespace std;
using namespace BitQA;




int main() {
	
	cgicc::Cgicc cgi;
	BitQA::HTML::displayHeader("Search", cgi);
	int id, username, age;
	string display, creation, location, email; 
	
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
		res = stmt->executeQuery("SELECT * FROM tblUser WHERE id = 53");

		while (res->next()) {
			id = (res->getInt("id"));
			username = (res->getInt("username"));
			display = (res->getString("displayname"));
			creation = (res->getString("creationdate"));
			age = (res->getInt("age")); 
			location = (res->getString("location"));
			email = (res->getString("email"));
		}
		
		cout << "<h2> Results </h2>" << endl;
		cout << "<p>" << id << "</p>" << endl;
		cout << "<p>" << username << "</p>" << endl;
		cout << "<p>" << display << "</p>" << endl;
		cout << "<p>" << creation << "</p>" << endl;
		cout << "<p>" << age << "</p>" << endl;
		cout << "<p>" << location << "</p>" << endl;
		cout << "<p>" << email << "</p>" << endl;
		
		delete res;
		delete stmt;
		delete con;
		
	} catch (sql::SQLException &e) {
		cout << "<p>Error outputting results</p>" << endl;
	}

	
	BitQA::HTML::displayFooter();	
}
