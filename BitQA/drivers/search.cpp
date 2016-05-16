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
 * - Add tag if not on list
 * - Checkbox for unanswered/answered questions?
 * - StringToTag not working
 */ 


bool isUser(string searchTerm) {
		if(searchTerm.at(0) == '@') {
			return true;
		}
		return false;	
}

int main() {
		
	BitQA::HTML::displayHeader();
	cgicc::Cgicc cgi;

	CgiEnvironment environment = cgi.getEnvironment();
	if(environment.getRequestMethod() == "POST"){		

		//Get search term from search bar
		string searchTerm;
		searchTerm = cgi("search");
	
		
		//Create search object with term
		MySearch searchObj(searchTerm);
		
		cout << "<h2> Search results for \"" << searchObj.getSearchTerm() <<  "\"</h2>" << endl;	
		
		//If user bring up user page, if question bring up search results
		if(isUser(searchTerm))
		{
			//Show link to user page
			int userID = searchObj.getUser();
			if(userID != -1) {
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
