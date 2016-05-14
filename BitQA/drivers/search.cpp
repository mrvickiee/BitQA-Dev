#include "../process/question.hpp"
#include "../process/comment.hpp"
#include "../process/search.hpp"
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
		//Get search term from search bar
		string searchTerm;
		/*
		form_iterator fi = formData.getElement("textcontent");
		if(!fi->isEmpty() && fi != (*formData).end()) {
			cout << "<p>This 3is what was entered: " << **fi << " </p>" << endl;
		}
		string searchTerm = document.getElementById('navbar').value;
		cout << "document.getElementById('navbar\').value" << endl;
		*/
		
		//Create search object with term
		MySearch searchObj(searchTerm);	
		
		//If user bring up user page, if question bring up search results
		if(isUser(searchTerm))
		{
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

