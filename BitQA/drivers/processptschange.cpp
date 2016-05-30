//
//  processptschange.cpp
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
string actionTitle;
int oldPts ;


int main(){
	BitQA::HTML::displayHeader("Change pts", cgi);
	actionTitle = cgi("title");
	oldPts = stoi(cgi("points"));
	admin = User().getUserObj(BitQA::HTML::getUsername(cgi));
	
	if(environemnt.getRequestMethod() == "POST"){
		string repPtsStr = cgi("repPts");
		int repPts = stoi(repPtsStr);
		
		sql::Driver *driver;
		sql::Connection *con;
		sql::PreparedStatement *prep_stmt;
		
		driver = get_driver_instance();
		con = driver->connect(BitQA::Database::HOST,
							  BitQA::Database::USERNAME,
							  BitQA::Database::PASSWORD
							  );
		
		con->setSchema(BitQA::Database::SCHEMA);
		
		prep_stmt = con->prepareStatement("UPDATE tblReputationPoints SET points = ? WHERE action = ?");
		prep_stmt->setInt(1, repPts);
		prep_stmt->setString(2,actionTitle);
		prep_stmt->executeUpdate();
		delete con;
		cout<< "<script>"
		<< "window.location.href = \"/changeptssys.html\";"
		<<"</script>" << endl;
	}
	{
		
		
		if(admin.getReputation() >= User().checkUserRight("ISADMIN") && BitQA::HTML::getLoggedInStatus(cgi)){
			cout << "<div class=\"text-center\" >";
			cout <<"<h3>Enter new points for " << actionTitle << "</h3>";
			cout << "<h4><strong>" <<actionTitle<<"</strong>'s  old points is <em>" << oldPts << "</em> pts</h4><br>";
			cout << "<form method=\"post\">";
			cout << "<label for=\"repPts\">New Reputation Pts: </label>";
			cout << "<input id=\"repPts\" name=\"repPts\" type=\"number\"/> <br>" ;
			cout << "<button type=\"submit\" class=\"btn btn-default\">Change</button>";
			cout << "</form>";
			cout <<"</div>";
			
		}else{
			
			cout << "<h1>Admin only. Turn back!</h1>";
		}
		
	}
	
	
	
	
	
	BitQA::HTML::displayFooter();
	
}



