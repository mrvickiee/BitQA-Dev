#include "../process/question.hpp"
#include "../process/comment.hpp"
#include "../process/answer.hpp"
#include "../includes/html.hpp"
#include "../includes/database.hpp"
#include "../process/vote.hpp"
#include "../includes/profile.hpp"

#include <regex>

using namespace cgicc;
using namespace std;

string qowner;
string qid;

bool isDuplicate;

void getQuestionStack(int id, Cgicc cgicc, string userName)
{
	BitQA::Profile userprofile(userName);
	
	BitQA::Question question(id);
	isDuplicate = question.getIfDuplicate();
	vector<BitQA::Voter> voters = BitQA::Vote::getContentIDVoted(userName);
	BitQA::Voter currentVoter;
	
	{
		
		/*
		 * Question
		 */
		
		//if (isDuplicate) cout << "Is duplicate" << endl;
		
		qowner = question.getQuestionOwner();
		qid = question.getQuestionID();
		
		cout << "<h1>" << question.getTitle() << "</h1>";
		cout << " <div class=\"container-fluid\"><div class=\"row\">";
		cout << "<div class=\"col-xs-1 col-sm-1 col-md-1 col-lg-1\">";
		
		currentVoter.ContentId = stoi(question.getQuestionContentID());
		currentVoter.Type = 'U';
		
		if (BitQA::Vote::searchContentIDVoted(voters, currentVoter)) {
			
			cout << "<h3><span style=\"background-color: green;\" class=\"bitqa-fake-link vote-up\" data-user-id=\"" << question.getQuestionOwner()
					<< "\" data-selected=\"true"
					<< "\" id=\"up" << question.getQuestionContentID()
					<< "\" data-vote-type=\"up"
					<< "\" data-content-id=\"" << question.getQuestionContentID()
					<< "\" >&#128077;</span></h3>";
			
		} else {
			
			cout << "<h3><span class=\"bitqa-fake-link vote-up\" data-user-id=\"" << question.getQuestionOwner()
					<< "\" id=\"up" << question.getQuestionContentID()
					<< "\" data-vote-type=\"up"
					<< "\" data-content-id=\"" << question.getQuestionContentID()
					<< "\" >&#128077;</span></h3>";
			
		}
		
		cout << "<span><b><span id=\"" << question.getQuestionContentID() << "\">" << question.getVotes() << "</span></b></span>";
		
		
		currentVoter.ContentId = stoi(question.getQuestionContentID());
		currentVoter.Type = 'D';
		
		if (BitQA::Vote::searchContentIDVoted(voters, currentVoter)) {
			
			cout << "<h3><span style=\"background-color: red;\" class=\"bitqa-fake-link vote-down\" data-user-id=\"" << question.getQuestionOwner()
					<< "\" data-selected=\"true"
					<< "\" id=\"down" << question.getQuestionContentID()
					<< "\" data-vote-type=\"down"
					<< "\" data-content-id=\"" << question.getQuestionContentID()
					<< "\" >&#128078;</span></h3>";
			
		} else {
		
			cout << "<h3><span class=\"bitqa-fake-link vote-down\" data-user-id=\"" << question.getQuestionOwner()
					<< "\" id=\"down" << question.getQuestionContentID()
					<< "\" data-vote-type=\"down"
					<< "\" data-content-id=\"" << question.getQuestionContentID()
					<< "\" >&#128078;</span></h3>";
		}
		
		
		cout << "</div>";
		cout << "<div class=\"col-xs-8 col-sm-8 col-md-8 col-lg-8\">";
		cout << "<br><p>" << question.getDetails() << "</p>";
		cout << "<p><i><b>Questioned by " << question.getUsername() << "</i></b></p>";
		
		// Check for duplicate
		{
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
			
			res = stmt->executeQuery("SELECT duplicate from tblQuestion WHERE id = " + question.getQuestionID());
			
			res->next();
			
			bool duplicate = res->getBoolean("duplicate");
			
			if (duplicate) {
				cout << "<div class=\"alert alert-warning\"><strong>Duplicate Question!</strong> This question has been marked as duplicate.</div>";
			}
		}
		
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

		if ((qryOwner == userName) ||
			(userprofile.canDo("DELETEANYANS"))
		) {
			// cout << "<div class=\"row-fluid\"><div class=\"span12\"><div style=\"width:1200px;\">";
			
			cout << " <div style=\"margin-left: -15px;\" class=\"container-fluid\">";
			cout << "<div style=\"margin-left: -15px;\" class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\">";
			cout << "<form style=\"width: 200px\" action='' method='post'>" << endl;
			cout << "<input type=\"hidden\" name=\"type\" value=\"delquestion\">";
			cout << "<input type=\"hidden\" name=\"questionid\" value=\"" << qid <<"\">";
			cout << "<button type=\"submit\" class=\"btn btn-default\">&#10060;</button>" << endl;
			cout << "</form><br>" << endl;
			cout << "</div>";
			
			cout << "<div style=\"margin-left: -75px;\" class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\">";
			cout << "<a href=\"/editcontent.html?contentid=" << question.getQuestionContentID() << "&questionid=" << qid << "\" class=\"btn btn-default\">&#128064;</a>" << endl;
			cout << "<br>" << endl;
			cout << "</div>";
			// cout << "</div></div></div>";
			
		}
		
		//-------
		
		if (userprofile.canDo("MARKFEATUREDQUES")){
		
		//--Setfeatured question
		cout << "<form method='post'>" << endl;
		cout << "<input type=\"hidden\" name=\"type\" value=\"setfeatured\">";
		cout << "<input type=\"hidden\" name=\"questionid\" value=\"" << qid <<"\">";
		cout << "<div style=\"margin-left: -75px;\" class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"><input class='btn btn-default' type='submit' value=&#127775;></div>" << endl;
		
		cout << "</form>" << endl;
		
		}
		
		//----
		
		//-------
		
		if (userprofile.canDo("MARKDUPLICATE")){
			
			//--Setfeatured question
			cout << "<form method='post'>" << endl;
			cout << "<input type=\"hidden\" name=\"type\" value=\"markduplicate\">";
			cout << "<input type=\"hidden\" name=\"questionid\" value=\"" << qid <<"\">";
			cout << "<div style=\"margin-left: -75px;\" class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"><input class='btn btn-default' type='submit' value=&#128588;></div>" << endl;
			
			cout << "</form>" << endl;
			
		}
		
		//----
		
		/*
		 * Tags
		 */
		cout << "</div>";
		cout << "<div style=\"margin-left: -15px;\" class=\"container-fluid\">";
		cout << "<p><b>Tags: </b>";
		
		{
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
			
			res = stmt->executeQuery("SELECT tags FROM tblQuestion WHERE id = " + question.getQuestionID());
			
			string tags = "";
			
			while (res->next()) {
				tags = res->getString("tags");
			};
			
			string s(tags);
			regex e("<(.*?)>");
			
			regex_iterator<string::iterator> rit(s.begin(), s.end(), e);
			regex_iterator<string::iterator> rend;
			
			while (rit != rend) {
				
				string original = rit->str();
				size_t s = original.find("<");
				size_t e = original.find(">", s);
				string sub = original.substr(s + 1, e - s -1);
				
				cout << "<a href=\"\">" + sub + "</a>" << endl;
				++rit;
			}
			
		}
		
		cout << "</p>";
		cout << "</div>";
		
		cout << "</div>";
		cout << "</div>";
		
		/*
		 * Question Comments
		 */
		
		cout << " <div class=\"container-fluid\">";
		
		vector<BitQA::Comment> commentList = question.getComments();
		
		for (int i = 0; i < commentList.size(); i++) {
			cout << "<div class=\"row\">";
			cout << "<div class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"></div>";
			cout << "<div class=\"col-xs-1 col-sm-1 col-md-1 col-lg-1\">";
			
			currentVoter.ContentId = stoi(commentList[i].getContentID());
			currentVoter.Type = 'U';
			
			if (BitQA::Vote::searchContentIDVoted(voters, currentVoter)) {
				cout << "<h5><span style=\"background-color: green;\" class=\"bitqa-fake-link vote-up\" data-user-id=\"" << commentList[i].getOwnerID()
					<< "\" data-selected=\"true"
					<< "\" id=\"up" << commentList[i].getContentID()
					<< "\" data-vote-type=\"up"
					<< "\" data-content-id=\"" << commentList[i].getContentID()
					<< "\" href=\"\">&#128077;</span></h5>";
			} else {
				cout << "<h5><span class=\"bitqa-fake-link vote-up\" data-user-id=\"" << commentList[i].getOwnerID()
				<< "\" id=\"up" << commentList[i].getContentID()
				<< "\" data-vote-type=\"up"
				<< "\" data-content-id=\"" << commentList[i].getContentID()
				<< "\" href=\"\">&#128077;</span></h5>";
			}
			
			
			cout << "<span><b><span id=\"" << commentList[i].getContentID() << "\">" << commentList[i].getVotes() << "</span></b></span>";
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
				cout << "<div style=\"margin-left: -15px;\" class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"><form method='post'>" << endl;
				cout << "<input type=\"hidden\" name=\"type\" value=\"delcomment\">";
				cout << "<input type=\"hidden\" name=\"commentid\" value=\"" << commentList[i].getCommentID() <<"\">";
				cout << "<input class='btn btn-default btn-sm' type='submit' value=&#10060;>" << endl;
				
				cout << "</form></div>" << endl;
				
				cout << "<div style=\"margin-left: -30px;\" class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"><a href=\"/editcontent.html?contentid=" << commentList[i].getContentID() << "&questionid=" << qid << "\" class=\"btn btn-default btn-sm\">&#128064;</a></div>" << endl;
				
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
			<< "<textarea" << (isDuplicate ? " disabled" : "")  <<" name=\"data\" style=\"width:645px\" class=\"input-large form-control\" cols=\"20\" rows=\"2\" id=\"comment\"></textarea><br>";
		cout << "<input type=\"hidden\" name=\"content-id\" value=\"" << question.getQuestionContentID() << "\">";
		cout << "<input type=\"hidden\" name=\"type\" value=\"comment\">";
		cout << "<input class=\"btn btn-default\" type=\"submit\">"
		<< "</form></div>";
		
		cout << "<div class=\"row\" style=\"width: 300px\">";
		cout << "<a style=\"display:none\" href=\"\">Comment on this answer</a>";
		cout << "</div>";
		cout << "</div></div>";
		
		
		cout << "</div>";
		cout << "<hr>";
		
		cout << BitQA::HTML::spacer(10);
		
	}
}

void getAnswerStack(int id, Cgicc cgicc, string userName)
{

	BitQA::Profile userprofile(userName);
	
	vector<BitQA::Answer> answerList;
	vector<BitQA::Voter> voters = BitQA::Vote::getContentIDVoted(userName);
	BitQA::Voter currentVote;
	
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
		
		if (answerList[i].isAcceptedAnswer()) {
		
		cout << " <div class=\"container-fluid\">";
		cout << "<div class=\"row\">";
		cout << "<div class=\"col-xs-1 col-sm-1 col-md-1 col-lg-1\">";
		
		currentVote.ContentId = answerList[i].getContentID();
		currentVote.Type = 'U';
		
		if (BitQA::Vote::searchContentIDVoted(voters, currentVote)) {
			cout << "<h3><span style=\"background-color:green;\" class=\"bitqa-fake-link vote-up\" data-user-id=\"" << answerList[i].getUserID()
				<< "\" data-selected=\"true"
				<< "\" id=\"up" << answerList[i].getContentID()
				<< "\" data-vote-type=\"up"
				<< "\" data-content-id=\"" << answerList[i].getContentID()
				<< "\" >&#128077;</span></h3>";
		} else {
			cout << "<h3><span class=\"bitqa-fake-link vote-up\" data-user-id=\"" << answerList[i].getUserID()
				<< "\" id=\"up" << answerList[i].getContentID()
				<< "\" data-vote-type=\"up"
				<< "\" data-content-id=\"" << answerList[i].getContentID()
				<< "\" >&#128077;</span></h3>";
		}
		
		cout << "<span><b><span id=\"" << answerList[i].getContentID() << "\">" << answerList[i].getVotes() << "</span></b></span>";
		
		currentVote.ContentId = answerList[i].getContentID();
		currentVote.Type = 'D';
		
		if (BitQA::Vote::searchContentIDVoted(voters, currentVote)) {
			cout << "<h3><span style=\"background-color:red;\" class=\"bitqa-fake-link vote-down\" data-user-id=\"" << answerList[i].getUserID()
				<< "\" data-selected=\"true"
				<< "\" id=\"down" << answerList[i].getContentID()
				<< "\" data-vote-type=\"down"
				<< "\" data-content-id=\"" << answerList[i].getContentID()
				<< "\" >&#128078;</span></h3>";
		} else {
			cout << "<h3><span class=\"bitqa-fake-link vote-down\" data-user-id=\"" << answerList[i].getUserID()
				<< "\" id=\"down" << answerList[i].getContentID()
				<< "\" data-vote-type=\"down"
				<< "\" data-content-id=\"" << answerList[i].getContentID()
				<< "\" >&#128078;</span></h3>";
		}
		
		cout << "</div>";
		cout << "<div class=\"col-xs-8 col-sm-8 col-md-8 col-lg-8\">";
		if (answerList[i].isAcceptedAnswer()) cout << "<h5>&#128175; Accepted Answer</h5>" << endl;
		cout << "<br><p>" << answerList[i].getDetails() << "</p>";
		
		
		cout << "<p><i><b>Answered by " << answerList[i].getUsername() << "</i></b></p>";
		
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
		
		res = stmt->executeQuery("CALL ProcGetOwner('A', " + to_string(answerList[i].getAnswerID()) + ");");
		
		res->next();
		
		string qryOwner = res->getString("owner");
		
		if ((qryOwner == userName) ||
			(userprofile.canDo("DELETEANYANS"))
		) {
			cout << "<div style=\"margin-left: -15px;\" class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"><form method='post'>" << endl;
			cout << "<input type=\"hidden\" name=\"type\" value=\"delanswer\">";
			cout << "<input type=\"hidden\" name=\"answerid\" value=\"" << answerList[i].getAnswerID() <<"\">";
			cout << "<input class='btn btn-default btn-sm' type='submit' value=&#10060;>" << endl;
			
			cout << "</form></div>" << endl;
			
			cout << "<div style=\"margin-left: -75px;\" class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"><a href=\"/editcontent.html?contentid=" << answerList[i].getContentID() << "&questionid=" << qid << "\" class=\"btn btn-default btn-sm\">&#128064;</a></div>" << endl;
			
		}
		
		//-----
		
		//--Set accepted answer
		if ((qowner == userName) ||
			(userprofile.canDo("SETACCEPTEDANSOTHERUSER"))
		) {
			cout << "<div style=\"margin-left: -75px;\" class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"><form method='post'>" << endl;
			cout << "<input type=\"hidden\" name=\"type\" value=\"setanswer\">";
			cout << "<input type=\"hidden\" name=\"answerid\" value=\"" << answerList[i].getAnswerID() <<"\">";
			cout << "<input type=\"hidden\" name=\"quesid\" value=\"" << qid <<"\">";
			cout << "<input class='btn btn-default btn-sm' type='submit' value=&#128175;>" << endl;
			
			cout << "</form></div><br>" << endl;
		}
		
		//-------

		
		cout << "</div>";
		cout << "</div></div><br>";
		
		vector<BitQA::Comment> commentList = answerList[i].getComments();
		
		
		
		for (int j = 0; j < commentList.size(); j++) {
			
			cout << "<div class=\"row\">";
			cout << "<div class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"></div>";
			cout << "<div class=\"col-xs-1 col-sm-1 col-md-1 col-lg-1\">";
			
			currentVote.ContentId = stoi(commentList[j].getContentID());
			currentVote.Type = 'U';
			
			if (BitQA::Vote::searchContentIDVoted(voters, currentVote)) {
				cout << "<h5><span style=\"background-color:green;\" class=\"bitqa-fake-link vote-up\" data-user-id=\"" << commentList[i].getOwnerID()
					<< "\" data-selected=\"true"
					<< "\" id=\"up" << commentList[j].getContentID()
					<< "\" data-vote-type=\"up"
					<< "\" data-content-id=\"" << commentList[j].getContentID()
					<< "\" >&#128077;</span></h5>";
			} else {
				cout << "<h5><span class=\"bitqa-fake-link vote-up\" data-user-id=\"" << commentList[i].getOwnerID()
					<< "\" id=\"up" << commentList[j].getContentID()
					<< "\" data-vote-type=\"up"
					<< "\" data-content-id=\"" << commentList[j].getContentID()
					<< "\" >&#128077;</span></h5>";
			}
			
			cout << "<span><b><span id=\"" << commentList[j].getContentID() << "\">" << commentList[j].getVotes() << "</span></b></span>";
			
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
			
			res = stmt->executeQuery("CALL ProcGetOwner('C', " + commentList[j].getCommentIDStr() + ");");
			
			res->next();
			
			string qryOwner = res->getString("owner");
			
			//cout << "comid: " << commentList[j].getCommentID() << " usr:" << userName << endl;
			
			if ((qryOwner == userName)  ||
				(userprofile.canDo("DELETEANYANS"))
			) {
				cout << "<div style=\"margin-left: -15px;\" class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"><form method='post'>" << endl;
				cout << "<input type=\"hidden\" name=\"type\" value=\"delcomment\">";
				cout << "<input type=\"hidden\" name=\"commentid\" value=\"" << commentList[j].getCommentID() <<"\">";
				cout << "<input class='btn btn-default btn-sm' type='submit' value=&#10060;>" << endl;
				
				cout << "</form></div>" << endl;
				
				cout << "<div style=\"margin-left: -30px;\" class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"><a href=\"/editcontent.html?contentid=" << commentList[j].getContentID() << "&questionid=" << qid << "\" class=\"btn btn-default btn-sm\">&#128064;</a></div>" << endl;
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
			<< "<textarea" << (isDuplicate ? " disabled" : "")  <<" name=\"data\" style=\"width:645px\" class=\"input-large form-control\" cols=\"20\" rows=\"2\" id=\"comment\"></textarea><br>";
		cout << "<input type=\"hidden\" name=\"content-id\" value=\"" << answerList[i].getContentID() << "\">";
		cout << "<input type=\"hidden\" name=\"type\" value=\"comment\">";
		cout << "<input class=\"btn btn-default\" type=\"submit\">"
			<< "</form></div>";
		cout << "<div class=\"row\" style=\"width: 300px\">";
		cout << "<a style=\"display:none\" href=\"\">Comment on this answer</a>";
		cout << "</div>";
		cout << "</div></div>";
		cout << "<hr>";
		}
		
	}
	
	
	//not accepted answers
	
	for (int i = 0; i < answerList.size(); i++) {
		
		if (!answerList[i].isAcceptedAnswer()) {
			
			cout << " <div class=\"container-fluid\">";
			cout << "<div class=\"row\">";
			cout << "<div class=\"col-xs-1 col-sm-1 col-md-1 col-lg-1\">";
			
			currentVote.ContentId = answerList[i].getContentID();
			currentVote.Type = 'U';
			
			if (BitQA::Vote::searchContentIDVoted(voters, currentVote)) {
				cout << "<h3><span style=\"background-color:green;\" class=\"bitqa-fake-link vote-up\" data-user-id=\"" << answerList[i].getUserID()
				<< "\" data-selected=\"true"
				<< "\" id=\"up" << answerList[i].getContentID()
				<< "\" data-vote-type=\"up"
				<< "\" data-content-id=\"" << answerList[i].getContentID()
				<< "\" >&#128077;</span></h3>";
			} else {
				cout << "<h3><span class=\"bitqa-fake-link vote-up\" data-user-id=\"" << answerList[i].getUserID()
				<< "\" id=\"up" << answerList[i].getContentID()
				<< "\" data-vote-type=\"up"
				<< "\" data-content-id=\"" << answerList[i].getContentID()
				<< "\" >&#128077;</span></h3>";
			}
			
			cout << "<span><b><span id=\"" << answerList[i].getContentID() << "\">" << answerList[i].getVotes() << "</span></b></span>";
			
			currentVote.ContentId = answerList[i].getContentID();
			currentVote.Type = 'D';
			
			if (BitQA::Vote::searchContentIDVoted(voters, currentVote)) {
				cout << "<h3><span style=\"background-color:red;\" class=\"bitqa-fake-link vote-down\" data-user-id=\"" << answerList[i].getUserID()
				<< "\" data-selected=\"true"
				<< "\" id=\"down" << answerList[i].getContentID()
				<< "\" data-vote-type=\"down"
				<< "\" data-content-id=\"" << answerList[i].getContentID()
				<< "\" >&#128078;</span></h3>";
			} else {
				cout << "<h3><span class=\"bitqa-fake-link vote-down\" data-user-id=\"" << answerList[i].getUserID()
				<< "\" id=\"down" << answerList[i].getContentID()
				<< "\" data-vote-type=\"down"
				<< "\" data-content-id=\"" << answerList[i].getContentID()
				<< "\" >&#128078;</span></h3>";
			}
			
			cout << "</div>";
			cout << "<div class=\"col-xs-8 col-sm-8 col-md-8 col-lg-8\">";
			if (answerList[i].isAcceptedAnswer()) cout << "<h5>&#128175; Accepted Answer</h5>" << endl;
			cout << "<br><p>" << answerList[i].getDetails() << "</p>";
			
			
			cout << "<p><i><b>Answered by " << answerList[i].getUsername() << "</i></b></p>";
			
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
			
			res = stmt->executeQuery("CALL ProcGetOwner('A', " + to_string(answerList[i].getAnswerID()) + ");");
			
			res->next();
			
			string qryOwner = res->getString("owner");
			
			if ((qryOwner == userName)  ||
				(userprofile.canDo("DELETEANYANS"))
			) {
				cout << "<div style=\"margin-left: -15px;\" class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"><form method='post'>" << endl;
				cout << "<input type=\"hidden\" name=\"type\" value=\"delanswer\">";
				cout << "<input type=\"hidden\" name=\"answerid\" value=\"" << answerList[i].getAnswerID() <<"\">";
				cout << "<input class='btn btn-default btn-sm' type='submit' value=&#10060;>" << endl;
				
				cout << "</form></div>" << endl;
				
				cout << "<div style=\"margin-left: -75px;\" class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"><a href=\"/editcontent.html?contentid=" << answerList[i].getContentID() << "&questionid=" << qid << "\" class=\"btn btn-default btn-sm\">&#128064;</a></div>" << endl;
			}
			
			//-----
			
			//--Set accepted answer
			if ((qowner == userName) ||
				(userprofile.canDo("SETACCEPTEDANSOTHERUSER"))
			) {
				cout << "<div style=\"margin-left: -75px;\" class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"><form method='post'>" << endl;
				cout << "<input type=\"hidden\" name=\"type\" value=\"setanswer\">";
				cout << "<input type=\"hidden\" name=\"answerid\" value=\"" << answerList[i].getAnswerID() <<"\">";
				cout << "<input type=\"hidden\" name=\"quesid\" value=\"" << qid <<"\">";
				cout << "<input class='btn btn-default btn-sm' type='submit' value=&#128175;>" << endl;
				
				cout << "</form></div>" << endl;
			}
			
			//-------
			
			
			cout << "</div>";
			cout << "</div></div>";
			
			vector<BitQA::Comment> commentList = answerList[i].getComments();
			
			
			
			for (int j = 0; j < commentList.size(); j++) {
				
				cout << "<div class=\"row\">";
				cout << "<div class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"></div>";
				cout << "<div class=\"col-xs-1 col-sm-1 col-md-1 col-lg-1\">";
				
				currentVote.ContentId = stoi(commentList[j].getContentID());
				currentVote.Type = 'U';
				
				if (BitQA::Vote::searchContentIDVoted(voters, currentVote)) {
					cout << "<h5><span style=\"background-color:green;\" class=\"bitqa-fake-link vote-up\" data-user-id=\"" << commentList[i].getOwnerID()
					<< "\" data-selected=\"true"
					<< "\" id=\"up" << commentList[j].getContentID()
					<< "\" data-vote-type=\"up"
					<< "\" data-content-id=\"" << commentList[j].getContentID()
					<< "\" >&#128077;</span></h5>";
				} else {
					cout << "<h5><span class=\"bitqa-fake-link vote-up\" data-user-id=\"" << commentList[i].getOwnerID()
					<< "\" id=\"up" << commentList[j].getContentID()
					<< "\" data-vote-type=\"up"
					<< "\" data-content-id=\"" << commentList[j].getContentID()
					<< "\" >&#128077;</span></h5>";
				}
				
				cout << "<span><b><span id=\"" << commentList[j].getContentID() << "\">" << commentList[j].getVotes() << "</span></b></span>";
				
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
				
				res = stmt->executeQuery("CALL ProcGetOwner('C', " + commentList[j].getCommentIDStr() + ");");
				
				res->next();
				
				string qryOwner = res->getString("owner");
				
				//cout << "comid: " << commentList[j].getCommentID() << " usr:" << userName << endl;
				
				if ((qryOwner == userName) ||
					(userprofile.canDo("DELETEANYANS"))
				) {
					cout << "<div style=\"margin-left: -15px;\" class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"><form method='post'>" << endl;
					cout << "<input type=\"hidden\" name=\"type\" value=\"delcomment\">";
					cout << "<input type=\"hidden\" name=\"commentid\" value=\"" << commentList[j].getCommentID() <<"\">";
					cout << "<input class='btn btn-default btn-sm' type='submit' value=&#10060;>" << endl;
					
					cout << "</form></div>" << endl;
					
					cout << "<div style=\"margin-left: -30px;\" class=\"col-xs-2 col-sm-2 col-md-2 col-lg-2\"><a href=\"/editcontent.html?contentid=" << commentList[j].getContentID() << "&questionid=" << qid << "\" class=\"btn btn-default btn-sm\">&#128064;</a></div>" << endl;
					
					
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
			<< "<textarea" << (isDuplicate ? " disabled" : "")  <<" name=\"data\" style=\"width:645px\" class=\"input-large form-control\" cols=\"20\" rows=\"2\" id=\"comment\"></textarea><br>";
			cout << "<input type=\"hidden\" name=\"content-id\" value=\"" << answerList[i].getContentID() << "\">";
			cout << "<input type=\"hidden\" name=\"type\" value=\"comment\">";
			cout << "<input class=\"btn btn-default\" type=\"submit\">"
			<< "</form></div>";
			cout << "<div class=\"row\" style=\"width: 300px\">";
			cout << "<a style=\"display:none\" href=\"\">Comment on this answer</a>";
			cout << "</div>";
			cout << "</div></div>";
			cout << "<hr>";
		}
	}
	
	cout << "<div class=\"row\"><div class=\"col-xs-9 col-sm-9 col-md-9 col-lg-9\">";
	cout << "<form action=\"\" method=\"post\"><div class=\"form-group\">"
	<< "<label for=\"answer\">Add new answer:</label>"
	<< "<textarea" << (isDuplicate ? " disabled" : "")  <<" name=\"data\" style=\"width:100%\" class=\"input-large form-control\" cols=\"20\" rows=\"5\" id=\"answer\"></textarea><br>";
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
				
			} else if (postType == "setfeatured"){
				
				string quid = cgicc("questionid");
				
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
				
				res = stmt->executeQuery("CALL ProcSetFeatured(" + quid + ");");
				
				res->next();
				string qryResult = res->getString("result");
				if (qryResult == "OK") {
					
					cout << "<div class=\"alert alert-success alert-dismissible\" role=\"alert\">";
					cout << "<button type=\"button\" class=\"close\" data-dismiss=\"alert\" aria-label=\"Close\">";
					cout << "<span aria-hidden=\"true\">&times;</span></button>";
					cout << "<strong>Featured question set</strong> successfully</div>";
				} else {
					cout << "<div class=\"alert alert-danger alert-dismissible\" role=\"alert\">";
					cout << "<button type=\"button\" class=\"close\" data-dismiss=\"alert\" aria-label=\"Close\">";
					cout << "<span aria-hidden=\"true\">&times;</span></button>";
					cout << "<strong>Featured question set</strong> failed</div>";
				}

				
			
			} else if (postType == "markduplicate"){
				
				string quid = cgicc("questionid");
				
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
				
				res = stmt->executeQuery("CALL ProcSetMarkedDuplicate(" + quid + ");");
				
				res->next();
				string qryResult = res->getString("result");
				if (qryResult == "OK") {
					
					cout << "<div class=\"alert alert-success alert-dismissible\" role=\"alert\">";
					cout << "<button type=\"button\" class=\"close\" data-dismiss=\"alert\" aria-label=\"Close\">";
					cout << "<span aria-hidden=\"true\">&times;</span></button>";
					cout << "<strong>Marked Duplicate question set</strong> successfully</div>";
				} else {
					cout << "<div class=\"alert alert-danger alert-dismissible\" role=\"alert\">";
					cout << "<button type=\"button\" class=\"close\" data-dismiss=\"alert\" aria-label=\"Close\">";
					cout << "<span aria-hidden=\"true\">&times;</span></button>";
					cout << "<strong>Featured question set</strong> failed</div>";
				}
				
				
				
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
				
								cout << "<H1>USER: " << userName << "</H1>";
				
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
				
			} else if (postType == "setanswer"){
				string answerid = cgicc("answerid");
				string quid = cgicc("quesid");
				
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
				
				res = stmt->executeQuery("CALL ProcSetAcceptedAnswer(" + quid + "," + answerid + ",'" + userName + "');");
				
				res->next();
				string qryResult = res->getString("result");
				if (qryResult == "OK") {
					
					cout << "<div class=\"alert alert-success alert-dismissible\" role=\"alert\">";
					cout << "<button type=\"button\" class=\"close\" data-dismiss=\"alert\" aria-label=\"Close\">";
					cout << "<span aria-hidden=\"true\">&times;</span></button>";
					cout << "<strong>Accepted answer set</strong> successfully</div>";
				} else {
					cout << "<div class=\"alert alert-danger alert-dismissible\" role=\"alert\">";
					cout << "<button type=\"button\" class=\"close\" data-dismiss=\"alert\" aria-label=\"Close\">";
					cout << "<span aria-hidden=\"true\">&times;</span></button>";
					cout << "<strong>Accepted answer set</strong>failed</div>";
				}
				
			
			} else if(postType == "delanswer"){
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
				
				string deleteId = cgicc("answerid");
				
				//cout << "del:" << deleteId << endl;
				
				res = stmt->executeQuery("CALL ProcDeleteContent('A', " + deleteId + ", '" + userName + "');");
				
				res->next();
				string qryResult = res->getString("result");
				if (qryResult == "OK") {
					
					cout << "<div class=\"alert alert-success alert-dismissible\" role=\"alert\">";
					cout << "<button type=\"button\" class=\"close\" data-dismiss=\"alert\" aria-label=\"Close\">";
					cout << "<span aria-hidden=\"true\">&times;</span></button>";
					cout << "<strong>Answer Deleted successfully</strong></div>";
				} else {
					cout << "<div class=\"alert alert-danger alert-dismissible\" role=\"alert\">";
					cout << "<button type=\"button\" class=\"close\" data-dismiss=\"alert\" aria-label=\"Close\">";
					cout << "<span aria-hidden=\"true\">&times;</span></button>";
					cout << "<strong>Answer Not Deleted</strong> successfully</div>";
				}
			
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
		
		BitQA::HTML::displayHeader("Question", cgicc);
		
		int id = stoi(cgicc("id"));
		//int id = 16511;
		
		processPOST(id, cgicc, needsExit);
		
		if (!needsExit) {
			getQuestionStack(id, cgicc, userName);
			
			getAnswerStack(id, cgicc, userName);
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
	
	cout << "<script type=\"text/javascript\" src=\"/includes/javascript/questions.js\"></script>";
	
	BitQA::HTML::displayFooter();
	
	return 0;
}
