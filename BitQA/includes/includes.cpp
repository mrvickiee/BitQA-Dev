#include "includes.hpp"

using namespace cgicc;
using namespace std;

void Includes::displayHeader(std::string title)
{
	cout << HTTPHTMLHeader() << endl
		<< "<!DOCTYPE html>" << endl
		<< html() << endl
		<< head() << endl
		<< cgicc::title() << title << cgicc::title() << endl
	
		// Mobile 1st
		<< "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">" << endl
	
		// CSS
		<< "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css\" />" << endl
		<< "<link rel=\"stylesheet\" href=\"/includes/css/style.css\" />" << endl
	
		// Scripts
		<< "<script type=\"text/javascript\" src=\"https://code.jquery.com/jquery-2.2.3.min.js\" defer></script>" << endl
		<< "<script type=\"text/javascript\" src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js\" defer></script>" << endl
	
		<< head() << endl;
	
	
	
	cout << body() << endl;
	
	// Navbar
	cout << "<nav class=\"navbar navbar-default navbar-fixed-top\">" << endl
		<< "<div class=\"container\">" << endl
		<< "<div class=\"navbar-header\">" << endl
			<< "<a class=\"navbar-brand\" href=\"#\">Bit QA</a>" << endl
		<< "</div>";
	
	cout << "<div id=\"navbar\" class=\"navbar-collapse collapse\"><ul class=\"nav navbar-nav\"><li class=\"active\"><a href=\"/\">Home</a></li><li><a href=\"/post/\">Post</a></li><li><a href=\"#\">Answers</a></li></ul>";
	
	cout << "<ul class=\"nav navbar-nav navbar-right\"><li><a href=\"./\">Login</a></li><li><a href=\"../navbar-static-top/\">Signup</a></li><li><a>Liam Frappell</a></li></ul>";
	
	cout << "</div>";
	
	cout << "</div></nav>";
	
	// Container
	cout << "<div class=\"bitqa-nav-spacer\"></div>"
		<< "<div class=\"container\">";
}

void Includes::displayFooter()
{
	cout << "</div>" << endl
		<< body() << endl
		<< html() << endl;
}
