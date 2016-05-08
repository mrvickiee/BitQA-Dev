#include "../process/question.hpp"
#include "../includes/html.hpp"
#include "../includes/database.hpp"

using namespace cgicc;
using namespace std;

int main()
{
	
	BitQA::Question question;
	
	{
		BitQA::HTML::displayHeader();
		
		/*
		 * Question
		 */
		cout << "<h1>" << question.getTitle() << "</h1>";
		cout << " <div class=\"container-fluid\"><div class=\"row\">";
			cout << "<div class=\"col-xs-1 col-sm-1 col-md-1 col-lg-1\">";
				cout << "<h3><a href=\"#\">&#128077;</a></h3>";
				cout << "<span><b>" << question.getVotes() << "</b></span>";
				cout << "<h3><a href=\"#\">&#128078;</a></h3>";
			cout << "</div>";
			cout << "<div class=\"col-xs-8 col-sm-8 col-md-8 col-lg-8\">";
				cout << "<br><p>" << question.getDetails() << "</p>";
				cout << "<p><i><b>Question by " << question.getUsername() << "</i></b></p>";
			cout << "</div>";
		cout << "</div></div>";
		
		
		/*
		 * Comments
		 */
		cout << " <div class=\"container-fluid\">";
		
		cout << "<div class=\"row\">";
			cout << "<div class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"></div>";
			cout << "<div class=\"col-xs-1 col-sm-1 col-md-1 col-lg-1\">";
			cout << "<h5><a href=\"#\">&#128077;</a></h5>";
			cout << "<span><b>" << question.getVotes() << "</b></span>";
			cout << "</div>";
			cout << "<div class=\"col-xs-5 col-sm-5 col-md-5 col-lg-5\">";
			cout << "<p>" << question.getDetails() << "</p>";
			cout << "<hr>";
			cout << "</div>";
		cout << "</div>";
		cout << "<div class=\"row\">";
			cout << "<div class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"></div>";
			cout << "<div class=\"col-xs-1 col-sm-1 col-md-1 col-lg-1\">";
			cout << "<h5><a href=\"#\">&#128077;</a></h5>";
			cout << "<span><b>" << question.getVotes() << "</b></span>";
			cout << "</div>";
			cout << "<div class=\"col-xs-5 col-sm-5 col-md-5 col-lg-5\">";
			cout << "<p>" << question.getDetails() << "</p>";
			cout << "</div>";
		cout << "</div>";
		
		cout << "</div>";
		
		cout << "<hr>";
		
		cout << BitQA::HTML::spacer(10);
		
		BitQA::HTML::displayFooter();
	}
	
	return 0;
}
