#include "post.hpp"
#include "includes.hpp"

using namespace std;
using namespace cgicc;

int main()
{
	Includes::displayHeader();
	
	cout << "<div class=\"row\">";
	
	cout << "<h1>Welcome to Bit QA, <span>Liam</span></h1>" << endl
		<< "<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean tempus blandit metus, id aliquet orci lacinia eget. Sed quis tempor turpis. In ornare lacus ut lacus tincidunt, nec euismod dolor tristique.</p>" << endl;
	
	cout << "<h3>Attempting DB Connection</h3>" << endl;
	
	try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::ResultSet *res;
		
		
		driver = get_driver_instance();
		con = driver->connect("tcp://db.csci222.com:3306", "root", "password");
		
		con->setSchema("BitQA");
		
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
		cout << "<p>Response: <span class=\"label label-danger\">Error " << e.getErrorCode() << "</span></p>" << endl;
	}
	
	cout << "</div>" << endl;
	
	Includes::displayFooter();
	
	return 0;
}
