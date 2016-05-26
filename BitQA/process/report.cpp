/*
Matthew Twose, mt156, 4510550
BitQA
report functionality declaration
*/
#include "report.hpp"

Report::Report()
{
	this->userid = "";
}

void Report::setUserId(string userId){
	this->userid = userId;
}

bool Report::loggedIn()
{
	if (this->userid.length() > 0) {
		return true;
	} else {
		return false;
	}
}

//Homepage reports

void Report::recQuestions()
{
	/*
	This becomes searchTerm
	(SELECT tags
	FROM tblUserTags
	WHERE id = 'this->userid';)

	SELECT Q.questionTitle, C.utimestamp
	FROM tblQuestion Q JOIN tblContent C
	WHERE Q.tags LIKE 'searchTerm'
	ORDER BY C.utimestamp DESC LIMIT 10;
	*/

	try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::ResultSet *res;
		sql::ResultSet *subRes;
		
		driver = get_driver_instance();
		con = driver->connect(BitQA::Database::HOST,
							  BitQA::Database::USERNAME,
							  BitQA::Database::PASSWORD
							  );
		
		con->setSchema(BitQA::Database::SCHEMA);
		stmt = con->createStatement();
		
		string searchTerm = "";

		if (this->loggedIn()) {
			subRes = stmt->executeQuery("SELECT tags FROM tblUserTags WHERE id = '" + this->userid + "'");
			
			while(subRes->next()){
				searchTerm = subRes->getString("tags");
			}
			
		}

		res = stmt->executeQuery("SELECT tblQuestion.id, tblQuestion.questionTitle, tblContent.utimestamp FROM tblQuestion JOIN tblContent ON tblQuestion.contentId = tblContent.id WHERE tblQuestion.tags LIKE '%" + searchTerm + "%' ORDER BY tblContent.utimestamp DESC LIMIT 10");

		cout << "<table class=\"table table-hover\">";
		cout << "<tr>";
		cout << "<th>Question Title</th>";
		cout << "<th>Date posted</th>";
		cout << "</tr>";
		while(res->next()){
			cout << "<tr>";
			cout << "<td><a href=\"/question.html?id=" << res->getString("id") << "\">" << res->getString("questionTitle") << "</a></td>";
			cout << "<td>" << res->getString("utimestamp") << "</td>";
			cout << "</tr>";
		}
		cout << "</table>";

		delete res;
		delete stmt;
		delete con;

	} catch (sql::SQLException &e) {
		cout << "<p>Error</p>";
	}
}

void Report::topUsers(){
	/*
	SELECT U.username, R.reputation, U.creationdate
	FROM tblUser U JOIN tblUserReputation R
	WHERE U.id = R.id
	ORDER BY R.reputation DESC LIMIT 10;
	*/

	try {
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
		
		
		res = stmt->executeQuery("SELECT tblUser.username, tblUser.displayname, tblUserReputation.reputation, tblUser.creationdate FROM tblUser JOIN tblUserReputation ON tblUser.username = tblUserReputation.username ORDER BY tblUserReputation.reputation DESC LIMIT 10;");

		cout << "<table class=\"table table-hover\">";
		cout << "<tr>";
		cout << "<th>Username</th>";
		cout << "<th>Reputation</th>";
		cout << "<th>Creation Date</th>";
		cout << "</tr>";
		while(res->next()){
			cout << "<tr>";
			cout << "<td><a href=\"/profile.html?username=" << res->getString("username") << "\">" << res->getString("displayname") << "</td>";
			cout << "<td>" << res->getString("reputation") << "</td>";
			cout << "<td>" << res->getString("creationdate") << "</td>";
			cout << "</tr>";
		}
		cout << "</table>";

		delete res;
		delete stmt;
		delete con;

	} catch (sql::SQLException &e) {
		cout << "<p>Error</p>";
	}
}

void Report::featured(){
	/*
	SELECT F.questionTitle, U.username
	FROM tblFeatured F JOIN tblUser U
	WHERE F.qOwner = U.id
	ORDER BY dateFeatured DESC LIMIT 10;
	*/

	try {
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
		
		
		res = stmt->executeQuery("SELECT tblFeatured.questionTitle, tblUser.username FROM tblFeatured JOIN tblUser ON tblFeatured.qOwner = tblUser.id ORDER BY tblFeatured.dateFeatured DESC LIMIT 10;");

		cout << "<table class=\"table table-hover\">";
		cout << "<tr>";
		cout << "<th>Question Title</th>";
		cout << "<th>Username</th>";
		cout << "</tr>";
		while(res->next()){
			cout << "<tr>";
			cout << "<td>" << res->getString("questionTitle") << "</td>";
			cout << "<td>" << res->getString("username") << "</td>";
			cout << "</tr>";
		}
		cout << "</table>";

		delete res;
		delete stmt;
		delete con;

	} catch (sql::SQLException &e) {
		cout << "<p>Error</p>";
	}
}

void Report::topQuestions(){
	/*
	SELECT Q.questionTitle, C.upvotes
	FROM tblQuestion Q JOIN tblContent C
	WHERE Q.contentId = C.id
	ORDER BY C.upvotes DESC LIMIT 10;
	*/

	try {
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

		
		res = stmt->executeQuery("SELECT Q.id, Q.questionTitle, C.upvotes FROM tblQuestion Q JOIN tblContent C ON Q.contentId = C.id ORDER BY C.upvotes DESC LIMIT 10;");

		cout << "<table class=\"table table-hover\">";
		cout << "<tr>";
		cout << "<th>Question Title</th>";
		cout << "<th>Upvotes</th>";
		cout << "</tr>";
		while(res->next()){
			cout << "<tr>";
			cout << "<td><a href=\"/question.html?id=" << res->getString("id") << "\">" << res->getString("questionTitle") << "</a></td>";
			cout << "<td>" << res->getString("upvotes") << "</td>";
			cout << "</tr>";
		}
		cout << "</table>";

		delete res;
		delete stmt;
		delete con;

	} catch (sql::SQLException &e) {
		cout << "<p>Error</p>";
	}

}

//User profile reports
void Report::activityGraph()
{
	cout << "<p>activityGraph</p>";
}

void Report::topTags(){
	/*
	SELECT Q.tags, count(*) AS frequency
	FROM tblQuestion Q JOIN tblContent C
	WHERE Q.aowner = 'this->userid'
	GROUP BY Q.tags
	ORDER BY count(*) DESC LIMIT 5
	*/

	try {
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
		
		
		res = stmt->executeQuery("SELECT tags, count(*) AS frequency FROM tblQuestion WHERE qowner = '" + this->userid + "' GROUP BY tags ORDER BY count(*) DESC LIMIT 5;");

		cout << "<table class=\"table table-hover\">";
		cout << "<tr>";
		cout << "<th>Tags</th>";
		cout << "<th>Frequency</th>";
		cout << "</tr>";
		
		int i = 0;
		
		while(res->next()){
			cout << "<tr>";
			cout << "<td>" << res->getString("tags") << "</td>";
			cout << "<td>" << res->getString("frequency") << "</td>";
			cout << "</tr>";
			i++;
		}
		
		if (i <= 0) {
			cout << "<tr>";
			cout << "<td>N/A</td>";
			cout << "<td>N/A</td>";
			cout << "</tr>";
		}
		
		cout << "</table>";

		delete res;
		delete stmt;
		delete con;

	} catch (sql::SQLException &e) {
		cout << "<p>Error</p>";
	}

}

void Report::topPostedQuestions()
{
	cout << "<p>topPostedQuestions</p>";
}

void Report::topPostedAnswers()
{
	cout << "<p>topPostedAnswers</p>";
}

void Report::postHistory(){
	/*
	"SELECT Con.id, Con.utimestamp
	FROM tblContent Con, tblAnswer A, tblQuestion Q, tblComment C
	WHERE (A.aowner = '" + this->userid + "') OR (Q.qowner = '" + this->userid + "') OR (C.aowner = '" + this->userid + "')
	ORDER BY utimestamp DESC LIMIT 10"
	*/

	try {
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
		
		res = stmt->executeQuery("SELECT tblQuestion.id, tblQuestion.questionTitle, tblContent.utimestamp FROM BitQA.tblQuestion JOIN tblContent ON tblQuestion.contentId = tblContent.id WHERE tblQuestion.qowner = '" + this->userid + "' ORDER BY tblContent.utimestamp DESC LIMIT 10;");

		cout << "<table class=\"table table-hover\">";
		cout << "<tr>";
		cout << "<th>Question</th>";
		cout << "<th>Timestamp</th>";
		cout << "</tr>";
		
		int i = 0;
		
		while(res->next()){
			cout << "<tr>";
			cout << "<td><a href=\"/question.html?id=" << res->getString("id") << "\">" << res->getString("questionTitle") << "</a></td>";
			cout << "<td>" << res->getString("utimestamp") << "</td>";
			cout << "</tr>";
			i++;
		}
		
		if (i <= 0) {
			cout << "<tr>";
			cout << "<td>None Posted</td>";
			cout << "<td>None Posted</td>";
			cout << "</tr>";
		}
		
		cout << "</table>";

		delete res;
		delete stmt;
		delete con;

	} catch (sql::SQLException &e) {
		cout << "<p>Error</p>";
	}

}
