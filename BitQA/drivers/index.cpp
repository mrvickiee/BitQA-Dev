#include <iostream>

#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

using namespace std;

using namespace cgicc;

int main(void)
{
	
	cout << "\n\r\n\r";
	
	try {
		Cgicc cgi;
		
		// Send HTTP header
		//cout << HTTPHTMLHeader() << endl;
		
		// Set up the HTML document
		cout << html() << head(title("cgicc example")) << endl;
		cout << body() << endl;
		
		// Print out the submitted element
		form_iterator name = cgi.getElement("name");
		if(name != cgi.getElements().end()) {
			// cout << "Your name: " << **name << endl;
		}
		
		cout << "Running 'SELECT 'Hello World!";
		
		try {
			sql::Driver *driver;
			sql::Connection *con;
			sql::Statement *stmt;
			sql::ResultSet *res;
			
			
			driver = get_driver_instance();
			con = driver->connect("tcp://db.csci222.com:3306", "root", "password");
			
			con->setSchema("BitQA");
			
			stmt = con->createStatement();
			res = stmt->executeQuery("SELECT 'Hello World!' AS _message");
			while (res->next()) {
				cout << "\t... MySQL replies: ";
				
				cout << res->getString("_message") << endl;
				cout << "\t... MySQL says it again: ";
				
				cout << res->getString(1) << endl;
			}
			delete res;
			delete stmt;
			delete con;
			
		} catch (sql::SQLException &e) {
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line "
			<< __LINE__ << endl;
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		}
		
		// Close the HTML document
		cout << body() << html();
	}
	catch(exception& e) {
		// handle any errors - omitted for brevity
	}
	
	return EXIT_SUCCESS;
}
