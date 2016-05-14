#include "../process/question.hpp"
#include "../process/comment.hpp"
#include "../process/mySearch.hpp"
#include "../includes/html.hpp"
#include "../includes/database.hpp"


using namespace cgicc;
using namespace std;
using namespace BitQA;


bool isUser(string searchTerm) {
		if(searchTerm.at(0) == '@') {
			return true;
		}
		return false;	
}

void searchResults() {
	
	cout << "<div class=\"row\">";
	cout << "<h2>Search results</h2><br>" << endl;
	
	cout << "</div>" << endl;
		
}

int main() {
		
	BitQA::HTML::displayHeader();
	cgicc::Cgicc cgi;
	
	CgiEnvironment environment = cgi.getEnvironment();
	
	
	//Get search term from search bar
	string searchTerm;
	
	if(environment.getRequestMethod() == "POST"){
		//Create search object with term
		MySearch searchObj(searchTerm);	
		
		//If user bring up user page, if question bring up search results
		if(isUser(searchTerm))
		{
			int userID = searchObj.getUser();
			
			//Redirect to user page with found ID
			cout << cgicc::HTTPRedirectHeader(BitQA::HTML::HOST + "/browse.html") << endl;
	
		}else
		{
			int questionID = -1;
			questionID = searchObj.getQuestion();
			
			if(questionID == -1)
			{
				//Redirect to page with search results
				searchResults();
			}else {
				//Redirect to question page with QuestionID
				cout << cgicc::HTTPRedirectHeader(BitQA::HTML::HOST + "/question.html") << endl;
			}
			

		}	
	}
	
	BitQA::HTML::displayFooter();	
}

