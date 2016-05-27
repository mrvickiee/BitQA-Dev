#include "profile.hpp"

using namespace std;

BitQA::Profile::Profile(string userName)
{
	this->userName = userName;
	
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
	
	res = stmt->executeQuery("SELECT reputation FROM BitQA.tblUserReputation WHERE username = '" + this->userName + "';");
	
	int reputation = 0;
	
	while (res->next()) {
		reputation = res->getInt("displayname");
	}
	
	delete res;
	delete stmt;
	delete con;
	
	this->Reputation = reputation;
}

int BitQA::Profile::getUserReputation()
{
	return this->Reputation;
}
