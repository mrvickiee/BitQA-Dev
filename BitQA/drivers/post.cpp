#include "../process/post.hpp"
#include "../includes/html.hpp"
#include "../includes/database.hpp"

using namespace cgicc;
using namespace std;

void addQuestion(string question)
{
	sql::Driver *driver;
	sql::Connection *con;
	sql::PreparedStatement *prep_stmt;
	
	driver = get_driver_instance();
	con = driver->connect(BitQA::Database::HOST,
						  BitQA::Database::USERNAME,
						  BitQA::Database::PASSWORD
						  );
	
	con->setSchema(BitQA::Database::SCHEMA);
	
	prep_stmt = con->prepareStatement("INSERT INTO test(id, label) VALUES (?, ?)");
	prep_stmt->setString(1, "value 1");
	prep_stmt->setString(2, question);
	prep_stmt->execute();
	
	delete prep_stmt;
	delete con;
	
}

bool validate(string question)
{
	if (question.length() > 0) {
		return true;
	} else {
		return false;
	}
}

int main()
{
	
	cgicc::Cgicc cgi;
	string response = "", question = "";
	auto error = false;
	
	// Check initial post
	CgiEnvironment environment = cgi.getEnvironment();
	
	if (environment.getRequestMethod() == "POST") {
		
		// Get Question
		try {
			question = cgi("question");
		} catch (exception &e) {
			error = true;
			response += "Error getting post: " + string(e.what()) + "<br>";
		}
		
		// Check response
		if (validate(question)) {
			cout << cgicc::HTTPRedirectHeader(BitQA::HTML::HOST + "/view/") << endl;
		} else {
			error = true;
			response += "Question needs to be valid<br>";
		}
		
		// Add to database
		try {
			addQuestion(question);
		} catch(sql::SQLException &e) {
			error = true;
			response += "Error storing into Database: " + string(e.what()) + "<br>";
		}
		
	}
	
	{
		BitQA::HTML::displayHeader();
		
		cout << "<h1>Post</h1>";
		cout << "Ask a question to Bit QA";
		cout << "<form data-ajax=\"false\" method=\"post\">";
		
		cout << "<div class=\"form-group\">"
			<< "<textarea name=\"question\" style=\"height: 100px\" class=\"form-control\">"
			<< question
			<< "</textarea></div><input class=\"btn btn-primary\" type=\"submit\">";
		
		cout << "</form>";
		
		cout << BitQA::HTML::spacer(10);
		
		if (environment.getRequestMethod() == "POST") {
			if (error) {
				cout << "<div class=\"alert alert-danger\">" << endl;
				cout << "<strong>Error!</strong> " << response << endl;
				cout << "</div>";
			} else {
				cout << "<div class=\"alert alert-success\">" << endl;
				cout << "<strong>Success!</strong> Added to Database." << endl;
				cout << "</div>";
			}
		}
		
		BitQA::HTML::displayFooter();
	}
	
	return 0;
}
