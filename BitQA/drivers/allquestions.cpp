//
//  allquestions.cpp
//  BitQA
//
//  Created by Asjad Athick on 14/05/2016.
//  Copyright © 2016 CSCI222. All rights reserved.
//

#include <stdio.h>
#include "../includes/database.hpp"
#include "../includes/html.hpp"

using namespace cgicc;
using namespace std;

int main(){
	BitQA::HTML::displayHeader();
	
	Cgicc cgicc;
	
	try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::PreparedStatement *prep_stmt;
		sql::ResultSet *res;
		
		driver = get_driver_instance();
		con = driver->connect(BitQA::Database::HOST,
							  BitQA::Database::USERNAME,
							  BitQA::Database::PASSWORD
							  );
		
		con->setSchema(BitQA::Database::SCHEMA);
		
		int pageNum = 0;
		
		//get max page num
		
		
		int fromVal, toVal;
		if (cgicc("page") == ""){
			fromVal = 0;
			pageNum = 1;
		}
		else{
			fromVal = ((stoi(cgicc("page")) -1) * 100);
			pageNum = stoi(cgicc("page"));
		}
		
		
		if (fromVal < 0) {
			throw string("Page out of range");
		}
		
		toVal = fromVal + 100;
		
		prep_stmt = con->prepareStatement("CALL GetAllQuestions(?,?);");
		prep_stmt->setInt(1, fromVal);
		prep_stmt->setInt(2, toVal);
		res = prep_stmt->executeQuery();
		
		cout << "<h1>Showing all questions</h1>" << endl;
		cout << "<br><br>" << endl;
		
		//print results
		while (res->next()) {
			cout << "<div class=\"panel panel-default\"><div class=\"panel-body\">" << endl;
			cout << "<h4><a href='question.html?id=" << res->getString("id") <<  "'>" <<  res->getString("questionTitle") << endl;
			cout << "</a></h4>" << "Information" << "</div></div>" << endl;
			
		}
		
		cout << "<br>" << endl;
		
		//pagination
		cout << "<nav>" <<
		"<ul class='pagination'>" <<
		"<li>" <<
		"<a href='allquestions.html?page=" << ((pageNum-1) < 1 ? 1 : pageNum-1) <<"'aria-label='Previous'>" <<
		"<span aria-hidden='true'>&laquo;</span>" <<
		"</a></li>" <<
		"<li><a href='allquestions.html?page=" << pageNum + 1 <<"' aria-label='Next'>" <<
		"<span aria-hidden='true'>&raquo;</span>" <<
		"</a>" <<
		"</li>" <<
		"</ul>" <<
		"</nav>"  << endl;
		
		
		delete prep_stmt;
		delete con;
		
		
	} catch (sql::SQLException &e) {
		
		string error(e.what());
		
		BitQA::HTML::error("There was an error with SQL",
						   "Please go <a href=\"/\">home</a><p>Details: " + error + "</p>"
						   );
		
	} catch (exception &e) {
		
		string error(e.what());
		
		BitQA::HTML::error("There was an error viewing questions",
						   "Please go <a href=\"/\">home</a><p>Details: " + error + "</p>"
						   );
		
	} catch (string e){
		BitQA::HTML::error("There was an error viewing questions",
						   "Please go <a href=\"/\">home</a><p></p>"
						   );
	}
	
	BitQA::HTML::displayFooter();
	return 0;
}
