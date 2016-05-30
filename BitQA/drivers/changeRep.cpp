//
//  changeRep.cpp
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



int main(){
	BitQA::HTML::displayHeader("Admin - Change Rep Pts", cgi);
	getUserInfo();
	if(BitQA::HTML::getLoggedInStatus(cgi)){
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
			
			prep_stmt = con->prepareStatement("UPDATE tblUserReputation SET reputation = ? WHERE username = ?");
			prep_stmt->setInt(1, repPts);
			prep_stmt->setString(2,targetUsername);
			prep_stmt->executeUpdate();
			delete con;
			cout<< "<script>"
			<< "window.location.href = \"/viewalluser.html\";"
			<<"</script>" << endl;
		}
		
		
		
		{
			
			if(admin.getReputation() >= User().checkUserRight("ASSIGNROLES") && BitQA::HTML::getLoggedInStatus(cgi)){
				cout << "<div class=\"text-center\" >";
				cout << "<h3>Change reputation points</h3>";
				
				cout << "<h4><strong>" <<targetUsername<<"</strong>'s  old points is <em>" << targetUser.getReputation() << "</em> pts</h4><br>";
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
	
	}else{
		cout << "<h1>Log in first</h1>";
	}
	
	BitQA::HTML::displayFooter();
	
}