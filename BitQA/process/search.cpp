#include "../includes/database.hpp"
#include "../includes/html.hpp"
#include "search.hpp"
#include <sstream>

using namespace std;
using namespace cgicc;


string spaceToTag(string text) {
	int length = text.length();
	for(int i =0; i < length; i++) {
		if(text.at(i) == ' ') {
			text.replace(i, 1, "><");
			i++;
		}	
	}
	text.replace(text.begin(), text.begin(), "<");
	text.replace(text.end(), text.end(), ">");
	return text;
}


MySearch::MySearch()
{
	this->searchTerm = "";
}

MySearch::MySearch(string query)
{
	this->searchTerm = query;
}

void MySearch::getQuestion(bool filter)
{
	bool found = false;
	
	//Splits words into individual tags
	string searchTags;
	searchTags = spaceToTag(this->searchTerm);
	
	if(!filter) {
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
			
	
    res = stmt->executeQuery("SELECT contentId, questionTitle FROM tblQuestion WHERE tags LIKE '" + searchTags + "'");

			cout << "<table>";
			while (res->next()) {
				cout << "<ul>";
				//cout << "<li>" << res->getString("questionTitle") << "</li>";
				int qID = stoi(res->getString("contentId"));	
				string qPage = to_string(qID);
				qPage = (BitQA::HTML::HOST + "/question.html?id=" + qPage);
				cout << "<li>";
				cout << "<a href=\"" << qPage << "\">" << res->getString("questionTitle") << "</a>" << endl;
				cout << "</li>";
				cout << "</ul>";
				found = true;
			}
			cout << "</table>";
			
			delete res;
			delete stmt;
			delete con;
			
		} catch (sql::SQLException &e) {
			cout <<"<h1>A</h1>" << endl;
			cout <<"<h1>error</h1>";
			return;
		}
		
		if(!found) {
				cout << "<h2> No results </h2>" << endl;
		}
	}else {
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
			
		
			res = stmt->executeQuery("SELECT contentId, questionTitle FROM tblQuestion WHERE tags LIKE '" + searchTags + "' AND acceptedAnswer = 0");

			cout << "<table>";
			while (res->next()) {
				cout << "<ul>";
				//cout << "<li>" << res->getString("questionTitle") << "</li>";
				int qID = stoi(res->getString("contentId"));	
				string qPage = to_string(qID);
				qPage = (BitQA::HTML::HOST + "/question.html?id=" + qPage);
				cout << "<li>";
				cout << "<a href=\"" << qPage << "\">" << res->getString("questionTitle") << "</a>" << endl;
				cout << "</li>";
				cout << "</ul>";
				found = true;
			}
			cout << "</table>";
			
			delete res;
			delete stmt;
			delete con;
			
		} catch (sql::SQLException &e) {
			cout <<"<h1>B</h1>" << endl;
			cout <<"<h1>error</h1>";
			return;
		}
		
		if(!found) {
				cout << "<h2> No results </h2>" << endl;
		}		
		
		
	}
	return;
}

int MySearch::getUser()
{
	//At this point system knows it is a user 
	bool found = false;
	
	//Discard @ symbol
	this->searchTerm.erase(0,1);
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
		//Testing
		//cout << "<br> <p>" << this->searchTerm << "</p>" << endl;
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT username FROM tblUser WHERE displayname = '" + (this->searchTerm) + "'");

		while (res->next()) {
			foundID = stoi(res->getString("username"));
			found = true;
		}
		
		delete res;
		delete stmt;
		delete con;
		
	} catch (sql::SQLException &e) {
		foundID = -1;
		return foundID;
	}
	if(!found) {
		cout << "<h2> User not found </h2>" << endl;
	}
	
	return foundID;
}

string MySearch::getSearchTerm()
{
	return this->searchTerm;
}
