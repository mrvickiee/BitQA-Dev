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
 * - Checkbox for unanswered/answered questions?
 */ 


bool isUser(string searchTerm) {
		if(searchTerm.at(0) == '@') {
			return true;
		}
		return false;	
}

int main() {
	
	cgicc::Cgicc cgi;
	BitQA::HTML::displayHeader("Search", cgi);

	string searchTerm;
	

	CgiEnvironment environment = cgi.getEnvironment();
	
	cout << "<form method=\"post\" action=\"\">"; 
	cout << "<div class =\"form=group\">";
    cout << "<button type=\"submit\" class=\"btn btn-default\"> Filter unanswered </button> " <<endl;
    cout << "<input type=\"hidden\" name=\"search\" value=\"" << cgi("search") << "\">" << endl;
    cout << "<input type=\"hidden\" name=\"filterPress\" value=\"true\">" << endl;
	cout << "</div>";
	cout << "</form>";
	
	
	if(environment.getRequestMethod() == "POST"){		
		
		//Get search term from search bar
		searchTerm = cgi("search");

		//Create search object with term
		MySearch searchObj(searchTerm);
		
		bool filter = false;
		if(cgi("filterPress") == "true") {
			filter = true;
		}
		
		
		cout << "<h2> Search results for \"" << searchObj.getSearchTerm() <<  "\"</h2>" << endl;
		
		//If user bring up user page, if question bring up search results
		if(isUser(searchTerm))
		{
			//Show link to user page
			int userID = searchObj.getUser();
			if(userID != -1) {
				cout << "<script>window.location.href=\""
				<< BitQA::HTML::HOST + "/profile.html?username=" + searchObj.getSearchTerm()
				<<"\"</script>" << endl;
			}
		}else
		{
			if(!filter) {
				searchObj.getQuestion(filter);
			}else
			{
				searchObj.getQuestion(filter);
			}
		}
		
		
	}
	
	BitQA::HTML::displayFooter();	
}
