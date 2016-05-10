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
			//QuestionId = stoi(res->getString("questionTitle"));
		}
		
		delete res;
		delete stmt;
		delete con;
		
	} catch (sql::SQLException &e) {
		QuestionId = -1;
	}
	
	//Redirect to question page
	return false;
}

bool BitQA::Search::getUser()
{
	//At this point system knows it is a user 
	int foundID = -1;
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
			//foundID = stoi(res->getString("questionTitle"));
		}
		
		delete res;
		delete stmt;
		delete con;
		
	} catch (sql::SQLException &e) {
		foundID = -1;
	}
	
	//Redirect to user page
		return true;
}
