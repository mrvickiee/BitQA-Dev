#include "../includes/database.hpp"
#include "../includes/html.hpp"
#include "search.hpp"
#include <sstream>

using namespace std;
using namespace cgicc;

//Does not work in here??
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
	//cout << "<h1>" << text << "</h1>";
	return text;
}


MySearch::MySearch()
{
	this->searchTerm = "<php><mysql>";
}

MySearch::MySearch(string query)
{
	this->searchTerm = query;
}

void MySearch::getQuestion()
{
	vector<int> result;
	int QuestionId = 0;
	
	//Splits words into individual tags
	string searchTags;
	searchTags = spaceToTag(this->searchTerm);
	

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
		
		
		res = stmt->executeQuery("SELECT contentId, questionTitle FROM tblQuestion WHERE tags LIKE '<php><mysql>'");
		
		cout << "<h2> Search results: </h2>" << endl;
		cout << "<table>";
		cout << "<tr>";
		cout << "<th>Question Title</th>";
		cout << "</tr>";
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
		}
		cout << "</table>";
		
		delete res;
		delete stmt;
		delete con;
		
	} catch (sql::SQLException &e) {
		QuestionId = -1;
		cout <<"<h1>error" << QuestionId <<  "</h1>";
		return;
	}
	
		
	return;
}

int MySearch::getUser()
{
	//At this point system knows it is a user 
	
	//Discard @ symbol
	this->searchTerm.erase(0,1);
	int foundID = 0;
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
		//Testing
		//cout << "<br> <p>" << this->searchTerm << "</p>" << endl;
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT username FROM tblUser WHERE displayname = '" + (this->searchTerm) + "'");

		while (res->next()) {
			foundID = stoi(res->getString("username"));
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

string MySearch::getSearchTerm()
{
	return this->searchTerm;
}

