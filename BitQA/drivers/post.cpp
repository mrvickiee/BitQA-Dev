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
	BitQA::HTML::displayHeader("Post Question", cgi);
	
	string response = "", questionTitle = "", questionDescription = "", questionTags = "", questionUser = "";
	auto error = false;
	
	// Check initial post
	CgiEnvironment environment = cgi.getEnvironment();
	
	if (environment.getRequestMethod() == "POST") {
		
		// Get Question
		try {
			CgiEnvironment environment = cgi.getEnvironment();
			const_cookie_iterator cci;
			
			string userName = "";
			string displayName = "";
			
			for (cci = environment.getCookieList().begin();
				 cci != environment.getCookieList().end();
				 cci++) {
				if (cci->getName() == "username") {
					userName = cci->getValue();
				} else if (cci->getName() == "displayname") {
					displayName = cci->getValue();
				}
			}
			
			if (userName == "") {
				error = true;
				response += "User not logged in. <a href='login.html'>Login</a> first.\n";
			}
			
			questionTitle = cgi("questionTitle");
            questionDescription = cgi("questionDescription");
            questionTags = cgi("questionTags");
            questionUser = userName;
			
			// Check response
			if (validate(questionTitle) && validate(questionDescription) && validate(questionTags)) {
				
				// Add to database
				try {
					addQuestion(questionTitle, questionDescription, questionTags, questionUser);
					
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
		
		if (error) {
			cout << "<div class=\"alert alert-danger\">" << endl;
			cout << "<strong>Error!</strong> " << response << endl;
			cout << "</div>";
		} else {
			
		
		cout << "<center><h1>Question posted successfully</h1>";
		cout << "<h4>James is processing your question and checking for memes...</h4>" << endl;
		cout << "<h5>View it <a  href= 'allquestions.html'>here</a></h5>" << endl;
		cout << "<br><br>" << endl;
		cout << "<img style='width:40%;' align='middle' src='https://cdn4.iconfinder.com/data/icons/ballicons-2-free/100/669348-letter-512.png'></center>" << endl;
		}
		
	}
	
	
	
	else {
		
		
        cout << "<h1>Post a new question</h1>";
        cout << "<h4>Provide a detailed description, and as many relevant tags to make the question more effective</h4><br>";
        cout << "<form data-ajax=\"false\" method=\"post\">";
        
        cout << "<div class=\"form-group\">" <<
        "<table> <tr class='row'><td style='width:300px'>Title:</td><td style='width: 80%'>" <<
        "<input type=\"text\" name=\"questionTitle\" class=\"form-control\" value='" <<
        questionTitle << "'></td></tr><tr height='10px'></tr><tr class='row'><td>Description:</td><td>" <<
        "<textarea name=\"questionDescription\" style=\"height: 100px\" class=\"form-control\">" << questionDescription
        << "</textarea></td></tr><tr height='10px'></tr><tr class='row'><td>Tags:</td><td><textarea name=\"questionTags\" style=\"height: 35px\" class=\"form-control\">" << questionTags <<
        "</textarea></td></tr></table>"
        
        << "<br><p><b>Note: </b>Tags must be surrounded with brackets like &lt;tag&gt;</p></div><input class=\"btn btn-primary\" type=\"submit\">";
        
        cout << "</form>";
		
		cout << BitQA::HTML::spacer(10);
		
		
		
	}
	
	BitQA::HTML::displayFooter();
	return 0;
}
