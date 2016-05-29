//
//  admindeactivate.cpp
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
string targetUsername;

int main(){
	BitQA::HTML::displayHeader("Admin: User Account Deactivation", cgi);
	
	if(BitQA::HTML::getLoggedInStatus(cgi)){
		admin = User().getUserObj(BitQA::HTML::getUsername(cgi));
	}else{
		admin.setReputation(0);
	}
	
	targetUsername = cgi("username");
	
	if(environemnt.getRequestMethod() == "POST"){
		sql::Driver *driver;
		sql::Connection *con;
		sql::PreparedStatement *prep_stmt;
		
		driver = get_driver_instance();
		con = driver->connect(BitQA::Database::HOST,
							  BitQA::Database::USERNAME,
							  BitQA::Database::PASSWORD
							  );
		
		con->setSchema(BitQA::Database::SCHEMA);
		
		prep_stmt = con->prepareStatement("UPDATE tblUser SET deleted = 1 WHERE username = ?");
		prep_stmt->setString(1,targetUsername);
		prep_stmt->executeUpdate();
		delete con;
		cout<< "<script>"
		<< "window.location = \"/index.html\";"
		<<"</script>" << endl;
	}
	{
		
		if(admin.getReputation() >= User().checkUserRight("DELETEANYPROFILE")){
			cout<< "<div class=\"text-center\">"
			<< "<h2>Account Deactivation</h2>"
			<< "Warning: There is no turning back after clicking deactivation button.<br>"
			<< "Are you sure you want to deactivate <strong>" << targetUsername <<"</strong> account?<br>"
			<< "<form style=\"margin-top:2%\" method=\"post\">"
			<< "<button type=\"submit\" class=\"btn btn-danger\">Deactivate</button>"
			<< "<button style=\"margin-left:2%\" onClick=\"javascript:window.location.href='/index.html'\" type=\"button\" class=\"btn btn-primary\">Nope</button>"
			<<"</form>"
			<< "</div>" << endl;
			
		}else{
			cout << "<h1>You do not have sufficient reputation points to view this page. Go back!</h1>" << endl;
			
		}
	}
	
	BitQA::HTML::displayFooter();
	
}