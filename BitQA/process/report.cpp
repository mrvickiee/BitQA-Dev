/*
Matthew Twose, mt156, 4510550
BitQA
report functionality declaration
*/
#include "report.hpp"

Report::Report(){}

//Homepage reports

void Report::recQuestions(){
	cout << "<p>recQuestions</p>";

	/*
	SELECT questiontitle, dateposted
	FROM tblQuestion?
	WHERE [the tags this user has] = [tags the current question has]
	ORDER BY dateposted DESC LIMIT 10;
	*/
}

void Report::topUsers(){
	cout << "<p>topUsers</p>";

	/*
	SELECT U.username, R.reputation, U.creationdate
	FROM tblUser U LEFT OUTER JOIN tblUserReputation R
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
		
		
		res = stmt->executeQuery("SELECT U.username, R.reputation, U.creationdate FROM tblUser U LEFT OUTER JOIN tblUserReputation R WHERE U.id = R.id ORDER BY R.reputation DESC LIMIT 10");

	} catch (sql::SQLException &e) {
		cout << "<p>Error</p>";
	}

}

void Report::featured(){
	cout << "<p>featured</p>";

	/*
	SELECT F.questionTitle, U.username
	FROM tblFeatured F LEFT OUTER JOIN tblUser U
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
		
		
		res = stmt->executeQuery("SELECT F.questionTitle, U.username FROM tblFeatured F LEFT OUTER JOIN tblUser U WHERE F.qOwner = U.id ORDER BY dateFeatured DESC LIMIT 10");

	} catch (sql::SQLException &e) {
		cout << "<p>Error</p>";
	}
}

void Report::topQuestions(){
	cout << "<p>topQuestions</p>";

	/*
	SELECT Q.questionTitle, C.upvotes
	FROM tblQuestion Q LEFT OUTER JOIN tblContent C
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
		
		
		res = stmt->executeQuery("SELECT Q.questionTitle, C.upvotes FROM tblQuestion Q LEFT OUTER JOIN tblContent C WHERE Q.contentId = C.id ORDER BY C.upvotes DESC LIMIT 10");

	} catch (sql::SQLException &e) {
		cout << "<p>Error</p>";
	}

}

//User profile reports
void Report::activityGraph(){
	cout << "<p>activityGraph</p>";
}

void Report::topTags(){
	cout << "<p>topTags</p>";
}

void Report::topPostedQuestions(){
	cout << "<p>topPostedQuestions</p>";
}

void Report::topPostedAnswers(){
	cout << "<p>topPostedAnswers</p>";
}

void Report::postHistory(){
	cout << "<p>postHistory</p>";
}

