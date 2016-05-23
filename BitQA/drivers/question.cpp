#include "../process/question.hpp"
#include "../process/comment.hpp"
#include "../process/answer.hpp"
#include "../includes/html.hpp"
#include "../includes/database.hpp"

using namespace cgicc;
using namespace std;

void getQuestionStack(int id, Cgicc cgicc)
{
	//check ownership and display
	CgiEnvironment environment = cgicc.getEnvironment();
	const_cookie_iterator cci;
	
	string userName = "";
	string displayName = "";
	
	for (cci = environment.getCookieList().begin();
		 cci != environment.getCookieList().end();
		 cci++) {
		if (cci->getName() == "username") {
			userName = cci->getValue();
		} else if (cci->getName() == "displayname") {
			displayName = cci->getValue();
		}
	}
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
		
		
		//pass username with question id
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
		
		res = stmt->executeQuery("CALL ProcGetOwner('Q', " + question.getQuestionID() + ");");
		
		res->next();
		
		string qryOwner = res->getString("owner");

		if (qryOwner == userName) {
			cout << "<form action='' method='post'>" << endl;
			cout << "<input type=\"hidden\" name=\"type\" value=\"delquestion\">";
			cout << "<input type=\"hidden\" name=\"questionid\" value=\"" << question.getQuestionID() <<"\">";
			cout << "<button type=\"submit\" class=\"btn btn-danger\">Delete</button>" << endl;
			cout << "</form><br>" << endl;
		}
		
		//-------
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
			
			//cout << commentList[i].getCommentIDStr() << endl;
			
			//-----Delete comment
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
			
			res = stmt->executeQuery("CALL ProcGetOwner('C', " + commentList[i].getCommentIDStr() + ");");
			
			res->next();
			
			string qryOwner = res->getString("owner");
			
			if (qryOwner == userName) {
				cout << "<form method='post'>" << endl;
				cout << "<input type=\"hidden\" name=\"type\" value=\"delcomment\">";
				cout << "<input type=\"hidden\" name=\"commentid\" value=\"" << commentList[i].getCommentID() <<"\">";
				cout << "<input class='btn btn-default btn-sm' type='submit' value=&#10060;>" << endl;
				
				cout << "</form>" << endl;
			}
			
			//-----
			cout << "<hr>";
			cout << "</div>";
			cout << "</div>";
		}
		
		cout << "<div class=\"row\">";
		cout << "<div class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"></div>";
		cout << "<div class=\"col-xs-1 col-sm-1 col-md-1 col-lg-1\">";
		cout << "<form action=\"\" method=\"post\"><div class=\"form-group\">"
		<< "<label for=\"comment\">Comment:</label>"
		<< "<textarea name=\"data\" style=\"width:645px\" class=\"input-large form-control\" cols=\"20\" rows=\"2\" id=\"comment\"></textarea><br>";
		cout << "<input type=\"hidden\" name=\"content-id\" value=\"" << question.getQuestionContentID() << "\">";
		cout << "<input type=\"hidden\" name=\"type\" value=\"comment\">";
		cout << "<input class=\"btn btn-default\" type=\"submit\">"
		<< "</form></div>";
		
		cout << "<div class=\"row\" style=\"width: 300px\">";
		cout << "<a style=\"display:none\" href=\"javascript:void();\">Comment on this answer</a>";
		cout << "</div>";
		cout << "</div></div>";
		
		
		cout << "</div>";
		cout << "<hr>";
		
		cout << BitQA::HTML::spacer(10);
		
	}
}

void getAnswerStack(int id, Cgicc cgicc)
{
	//check ownership and display
	CgiEnvironment environment = cgicc.getEnvironment();
	const_cookie_iterator cci;
	
	string userName = "";
	string displayName = "";
	
	for (cci = environment.getCookieList().begin();
		 cci != environment.getCookieList().end();
		 cci++) {
		if (cci->getName() == "username") {
			userName = cci->getValue();
		} else if (cci->getName() == "displayname") {
			displayName = cci->getValue();
		}
	}

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
	
	res = stmt->executeQuery("SELECT id FROM tblAnswer WHERE questionId = '" + to_string(id) + "' AND deleted=0");
	
	
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
			
			//-----Delete comment
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
			
			res = stmt->executeQuery("CALL ProcGetOwner('C', " + commentList[i].getCommentIDStr() + ");");
			
			res->next();
			
			string qryOwner = res->getString("owner");
			
			if (qryOwner == userName) {
				cout << "<form method='post'>" << endl;
				cout << "<input type=\"hidden\" name=\"type\" value=\"delcomment\">";
				cout << "<input type=\"hidden\" name=\"commentid\" value=\"" << commentList[i].getCommentID() <<"\">";
				cout << "<input class='btn btn-default btn-sm' type='submit' value=&#10060;>" << endl;
				
				cout << "</form>" << endl;
			}
			
			//-----
			
			cout << "<hr>";
			cout << "</div>";
			cout << "</div>";
		}
		
		cout << "<div class=\"row\">";
		cout << "<div class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"></div>";
		cout << "<div class=\"col-xs-1 col-sm-1 col-md-1 col-lg-1\">";
		cout << "<form action=\"\" method=\"post\"><div class=\"form-group\">"
			<< "<label for=\"comment\">Comment:</label>"
			<< "<textarea name=\"data\" style=\"width:645px\" class=\"input-large form-control\" cols=\"20\" rows=\"2\" id=\"comment\"></textarea><br>";
		cout << "<input type=\"hidden\" name=\"content-id\" value=\"" << answerList[i].getContentID() << "\">";
		cout << "<input type=\"hidden\" name=\"type\" value=\"comment\">";
		cout << "<input class=\"btn btn-default\" type=\"submit\">"
			<< "</form></div>";
		cout << "<div class=\"row\" style=\"width: 300px\">";
		cout << "<a style=\"display:none\" href=\"javascript:void();\">Comment on this answer</a>";
		cout << "</div>";
		cout << "</div></div>";
		cout << "<hr>";
		
	}
	
	cout << "<div class=\"row\"><div class=\"col-xs-9 col-sm-9 col-md-9 col-lg-9\">";
	cout << "<form action=\"\" method=\"post\"><div class=\"form-group\">"
	<< "<label for=\"answer\">Add new answer:</label>"
	<< "<textarea name=\"data\" style=\"width:100%\" class=\"input-large form-control\" cols=\"20\" rows=\"5\" id=\"answer\"></textarea><br>";
	cout << "<input type=\"hidden\" name=\"question-id\" value=\"" << to_string(id) << "\">";
	cout << "<input type=\"hidden\" name=\"type\" value=\"questionAnswer\">";
	cout << "<input class=\"btn btn-default\" type=\"submit\">"
	<< "</form></div></div>";
	
	delete res;
	delete stmt;
	delete con;
}

void processPOST(int id, Cgicc cgicc, bool &exit)
{
	BitQA::Answer answer(id);
	
	CgiEnvironment environment = cgicc.getEnvironment();
	const_cookie_iterator cci;
	
	string userName = "";
	string displayName = "";
	
	for (cci = environment.getCookieList().begin();
		cci != environment.getCookieList().end();
		cci++) {
		if (cci->getName() == "username") {
			userName = cci->getValue();
		} else if (cci->getName() == "displayname") {
			displayName = cci->getValue();
		}
	}
	
	if (environment.getRequestMethod() == "POST") {
		
		if (!userName.empty()) {
			
			string postType = cgicc("type");
			
			if (postType == "questionAnswer") {
				
				sql::Driver *driver;
				sql::Connection *con;
				sql::PreparedStatement *prep_stmt;
				
				driver = get_driver_instance();
				con = driver->connect(BitQA::Database::HOST,
									  BitQA::Database::USERNAME,
									  BitQA::Database::PASSWORD
									  );
				
				con->setSchema(BitQA::Database::SCHEMA);
				
				prep_stmt = con->prepareStatement("CALL ProcInsertAnswer(?, ?, ?);");
				prep_stmt->setInt(1, id);
				prep_stmt->setString(2, cgicc("data"));
				prep_stmt->setString(3, userName);
				prep_stmt->execute();
				
				delete prep_stmt;
				delete con;
				
				cout << "<div class=\"alert alert-success alert-dismissible\" role=\"alert\">";
				cout << "<button type=\"button\" class=\"close\" data-dismiss=\"alert\" aria-label=\"Close\">";
				cout << "<span aria-hidden=\"true\">&times;</span></button>";
				cout << "<strong>Success!</strong> Posted Answer Successfully!</div>";
				
			} else if (postType == "comment") {
				
				sql::Driver *driver;
				sql::Connection *con;
				sql::PreparedStatement *prep_stmt;
				
				driver = get_driver_instance();
				con = driver->connect(BitQA::Database::HOST,
									  BitQA::Database::USERNAME,
									  BitQA::Database::PASSWORD
									  );
				
				con->setSchema(BitQA::Database::SCHEMA);
				
				prep_stmt = con->prepareStatement("CALL ProcInsertComment(?, ?, ?);");
				prep_stmt->setInt(1, stoi(cgicc("content-id")));
				prep_stmt->setString(2, cgicc("data"));
				prep_stmt->setString(3, userName);
				prep_stmt->execute();
				
				delete prep_stmt;
				delete con;
				
				cout << "<div class=\"alert alert-success alert-dismissible\" role=\"alert\">";
				cout << "<button type=\"button\" class=\"close\" data-dismiss=\"alert\" aria-label=\"Close\">";
				cout << "<span aria-hidden=\"true\">&times;</span></button>";
				cout << "<strong>Success!</strong> Posted Comment Successfully!</div>";
				
			} else if (postType == "delquestion"){
				
				CgiEnvironment environment = cgicc.getEnvironment();
				const_cookie_iterator cci;
				
				string userName = "";
				string displayName = "";
				
				for (cci = environment.getCookieList().begin();
					 cci != environment.getCookieList().end();
					 cci++) {
					if (cci->getName() == "username") {
						userName = cci->getValue();
					} else if (cci->getName() == "displayname") {
						displayName = cci->getValue();
					}
				}
				
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
				
				string deleteId = cgicc("questionid");
				
				res = stmt->executeQuery("CALL ProcDeleteContent('Q', " + deleteId + ", '" + userName + "');");
				
				res->next();
				string qryResult = res->getString("result");
				if (qryResult == "OK") {
					
					cout << "<div class=\"alert alert-success alert-dismissible\" role=\"alert\">";
					cout << "<button type=\"button\" class=\"close\" data-dismiss=\"alert\" aria-label=\"Close\">";
					cout << "<span aria-hidden=\"true\">&times;</span></button>";
					cout << "<strong>Question Deleted successfully</strong>, browse more <a href='allquestions.html'>here</a></div>";
					exit = true;
				} else {
					cout << "<div class=\"alert alert-danger alert-dismissible\" role=\"alert\">";
					cout << "<button type=\"button\" class=\"close\" data-dismiss=\"alert\" aria-label=\"Close\">";
					cout << "<span aria-hidden=\"true\">&times;</span></button>";
					cout << "<strong>Question Not Deleted</strong> successfully</div>";
				}
			} else if (postType == "delcomment"){
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
				
				string deleteId = cgicc("commentid");
				
				res = stmt->executeQuery("CALL ProcDeleteContent('C', " + deleteId + ", '" + userName + "');");
				
				res->next();
				string qryResult = res->getString("result");
				if (qryResult == "OK") {
					
					cout << "<div class=\"alert alert-success alert-dismissible\" role=\"alert\">";
					cout << "<button type=\"button\" class=\"close\" data-dismiss=\"alert\" aria-label=\"Close\">";
					cout << "<span aria-hidden=\"true\">&times;</span></button>";
					cout << "<strong>Comment Deleted successfully</strong></div>";
				} else {
					cout << "<div class=\"alert alert-danger alert-dismissible\" role=\"alert\">";
					cout << "<button type=\"button\" class=\"close\" data-dismiss=\"alert\" aria-label=\"Close\">";
					cout << "<span aria-hidden=\"true\">&times;</span></button>";
					cout << "<strong>Comment Not Deleted</strong> successfully</div>";
				}
			
			} else {
				cout << "<div class=\"alert alert-danger alert-dismissible\" role=\"alert\">";
				cout << "<button type=\"button\" class=\"close\" data-dismiss=\"alert\" aria-label=\"Close\">";
				cout << "<span aria-hidden=\"true\">&times;</span></button>";
				cout << "<strong>Error!</strong> Invalid POST.</div>";
			}
			
		} else {
			cout << "<div class=\"alert alert-danger alert-dismissible\" role=\"alert\">";
			cout << "<button type=\"button\" class=\"close\" data-dismiss=\"alert\" aria-label=\"Close\">";
			cout << "<span aria-hidden=\"true\">&times;</span></button>";
			cout << "<strong>Error!</strong> Not logged in, could not post Answer.</div>";
		}
		
	}
}

int main()
{
	
	try {
		
		bool needsExit = false;
		
		Cgicc cgicc;
		
		BitQA::HTML::displayHeader("Question", cgicc);
		
		int id = stoi(cgicc("id"));
		//int id = 16511;
		
		processPOST(id, cgicc, needsExit);
		
		if (!needsExit) {
			getQuestionStack(id, cgicc);
			
			getAnswerStack(id, cgicc);
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
