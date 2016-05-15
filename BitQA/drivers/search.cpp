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
	
	
	vector<int> questionResults;


	//Create search object with term
	//MySearch searchObj("<php><mysql>");
	/*cout << "<h1> Test " << searchObj.getSearchTerm() << "</h1>" <<endl;
	questionResults = searchObj.getQuestion();
	
	cout << "<h1> Test " << searchObj.getSearchTerm() << "</h1>" <<endl;
	for(vector<int>::iterator it = questionResults.begin(); it != questionResults.end(); ++it) {
		cout << "<p>This" << *it << "</p>" << endl;
	}
	*/
	

		//Get search term from search bar
		string searchTerm = "@Leon Bambrick";
		string testA = "<php><mysql>";
	
		
		//Create search object with term
		MySearch searchObj(searchTerm);
			int userID = searchObj.getUser();	
			string userPage = to_string(userID);
			userPage = (BitQA::HTML::HOST + "/profile.html?username=" + userPage);
			cout << "<h2> Search results </h2>" << endl;
			cout << "<a href=\"" << userPage << "\">" << searchObj.getSearchTerm() << "</a>" << endl;

	

	if(environment.getRequestMethod() == "POST"){		
		cout << "<h1> Hello Benjamin </h1> " << endl;
		//Get search term from search bar
		string searchTerm = "@Leon Bambrick";
	
		
		//Create search object with term
		MySearch searchObj(searchTerm);
		
		cout << "<h2> Search results" << searchObj.getSearchTerm() <<  "</h2>" << endl;	
		
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
			questionResults = searchObj.getQuestion();
			
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

	/*
	if(environment.getRequestMethod() == "POST"){
		
		    form_iterator fi = formData.getElement("search");
    if( !fi->isEmpty() && fi != (*formData).end()) {
		cout << "<p> Data entered: " << **fi << "</p>" << endl;
	}

		try{
			string searchTerm = cgi("search");
			cout << "<h1> " << searchTerm << "</h1>" << endl;
		}catch(exception &e){
			string error(e.what());
			BitQA::HTML::error("There was an error viewing your question",
						   "Please go <a href=\"/\">home</a><p>Details: " + error + "</p>");
        }
		
	}
	
	
	if(environment.getRequestMethod() == "POST"){
		string test = cgi("search");
		cout << "<h1> " << test << "</h1>" << endl;
	}
	
    cout << "<form data-ajax=\"false\" method=\"post\">";  
    cout << "<div class=\"form-group\">" << "<input type=\"text\" name=\"search\" class=\"form-control\">" << "</div><input class=\"btn btn-primary\" type=\"submit\">";
    cout << "</form>";
    */ 
    
