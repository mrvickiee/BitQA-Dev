#include "question.hpp"
#include "../includes/database.hpp"

using namespace std;

BitQA::Question::Question(int QuestionID)
{
	this->QuestionID = QuestionID;
	this->ContentID = 0;
	this->QuestionOwner = 0;
	
	
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
		
		
		res = stmt->executeQuery("SELECT contentId, qowner FROM tblQuestion WHERE id = '" + to_string(this->QuestionID) + "'");
		
		while (res->next()) {
			this->ContentID = res->getInt("contentId");
			this->QuestionOwner = res->getInt("qowner");
		}
		
		delete res;
		delete stmt;
		delete con;
		
	} catch (sql::SQLException &e) {
		this->ContentID = NULL;
	}
}

vector<int> BitQA::Question::getContentID()
{
	vector<int> contentID;
	
	for (int i = 0; i < 5; i++) {
		contentID.push_back(i);
	}
	
	return contentID;
}

string BitQA::Question::getTitle()
{
	string title = "";
	
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
		
		
		res = stmt->executeQuery("SELECT questionTitle FROM tblQuestion WHERE id = '" + to_string(this->QuestionID) + "'");
		
		while (res->next()) {
			title = res->getString("questionTitle");
		}
		
		delete res;
		delete stmt;
		delete con;
		
	} catch (sql::SQLException &e) {
		title = "Error";
	}
	
	return title;
}

string BitQA::Question::getDetails()
{
	string details = "";
	
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
		
		res = stmt->executeQuery("SELECT content FROM tblContent WHERE id = '" + to_string(this->ContentID) + "'");
		
		while (res->next()) {
			details = res->getString("content");
		}
		
		delete res;
		delete stmt;
		delete con;
		
	} catch (sql::SQLException &e) {
		details = "Error";
	}
	
	return details;
}

string BitQA::Question::getVotes()
{
	string votes = "";
	
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
		
		res = stmt->executeQuery("SELECT (upvotes - downvotes) FROM tblContent WHERE id = '" + to_string(this->ContentID) + "'");
		
		while (res->next()) {
			votes = res->getString("(upvotes - downvotes)");
		}
		
		delete res;
		delete stmt;
		delete con;
		
	} catch (sql::SQLException &e) {
		votes = "Error";
	}
	
	return votes;
}

string BitQA::Question::getUsername()
{
	string username = "";
	
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
		
		res = stmt->executeQuery("SELECT displayname FROM tblUser WHERE id = '" + to_string(this->QuestionOwner) + "'");
		
		while (res->next()) {
			username = res->getString("displayname");
		}
		
		delete res;
		delete stmt;
		delete con;
		
	} catch (sql::SQLException &e) {
		username = "Error";
	}
	
	return username;
}
