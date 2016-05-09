#include "../process/question.hpp"
#include "../process/comment.hpp"
#include "../includes/html.hpp"
#include "../includes/database.hpp"

using namespace cgicc;
using namespace std;

int main()
{
	
	Cgicc cgicc;
	int id = 0;
	
	try {
		id = stoi(cgicc("id"));
	
		BitQA::Question question(id);
		vector<BitQA::Comment> questionComments;
		
		// Get Comments for question
		vector<int> questionCommentsID = question.getContentID();
		vector<int>::iterator questionCommentsID_Iterator = questionCommentsID.begin();
		
		while (questionCommentsID_Iterator != questionCommentsID.end()) {
			questionComments.push_back(BitQA::Comment(*questionCommentsID_Iterator));
			questionCommentsID_Iterator++;
		}
		
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
			 * Question Comments
			 */
			
			cout << " <div class=\"container-fluid\">";
			
			vector<BitQA::Comment>::iterator questionComments_Iterator = questionComments.begin();
			
			while (questionComments_Iterator != questionComments.end()) {
				// cout << questionComments_Iterator->getContentID() << endl;
				
				
				cout << "<div class=\"row\">";
					cout << "<div class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"></div>";
					cout << "<div class=\"col-xs-1 col-sm-1 col-md-1 col-lg-1\">";
					cout << "<h5><a href=\"#\">&#128077;</a></h5>";
					cout << "<span><b>" << questionComments_Iterator->getVotes() << "</b></span>";
					cout << "</div>";
					cout << "<div class=\"col-xs-5 col-sm-5 col-md-5 col-lg-5\">";
					cout << "<p>" << questionComments_Iterator->getDetails() << "</p>";
					cout << "<p><b>Comment by " << questionComments_Iterator->getUsername() << "</b></p>";
					cout << "<hr>";
					cout << "</div>";
				cout << "</div>";
				
				questionComments_Iterator++;
			}
			
			cout << "</div>";
			cout << "<hr>";
			
			cout << BitQA::HTML::spacer(10);
			
			BitQA::HTML::displayFooter();
		}
		
	} catch (exception &e) {
		
		BitQA::HTML::displayHeader();
		
		BitQA::HTML::error("Invalid Question Being Viewed",
						   "Please go <a href=\"/\">home</a>"
						   );
		
		BitQA::HTML::displayFooter();
		
	}
	
	return 0;
}
