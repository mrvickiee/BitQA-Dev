#include "comment.hpp"
#include "../includes/database.hpp"

using namespace std;

string BitQA::Comment::getCommentIDStr(){
	return to_string(CommentID);
}

BitQA::Comment::Comment(int CommentID)
{
	this->CommentID = CommentID;
	
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	
	
	driver = get_driver_instance();
	con = driver->connect(BitQA::Database::HOST, BitQA::Database::USERNAME, BitQA::Database::PASSWORD);
	con->setSchema(BitQA::Database::SCHEMA);
	stmt = con->createStatement();
	
	
	res = stmt->executeQuery("SELECT contentId, aowner FROM tblComment WHERE id = '" + to_string(this->CommentID) + "'");
	
	while (res->next()) {
		this->ContentID = res->getInt("contentId");
		this->CommentOwner = res->getString("aowner");
	}
	
	delete res;
	delete stmt;
	delete con;
	
}

string BitQA::Comment::getContentID()
{
	return to_string(this->ContentID);
}

string BitQA::Comment::getOwnerID()
{
	return this->CommentOwner;
}


int BitQA::Comment::getCommentID()
{
	return this->CommentID;
}

string BitQA::Comment::getDetails()
{
	string details = "";
	
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	
	driver = get_driver_instance();
	con = driver->connect(
						  BitQA::Database::HOST,
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

string BitQA::Comment::getVotes()
{
	string votes = "";
	
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	
	
	driver = get_driver_instance();
	con = driver->connect(BitQA::Database::HOST, BitQA::Database::USERNAME, BitQA::Database::PASSWORD);
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

string BitQA::Comment::getUsername()
{
	string username = "";
	
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	
	driver = get_driver_instance();
	con = driver->connect(BitQA::Database::HOST, BitQA::Database::USERNAME, BitQA::Database::PASSWORD);
	con->setSchema(BitQA::Database::SCHEMA);
	stmt = con->createStatement();
	
	res = stmt->executeQuery("SELECT displayname FROM tblUser WHERE username = '" + this->CommentOwner + "'");
	
	while (res->next()) {
		username = res->getString("displayname");
	}
	
	delete res;
	delete stmt;
	delete con;
	
	return username;
}

