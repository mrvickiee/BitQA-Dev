#include "../process/question.hpp"
#include "../process/comment.hpp"
#include "../process/search.hpp"
#include "../includes/html.hpp"
#include "../includes/database.hpp"


using namespace cgicc;
using namespace std;
using namespace BitQA;


/*
 * Issues
 * - get string from navbar
 * - Add tag if not on list
 * - Checkbox for unanswered/answered questions?
 * - StringToTag not working
 * - testA not outputing
 */ 


bool isUser(string searchTerm) {
		if(searchTerm.at(0) == '@') {
			return true;
		}
		return false;	
}

void searchResults() {
	
	cout << "<div class=\"row\">";
	cout << "<h2>Search results</h2><br>" << endl;
	cout << "<ul id = \"list\">" << endl;
	cout << "<li> </li>" << endl;
	cout << "<li> </li>" << endl;
	cout << "</ul>" << endl;	
	cout << "</div>" << endl;
		
}

int main() {
		
	BitQA::HTML::displayHeader();
	cgicc::Cgicc cgi;

	CgiEnvironment environment = cgi.getEnvironment();
	if(environment.getRequestMethod() == "POST"){
		string test = cgi("search");
		cout << "<h1> " << test << "</h1>" << endl;
	}	


	//Get search term from search bar
	string searchTerm = "@Leon Bambrick";
	string testA = "<c++>";
	cout << "<h3>" << testA << "</h3>";
	MySearch testObject(testA);


    cout << "<form data-ajax=\"false\" method=\"post\">";  
    cout << "<div class=\"form-group\">" << "<input type=\"text\" name=\"search\" class=\"form-control\">" << "</div><input class=\"btn btn-primary\" type=\"submit\">";
    cout << "</form>";
	
	
	//Runs with <php><mysql>
	testObject.getQuestion();
	

	

	if(environment.getRequestMethod() == "POST"){		
		cout << "<h1> Hello Benjamin </h1> " << endl;
		//Get search term from search bar
		string searchTerm = "@Leon Bambrick";
	
		
		//Create search object with term
		MySearch searchObj(searchTerm);
		
		cout << "<h2> Search results for \"" << searchObj.getSearchTerm() <<  "\"</h2>" << endl;	
		
		//If user bring up user page, if question bring up search results
		if(isUser(searchTerm))
		{
			//Show link to user page
			int userID = searchObj.getUser();
			if(userID == -1) {
				cout << "<h2> User not found </h2>";
			}else {	
				string userPage = to_string(userID);
				userPage = (BitQA::HTML::HOST + "/profile.html?username=" + userPage);
				cout << "<a href=\"" << userPage << "\">" << searchObj.getSearchTerm() << "</a>" << endl;
			}
		}else
		{
			searchObj.getQuestion();
		}

	}
	
	
	
	
	BitQA::HTML::displayFooter();	
}
