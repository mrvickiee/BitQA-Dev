/*
Matthew Twose, mt156, 4510550
BitQA
report functionality declaration
*/
#include "report.hpp"

Report::Report(){
	this->userid = "";
}

Report::Report(string userId){
	this->userid = userId;
}

void Report::setUserId(string userId){
	this->userid = userId;
}


//Homepage reports

void Report::recQuestions(){
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
		string searchTerm;
		
		driver = get_driver_instance();
		con = driver->connect(BitQA::Database::HOST,
							  BitQA::Database::USERNAME,
							  BitQA::Database::PASSWORD
							  );
		
		con->setSchema(BitQA::Database::SCHEMA);
		
		stmt = con->createStatement();

		subRes = stmt->executeQuery("SELECT tags FROM tblUserTags WHERE id = '" + this->userid + "'");

		while(subRes->next()){
			searchTerm = subRes->getString("tags");
		}

		res = stmt->executeQuery("SELECT Q.questionTitle, C.utimestamp FROM tblQuestion Q JOIN tblContent C	WHERE Q.tags LIKE '" + searchTerm + "' ORDER BY C.utimestamp DESC LIMIT 10");

		cout << "<style>table, th, td{border: 2px solid black;}</style>";
		cout << "<table>";
		cout << "<tr>";
		cout << "<th>Question Title</th>";
		cout << "<th>Date posted</th>";
		cout << "</tr>";
		while(res->next()){
			cout << "<tr>";
			cout << "<td>" << res->getString("questionTitle") << "</td>";
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
		
		
		res = stmt->executeQuery("SELECT U.username, R.reputation, U.creationdate FROM tblUser U JOIN tblUserReputation R WHERE U.id = R.id ORDER BY R.reputation DESC LIMIT 10");

		cout << "<style>table, th, td{border: 2px solid black;}</style>";
		cout << "<table>";
		cout << "<tr>";
		cout << "<th>Username</th>";
		cout << "<th>Reputation</th>";
		cout << "<th>Creation Date</th>";
		cout << "</tr>";
		while(res->next()){
			cout << "<tr>";
			cout << "<td>" << res->getString("username") << "</td>";
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
		
		
		res = stmt->executeQuery("SELECT F.questionTitle, U.username FROM tblFeatured F JOIN tblUser U WHERE F.qOwner = U.id ORDER BY dateFeatured DESC LIMIT 10");

		cout << "<style>table, th, td{border: 2px solid black;}</style>";
		cout << "<table>";
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


//		res = stmt->executeQuery("SELECT id, upvotes FROM tblContent ORDER BY upvotes DESC LIMIT 10");
//		res = stmt->executeQuery("SELECT tblQuestion.questionTitle, tblContent.upvotes FROM tblQuestion LEFT OUTER JOIN tblContent WHERE tblQuestion.contentId = tblContent.id ORDER BY tblContent.upvotes DESC LIMIT 10");
//		res = stmt->executeQuery("SELECT Q.questionTitle, C.upvotes FROM tblQuestion Q LEFT OUTER JOIN tblContent C WHERE Q.contentId = C.id ORDER BY C.upvotes DESC LIMIT 10");
		res = stmt->executeQuery("SELECT Q.questionTitle, C.upvotes FROM tblQuestion Q JOIN tblContent C WHERE Q.contentId = C.id ORDER BY C.upvotes DESC LIMIT 10");

		cout << "<style>table, th, td{border: 2px solid black;}</style>";
		cout << "<table>";
		cout << "<tr>";
		cout << "<th>Question Title</th>";
		cout << "<th>Upvotes</th>";
		cout << "</tr>";
		while(res->next()){
			cout << "<tr>";
			cout << "<td>" << res->getString("questionTitle") << "</td>";
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
void Report::activityGraph(){
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
		
		
//		res = stmt->executeQuery("SELECT Q.tags, count(*) AS frequency FROM tblQuestion Q JOIN tblContent C WHERE Q.aowner = '" + this->userid + "' GROUP BY Q.tags ORDER BY count(*) DESC LIMIT 5");
//		res = stmt->executeQuery("SELECT Q.tags, Q.count(Q.tags) AS frequency FROM tblQuestion Q JOIN tblContent C WHERE Q.aowner = '" + this->userid + "' GROUP BY Q.tags ORDER BY Q.count(Q.tags) DESC LIMIT 5");
		res = stmt->executeQuery("SELECT tags, count(*) AS frequency FROM tblQuestion WHERE qowner = '" + this->userid + "' GROUP BY tags ORDER BY count(*) DESC LIMIT 5");

		cout << "<style>table, th, td{border: 2px solid black;}</style>";
		cout << "<table>";
		cout << "<tr>";
		cout << "<th>Tags</th>";
		cout << "<th>Frequency</th>";
		cout << "</tr>";
		while(res->next()){
			cout << "<tr>";
			cout << "<td>" << res->getString("tags") << "</td>";
			cout << "<td>" << res->getString("frequency") << "</td>";
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

void Report::topPostedQuestions(){
	cout << "<p>topPostedQuestions</p>";
}

void Report::topPostedAnswers(){
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
		
		
//		res = stmt->executeQuery("SELECT Con.id, Con.utimestamp	FROM (tblContent Con, tblAnswer A, tblQuestion Q, tblComment C WHERE (A.aowner = '" + this->userid + "') OR (Q.qowner = '" + this->userid + "') OR (C.aowner = '" + this->userid + "') ORDER BY Con.utimestamp DESC LIMIT 10");
		res = stmt->executeQuery("SELECT Con.id, Con.utimestamp	FROM (tblContent Con JOIN tblAnswer A) JOIN (tblContent Con JOIN tblQuestion Q) WHERE (A.aowner = '" + this->userid + "') OR (Q.qowner = '" + this->userid + "') ORDER BY Con.utimestamp DESC LIMIT 10");

		cout << "<style>table, th, td{border: 2px solid black;}</style>";
		cout << "<table>";
		cout << "<tr>";
		cout << "<th>Content ID</th>";
		cout << "<th>Timestamp</th>";
		cout << "</tr>";
		while(res->next()){
			cout << "<tr>";
			cout << "<td>" << res->getString("id") << "</td>";
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
