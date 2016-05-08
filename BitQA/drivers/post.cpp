#include "../process/post.hpp"
#include "../includes/html.hpp"
#include "../includes/database.hpp"

using namespace cgicc;
using namespace std;

void addQuestion(string questionTitle, string questionDescription, string questionTags, string questionUser)
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
	
	prep_stmt = con->prepareStatement("CALL ProcInsertQuestion(?,?,?,?);");
	prep_stmt->setString(1, questionTitle);
	prep_stmt->setString(2, questionDescription);
    prep_stmt->setString(3, questionTags);
    prep_stmt->setString(4, questionUser);
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
	string response = "", questionTitle = "", questionDescription = "", questionTags = "", questionUser = "";
	auto error = false;
	
	// Check initial post
	CgiEnvironment environment = cgi.getEnvironment();
	
	if (environment.getRequestMethod() == "POST") {
		
		// Get Question
		try {
			questionTitle = cgi("questionTitle");
            questionDescription = cgi("questionDescription");
            questionTags = cgi("questionTags");
            //questionUser = cgi("questionUser"); //GET FROM COOKIE
            questionUser = "100";
			
			// Check response
			if (validate(questionTitle) && validate(questionDescription) && validate(questionTags)) {
				
				// Add to database
				try {
					addQuestion(questionTitle, questionDescription, questionTags, questionUser);
					
					cout << cgicc::HTTPRedirectHeader(BitQA::HTML::HOST + "/post.html") << endl;
					
				} catch(sql::SQLException &e) {
					error = true;
					response += "Error storing into Database: " + string(e.what()) + "<br>";
				}
				
			} else {
				error = true;
				response += "Question needs to be valid<br>";
			}
			
		} catch (exception &e) {
			error = true;
			response += "Error getting post: " + string(e.what()) + "<br>";
		}
		
	}
	
	{
		BitQA::HTML::displayHeader();
		
        cout << "<h1>Post a new question</h1>";
        cout << "<h4>Provide a detailed description, and as many relevant tags to make the question more effective</h4><br>";
        cout << "<form data-ajax=\"false\" method=\"post\">";
        
        cout << "<div class=\"form-group\">" <<
        "<table> <tr><td>Title:</td><td>" <<
        "<input type=\"text\" name=\"questionTitle\" class=\"form-control\">" <<
        questionTitle << "</td> <tr> <td>Description:</td><td>" <<
        "<textarea name=\"questionDescription\" style=\"height: 100px\" class=\"form-control\">" << questionDescription
        << "</textarea></td></tr><tr><td>Tags:</td><td><textarea name=\"questionTags\" style=\"height: 100px\" class=\"form-control\">" << questionTags <<
        "</textarea></td></tr></table>"
        
        << "</div><input class=\"btn btn-primary\" type=\"submit\">";
        
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
