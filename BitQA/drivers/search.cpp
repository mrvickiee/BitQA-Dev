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
	Cgicc formData;
	CgiEnvironment environment = cgi.getEnvironment();
	
	string searchTerm = "@Leon Bambrick";

	/*	TESTING
	//Attempt form with information
	string searchTerm = "@Leon Bambrick";
	cout << "<form data-ajax=\"false\" method=\"post\">"<<endl;
        
    cout << "<div class=\"form-group\">" << endl;
        
    cout << "<label for= \"Username\"> Username </label>" << endl;
    cout << "<input type=\"text\" class=\"form-control\" id=\"userName\" name=\"userName\" placeholder = \"Enter Username\"> " << endl;
        
    cout << "</div>" << endl;

    


    if(environment.getRequestMethod() == "POST"){
		try{
			searchTerm = cgi("search");
			cout << "<h1> " << searchTerm << "</h1>" << endl;
		}catch(exception &e){
			string error(e.what());
			BitQA::HTML::error("There was an error viewing your question",
						   "Please go <a href=\"/\">home</a><p>Details: " + error + "</p>");
        }
		
	}
	
	//Create search object with term
	MySearch searchObj(searchTerm);
	
	
	//Redirect to user page with found ID
	int userID = searchObj.getUser();	
	string userPage = to_string(userID);
	userPage = (BitQA::HTML::HOST + "/profile.html?username=" + userPage);
	cout << "<a href=\"" << userPage << "\">" << searchObj.getSearchTerm() << "</a>" << endl;
	*/

	
	        
	
	
	if(environment.getRequestMethod() == "POST"){		
		cout << "<h1> Hello Benjamin </h1> " << endl;
		//Get search term from search bar
		string searchTerm = "@Leon Bambrick";

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
			//Show link to user page
			int userID = searchObj.getUser();	
			string userPage = to_string(userID);
			userPage = (BitQA::HTML::HOST + "/profile.html?username=" + userPage);
			cout << "<h2> Search results </h2>" << endl;
			cout << "<a href=\"" << userPage << "\">" << searchObj.getSearchTerm() << "</a>" << endl;
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

