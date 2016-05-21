#include "../includes/html.hpp"
#include "../includes/database.hpp"

using namespace std;
using namespace cgicc;

void printKnownUser()
{
	cout << "<h5>Welcome back, <span>" << BitQA::HTML::getDisplayName() << "</span></h5>" << endl;
	cout << "<br><br><iframe width=\"853\" height=\"480\" src=\"https://www.youtube.com/embed/b_KfnGBtVeA?rel=0&amp;controls=0&amp;showinfo=0&amp;autoplay=1\" frameborder=\"0\" allowfullscreen></iframe>";
}

void printUnknownUser()
{
	cout << "<h5>The world's greatest StackOverflow Clone.</h5>";
	cout << "<p><a href=\"/login.html\">Login</a> or <a href=\"/signup.html\">Signup</a> to get started</p>";
	cout << "<br><br><iframe width=\"853\" height=\"480\" src=\"https://www.youtube.com/embed/b_KfnGBtVeA?rel=0&amp;controls=0&amp;showinfo=0&amp;autoplay=1\" frameborder=\"0\" allowfullscreen></iframe>";
}

int main()
{
	BitQA::HTML::displayHeader();
	
	cout << "<center><div class=\"row\">";
	cout << "<h1>Bit QA - The World's Questions</h1>";
	
	if (BitQA::HTML::getLoggedInStatus()) {
		printKnownUser();
	} else {
		printUnknownUser();
	}
	
	cout << "</div></center>" << endl;
	
	BitQA::HTML::displayFooter();
	
	return 0;
}
