#include "../process/question.hpp"
#include "../process/comment.hpp"
#include "../process/answer.hpp"
#include "../includes/html.hpp"
#include "../includes/database.hpp"

using namespace cgicc;
using namespace std;

void getQuestionStack(int id)
{
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
}

void getAnswerStack(int id)
{
	vector<BitQA::Answer> answerList;
	
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	
	
	driver = get_driver_instance();
	con = driver->connect(BitQA::Database::HOST,
						  BitQA::Database::USERNAME,
						  BitQA::Database::PASSWORD
						  );
	
	con->setSchema(BitQA::Database::SCHEMA);
	
	stmt = con->createStatement();
	
	res = stmt->executeQuery("SELECT id FROM tblAnswer WHERE questionId = '" + to_string(id) + "'");
	
	
	while (res->next()) {
		//construct comment
		BitQA::Answer insAnswer(res->getInt("id"));
		
		answerList.push_back(insAnswer);
	}
	
	cout << "<div><h4> There are " << answerList.size() << " Answers to this Question:</h4></div><hr>";
	
	for (int i = 0; i < answerList.size(); i++) {
		
		cout << " <div class=\"container-fluid\">";
		cout << "<div class=\"row\">";
		cout << "<div class=\"col-xs-1 col-sm-1 col-md-1 col-lg-1\">";
		cout << "<h3><a href=\"#\">&#128077;</a></h3>";
		cout << "<span><b>" << answerList[i].getVotes() << "</b></span>";
		cout << "<h3><a href=\"#\">&#128078;</a></h3>";
		cout << "</div>";
		cout << "<div class=\"col-xs-8 col-sm-8 col-md-8 col-lg-8\">";
		cout << "<br><p>" << answerList[i].getDetails() << "</p>";
		cout << "<p><i><b>Answered by " << answerList[i].getUsername() << "</i></b></p>";
		cout << "</div>";
		cout << "</div></div>";
		
		vector<BitQA::Comment> commentList = answerList[i].getComments();
		
		for (int j = 0; j < commentList.size(); j++) {
			
			cout << "<div class=\"row\">";
			cout << "<div class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"></div>";
			cout << "<div class=\"col-xs-1 col-sm-1 col-md-1 col-lg-1\">";
			cout << "<h5><a href=\"#\">&#128077;</a></h5>";
			cout << "<span><b>" << commentList[j].getVotes() << "</b></span>";
			cout << "</div>";
			cout << "<div class=\"col-xs-5 col-sm-5 col-md-5 col-lg-5\">";
			cout << "<p>" << commentList[j].getDetails() << "</p>";
			cout << "<p><b>Comment by " << commentList[j].getUsername() << "</b></p>";
			cout << "<hr>";
			cout << "</div>";
			cout << "</div>";
		}
		
		cout << "<div class=\"row\">";
		cout << "<div class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"></div>";
		cout << "<div class=\"col-xs-1 col-sm-1 col-md-1 col-lg-1\">";
		cout << "<form style=\"display:none\" action=\"\" method=\"post\"><div class=\"form-group\">"
			<< "<label for=\"comment\">Comment:</label>"
			<< "<textarea name=\"comment\" style=\"width:645px\" class=\"input-large form-control\" cols=\"20\" rows=\"2\" id=\"comment\"></textarea><br>";
		cout << "<input type=\"hidden\" name=\"comment-id\" value=\"data\">";
		
		cout << "<input class=\"btn btn-default\" type=\"submit\">"
			<< "</form></div>";
		cout << "<div class=\"row\" style=\"width: 300px\">";
		cout << "<a href=\"javascript:void();\">Comment on this answer</a>";
		cout << "</div>";
		cout << "</div></div>";
		cout << "<hr>";
		
	}
	
	delete res;
	delete stmt;
	delete con;
}

int main()
{
	
	BitQA::HTML::displayHeader();
	
	try {
		Cgicc cgicc;
		int id = stoi(cgicc("id"));
		//int id = 16511;
		
		getQuestionStack(id);
		
		getAnswerStack(id);
		
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
	
	//cout << "<script src=\"/includes/javascript/events.js\"></script>" << endl;
	
	BitQA::HTML::displayFooter();
	
	return 0;
}
