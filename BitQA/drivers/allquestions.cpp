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
		
		int fromVal, toVal;
		if (cgicc("page") == "")
			fromVal = 0;
		else
			fromVal = ((stoi(cgicc("page")) -1) * 100);
		
		
		if (fromVal < 0) {
			throw string("Page out of range");
		}
		
		toVal = fromVal + 100;
		
		prep_stmt = con->prepareStatement("CALL GetAllQuestions(?,?);");
		prep_stmt->setInt(1, fromVal);
		prep_stmt->setInt(2, toVal);
		res = prep_stmt->executeQuery();
		
		//print results
		while (res->next()) {
			cout << res->getString("questionTitle") << endl;
		}
		
		
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
