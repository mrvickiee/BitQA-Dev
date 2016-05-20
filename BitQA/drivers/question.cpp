#include "../process/question.hpp"
#include "../process/comment.hpp"
#include "../includes/html.hpp"
#include "../includes/database.hpp"

using namespace cgicc;
using namespace std;

int main()
{
	
	BitQA::HTML::displayHeader();
	
	Cgicc cgicc;
	int id = 0;
	
	try {
		id = stoi(cgicc("id"));
		//id = 16955;
		
		BitQA::Question question(id);
		
		{
			
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
					cout << "<p><i><b>Questioned by " << question.getUsername() << "</i></b></p>";
				cout << "</div>";
			cout << "</div></div>";
			
			
			/*
			 * Question Comments
			 */
			
			cout << " <div class=\"container-fluid\">";
			
			vector<BitQA::Comment> commentList = question.getComments();
			
			for (int i = 0; i < commentList.size(); i++) {
				cout << "<div class=\"row\">";
				cout << "<div class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"></div>";
				cout << "<div class=\"col-xs-1 col-sm-1 col-md-1 col-lg-1\">";
				cout << "<h5><a href=\"#\">&#128077;</a></h5>";
				cout << "<span><b>" << commentList[i].getVotes() << "</b></span>";
				cout << "</div>";
				cout << "<div class=\"col-xs-5 col-sm-5 col-md-5 col-lg-5\">";
				cout << "<p>" << commentList[i].getDetails() << "</p>";
				cout << "<p><b>Comment by " << commentList[i].getUsername() << "</b></p>";
				cout << "<hr>";
				cout << "</div>";
				cout << "</div>";
			}
			
			
			cout << "</div>";
			cout << "<hr>";
			
			cout << BitQA::HTML::spacer(10);
			
		}
		
	} catch (sql::SQLException &e) {
		
		string error(e.what());
		
		BitQA::HTML::error("There was an error viewing your question",
						   "Please go <a href=\"/\">home</a><p>Details: " + error + "</p>"
						   );
		
	} catch (exception &e) {
		
		string error(e.what());
		
		BitQA::HTML::error("There was an error viewing your question",
						   "Please go <a href=\"/\">home</a><p>Details: " + error + "</p>"
						   );
		
	}
	
	BitQA::HTML::displayFooter();
	
	return 0;
}
