#include "html.hpp"

using namespace cgicc;
using namespace std;

#if DEBUG
	const string BitQA::HTML::HOST = "http://csci222.local";
#else
	const string BitQA::HTML::HOST = "https://csci222.com";
#endif

void BitQA::HTML::displayHeader(std::string title)
{
	cout << HTTPHTMLHeader() << endl
		<< "<!DOCTYPE html>" << endl
		<< html() << endl
		<< head() << endl
		<< cgicc::title() << title << cgicc::title() << endl
	
		// Mobile 1st
		<< "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">" << endl
	
		// CSS
		<< "<link rel=\"stylesheet\" href=\"/includes/css/bootstrap.min.css\" />" << endl
		<< "<link rel=\"stylesheet\" href=\"/includes/css/style.css\" />" << endl
	
		// Scripts
		<< "<script type=\"text/javascript\" src=\"/includes/javascript/jquery.min.js\"></script>" << endl
		<< "<script type=\"text/javascript\" src=\"/includes/javascript/bootstrap.min.js\"></script>" << endl
		<< "<script type=\"text/javascript\" src=\"/includes/javascript/main.js\"></script>" << endl
	
		<< head() << endl;
	
	
	
	cout << body() << endl;
	
	// Navbar
	cout << "<nav class=\"navbar navbar-default navbar-fixed-top\">" << endl
		<< "<div class=\"container\">" << endl
		<< "<div class=\"navbar-header\">" << endl
			<< "<a class=\"navbar-brand\" href=\"index.html\">Bit QA</a>" << endl
		<< "</div>";
	
	cout << "<div id=\"navbar\" class=\"navbar-collapse collapse\"><ul class=\"nav navbar-nav\"><li class=\"active\"><a href=\"/\">Home</a></li><li><a href=\"/post.html\">Post</a></li><li><a href=\"#\">Answers</a></li></ul>";
	
	cout << "<ul class=\"nav navbar-nav navbar-right\"><li><a href=\"login.html\">Login</a></li><li><a href=\"signup.html\">Signup</a></li><li><a>Liam Frappell</a></li></ul>";
	
	cout << "</div>";
	
	cout << "</div></nav>";
	
	// Container
	cout << "<div class=\"bitqa-nav-spacer\"></div>"
		<< "<div class=\"container\">";
}

void BitQA::HTML::displayFooter()
{
	cout << "</div>" << endl
		<< body() << endl
		<< html() << endl;
}

std::string BitQA::HTML::spacer(int height)
{
	return "<div style=\"margin-top: " + to_string(height) + "px;\"></div>";
}

void BitQA::HTML::error(std::string title, std::string message)
{
	cout << "<div class=\"modal fade\" id=\"errorModal\" tabindex=\"-1\" role=\"dialog\"><div class=\"modal-dialog\" role=\"document\"><div class=\"modal-content\"><div class=\"modal-header\"><h4 class=\"modal-title\">Error</h4></div>";
	
	cout << "<div class=\"modal-body\"><div class=\"panel panel-danger\">"
		<< "<div class=\"panel-heading\">" << title << "</div>"
		<< "<div class=\"panel-body\">" << message << "</div>"
		<< "</div>";
	
	cout << "</div><div class=\"modal-footer\"><button type=\"button\" class=\"btn btn-default\" data-dismiss=\"modal\">Close</button></div></div></div></div>";
	
	cout << "<script type=\"text/javascript\">$(document).ready(function(){showError()});</script>";
}
