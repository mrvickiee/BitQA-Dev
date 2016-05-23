#include "question.hpp"
#include "../includes/database.hpp"

using namespace std;

BitQA::Question::Question(int QuestionID)
{
	this->QuestionID = QuestionID;
	this->ContentID = 0;
	this->QuestionOwner = 0;
	
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
}

string BitQA::Question::getQuestionContentID()
{
	return to_string(this->ContentID);
}

vector<BitQA::Comment> BitQA::Question::getComments()
{
	vector<BitQA::Comment> result;
	
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
	
	res = stmt->executeQuery("SELECT *, tblComment.id FROM tblComment WHERE tblComment.parentContentId IN (SELECT tblQuestion.contentId FROM tblQuestion WHERE id = '" + to_string(this->QuestionID) + "') AND deleted=0");
	
	
	while (res->next()) {
		//construct comment
		BitQA::Comment insComment(res->getInt("id"));
		
		result.push_back(insComment);
	}
	
	delete res;
	delete stmt;
	delete con;
	
	return result;
}

vector<int> BitQA::Question::getContentID()
{
	vector<int> contentID;
	
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
	
	
	res = stmt->executeQuery("SELECT contentId FROM tblComment WHERE parentContentId = '" + to_string(this->ContentID) + "'");
	
	while (res->next()) {
		contentID.push_back(res->getInt("contentId"));
	}
	
	delete res;
	delete stmt;
	delete con;
	
	return contentID;
}

string BitQA::Question::getTitle()
{
	string title = "";
	
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

	return title;
}

string BitQA::Question::getDetails()
{
	string details = "";
	
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
	
	return details;
}

string BitQA::Question::getVotes()
{
	string votes = "";
	
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
	
	return votes;
}

string BitQA::Question::getQuestionID(){
	return to_string(QuestionID);
}

string BitQA::Question::getUsername()
{
	string username = "";
	
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
	
	res = stmt->executeQuery("SELECT displayname FROM tblUser WHERE username = '" + to_string(this->QuestionOwner) + "'");
	
	while (res->next()) {
		username = res->getString("displayname");
	}
	
	delete res;
	delete stmt;
	delete con;
	
	return username;
}
