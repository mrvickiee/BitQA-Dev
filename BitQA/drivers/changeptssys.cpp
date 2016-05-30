//
//  changeptssys.cpp
//  BitQA
//
//  Created by Victor Ang on 29/05/2016.
//  Copyright © 2016 CSCI222. All rights reserved.
//

#include <stdio.h>
#include "../includes/html.hpp"
#include "../includes/database.hpp"
#include "../process/user.hpp"

using namespace std;
using namespace cgicc;

Cgicc cgi;
CgiEnvironment environemnt = cgi.getEnvironment();
User admin;
User targetUser;
string targetUsername;

void getUserInfo(){
	
	admin = User().getUserObj(BitQA::HTML::getUsername(cgi));
	targetUsername  = cgi("username");
	targetUser = User().getUserObj(targetUsername);
	
}


void populateTable(){
	
	
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
		
		
		res = stmt->executeQuery("SELECT * FROM tblReputationPoints;");
		
		cout << "<table class=\"table table-hover\">";
		cout << "<thead>";
		cout << "<tr>";
		cout << "<th>Title</th>";
		cout << "<th>Reputation Point</th>";
		cout << "<th></th>";
		cout << "</tr>";
		cout << "</thead>";
		while(res->next()){
			cout << "<tr>";
			cout << "<td>"<< res->getString("action") <<  "</td>";
			cout << "<td>" << res->getString("points") << "</td>";
			cout << "<td><a href=\"/processptschange.html?title="<<res->getString("action") << "&points=" << res->getString("points") << "\" class=\"btn btn-warning\">Modify</a></td>";
			cout << "</tr>";
		}
		cout << "</table>";
		
		delete res;
		delete stmt;
		delete con;
		
	} catch (sql::SQLException &e) {
		cout << "<p>Error</p>";
	}

	
	
	
	
	
	
}



int main(){
	BitQA::HTML::displayHeader("Admin - Change Rep Pts", cgi);
	getUserInfo();
	
	
	if(environemnt.getRequestMethod() == "POST"){
		
		
		
		
		
		
		
		
		
		
		
	}
	{
		
		
		if(admin.getReputation() >= User().checkUserRight("ISADMIN") && BitQA::HTML::getLoggedInStatus(cgi)){
			cout << "<h3>System wide points management</h3>";
			populateTable();
		}else{
			cout << "<h1>Admin only. Turn back!</h1>";
		}


		
		BitQA::HTML::displayFooter();
		
		
	}
}