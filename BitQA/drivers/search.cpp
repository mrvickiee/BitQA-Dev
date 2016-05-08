#include "../process/post.hpp"
#include "../includes/html.hpp"
#include "../includes/database.hpp"

using namespace cgicc;
using namespace std;


//Main and functionality


int main() {
	string search;
	
	cgicc::Cgicc cgi;
	
	
	//Get search term
			BitQA::HTML::displayHeader();
		
		cout << "<h1>Post</h1>";
		cout << "Ask a question to Bit QA";
		cout << "<form data-ajax=\"false\" method=\"post\">";
		
		cout << "<div class=\"form-group\">"
			<< "<textarea name=\"question\" style=\"height: 100px\" class=\"form-control\">"
			<< search
			<< "</textarea></div><input class=\"btn btn-primary\" type=\"submit\">";
		
		cout << "</form>";
	
	//Parse term to determine what table to search
	
	
	//Search table
	
	
	//Return results
	
	
	}
	
	
void searchUser(string search) {

		//Search DB
}


void searchTag(string search) {
	
		//Search DB
	
}

