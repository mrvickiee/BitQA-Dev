#include "answer.hpp"
#include "../includes/database.hpp"

using namespace std;

BitQA::Answer::Answer(int AnswerID)
{
	this->AnswerID = AnswerID;
	this->ContentID = 0;
	this->AnswerOwner = "";
	
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
	
	
	res = stmt->executeQuery("SELECT contentId, aowner FROM tblAnswer WHERE id = '" + to_string(this->AnswerID) + "'");
	
	while (res->next()) {
		this->ContentID = res->getInt("contentId");
		this->AnswerOwner = res->getString("aowner");
	}
	
	delete res;
	delete stmt;
	delete con;
}

int BitQA::Answer::getAnswerID()
{
	return this->AnswerID;
}

string BitQA::Answer::getDetails()
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

vector<BitQA::Comment> BitQA::Answer::getComments()
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
	
	res = stmt->executeQuery("SELECT *, tblComment.id FROM tblComment WHERE tblComment.parentContentId IN (SELECT tblAnswer.contentId FROM tblAnswer WHERE id = '" + to_string(this->AnswerID) + "') AND deleted=0");
	
	
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

string BitQA::Answer::getVotes()
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

string BitQA::Answer::getUsername()
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
	
	res = stmt->executeQuery("SELECT displayname FROM tblUser WHERE username = '" + this->AnswerOwner + "'");
	
	while (res->next()) {
		username = res->getString("displayname");
	}
	
	delete res;
	delete stmt;
	delete con;
	
	return username;
}

string BitQA::Answer::getUserID()
{
	return this->AnswerOwner;
}

int BitQA::Answer::getContentID()
{
	return this->ContentID;
}