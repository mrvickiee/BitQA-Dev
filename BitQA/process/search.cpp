#include "../includes/database.hpp"
#include "search.hpp"

using namespace std;

BitQA::Search::Search()
{
	searchTerm = "@liam";
}

BitQA::Search::Search(string query)
{
	searchTerm = query;
}

bool BitQA::Search::getQuestion()
{
		int QuestionId = -1;
		
		
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
		
		
		res = stmt->executeQuery("SELECT questionTitle FROM tblQuestion WHERE id = '" + this->searchTerm + "'");
		
		while (res->next()) {
			QuestionId = stoi(res->getString("questionTitle"));
		}
		
		delete res;
		delete stmt;
		delete con;
		
	} catch (sql::SQLException &e) {
		QuestionId = -1;
		return false;
	}
	
	//Redirect to question page with QuestionID
	
	return false;
}

bool BitQA::Search::getUser()
{
	//At this point system knows it is a user 
	
	//Discard @ symbol
	this->searchTerm.erase(0,1);
	int foundID;
	
	
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
		
		res = stmt->executeQuery("SELECT id FROM tblUser WHERE username = '" + (this->searchTerm) + "'");
		
		while (res->next()) {
			//incorrect??
			foundID = stoi(res->getString("id"));
		}
		
		delete res;
		delete stmt;
		delete con;
		
	} catch (sql::SQLException &e) {
		foundID = -1;
		return false;
	}
	
	//Redirect to user page
	//Direct to user page with foundID
	return true;
}
