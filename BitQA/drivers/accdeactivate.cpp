//
//  accdeactivate.cpp
//  BitQA
//
//  Created by Victor Ang on 28/05/2016.
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

int main(){
	BitQA::HTML::displayHeader("Account Deactivation", cgi);
	
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
		prep_stmt->setString(1,BitQA::HTML::getUsername(cgi));
		prep_stmt->executeUpdate();
		delete con,prep_stmt;
		cout<< "<script>"
		<< "Cookies.remove(\"username\");"
		<< "Cookies.remove(\"displayname\");"
		<< "window.location = \"/index.html\";"
		<<"</script>" << endl;
		
		
	}
	{
	
		
		if(BitQA::HTML::getLoggedInStatus(cgi)) {

			cout<< "<div class=\"text-center\">"
				<< "<h2>Account Deactivation</h2>"
				<< "Warning: There is no turning back after clicking deactivation button.<br>"
				<< "Are you sure you want to deactivate your account?<br>"
				<< "<form style=\"margin-top:2%\" method=\"post\">"
				<< "<button type=\"submit\" class=\"btn btn-danger\">Deactivate</button>"
				<< "<button style=\"margin-left:2%\" onClick=\"javascript:window.location.href='/index.html'\" type=\"button\" class=\"btn btn-primary\">Nope</button>"
				<<"</form>"
				<< "</div>" << endl;
			
		}else{
			cout <<"<h3>Don't attempt to break the server please</h3>" << endl;
		}
		
	
	}
	BitQA::HTML::displayFooter();
	return 0;
}