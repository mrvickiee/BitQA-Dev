#include "../includes/database.hpp"
#include "../includes/html.hpp"
#include "mySearch.hpp"

using namespace std;
using namespace cgicc;

MySearch::MySearch()
{
	searchTerm = "";
}

MySearch::MySearch(string query)
{
	searchTerm = query;
}

int MySearch::getQuestion()
{
	int *QuestionId = new int;
		
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
		
		
		res = stmt->executeQuery("SELECT contentId FROM tblQuestion WHERE tag LIKE = '" + this->searchTerm + "'");
		
		while (res->next()) {
			QuestionId = stoi(res->getString("contentId"));
		}
		
		delete res;
		delete stmt;
		delete con;
		
	} catch (sql::SQLException &e) {
		QuestionId = -1;
		return QuestionId;
	}
	
		
	return QuestionId;
}

int MySearch::getUser()
{
	//At this point system knows it is a user 
	
	//Discard @ symbol
	this->searchTerm.erase(0,1);
	int foundID;
	string statement;
	
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
			foundID = stoi(res->getString("id"));
		}
		
		delete res;
		delete stmt;
		delete con;
		
	} catch (sql::SQLException &e) {
		foundID = -1;
		return foundID;
	}
	
	return foundID;
}

string prepareStatement(string table, string select, string where)
{
	string statement = "SELECT ";
	statement.append(select + " FROM " + table + " WHERE " + where + " = ");
	return statement;
}

