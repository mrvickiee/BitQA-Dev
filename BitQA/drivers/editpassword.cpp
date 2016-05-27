//
//  editpassword.cpp
//  BitQA
//
//  Created by Victor Ang on 27/05/2016.
//  Copyright © 2016 CSCI222. All rights reserved.
//


#include <stdio.h>
#include "../includes/html.hpp"
#include "../includes/database.hpp"
#include "../process/user.hpp"
#include "../includes/md5.hpp"
using namespace std;
using namespace cgicc;

User curUser;
cgicc::Cgicc cgi;
CgiEnvironment environment = cgi.getEnvironment();
string newPassword, confirmPassword, oldPassword,response;
bool error = false;

void getUserInfo(){
	string currUsername = BitQA::HTML::getUsername(cgi);
	
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
	prep_stmt = con->prepareStatement("SELECT *, (select tags from tblUserTags where id = A.id) as 'UserTag', (select reputation from tblUserReputation where username = A.username) as 'Reputation' from tblUser A where username = ?");
	prep_stmt->setString(1, currUsername);
	res = prep_stmt->executeQuery();
	
	if(res->next()){            //get user info and populate
		curUser.setUsername(currUsername);
		curUser.setPassword(res->getString("passhash"));
		curUser.setLocation(res->getString("location"));
		curUser.setDisplayName(res->getString("displayname"));
		curUser.setAge(res->getInt("age"));
		curUser.setEmail(res->getString("email"));
		curUser.setTag(res->getString("UserTag"));
		curUser.setReputation(res->getInt("Reputation"));
		curUser.setID(res->getInt("id"));
		
		
	}
	delete prep_stmt;
	delete con;
}

void updateUserPassword(){
	
	sql::Driver *driver;
	sql::Connection *con;
	sql::PreparedStatement *prep_stmt;
	
	driver = get_driver_instance();
	con = driver->connect(BitQA::Database::HOST,
						  BitQA::Database::USERNAME,
						  BitQA::Database::PASSWORD
						  );
	
	con->setSchema(BitQA::Database::SCHEMA);
	
	prep_stmt = con->prepareStatement("UPDATE tblUser SET passhash = ? WHERE username = ?");
	prep_stmt->setString(1, newPassword);
	prep_stmt->setString(2,curUser.getUsername());
	prep_stmt->executeUpdate();

	
	delete con,prep_stmt;

}


int main(){
	getUserInfo();
	if(environment.getRequestMethod() == "POST"){
		try{
			newPassword = cgi("newPassword");
			oldPassword = cgi("oldPassword");
			confirmPassword = cgi("confirmPassword");

			string oldHash = md5(oldPassword);

			if(oldHash == curUser.getPassword()){	//if the old password match
				if(newPassword == confirmPassword){
					newPassword = md5(newPassword);
					updateUserPassword();
				}else{		//if newpassword and confirm password do not match
					error = true;
					response += "Your new password and confirm password do not match!<br>";
				}
			}else{			//if old password is wrong
				error= true;
				response += "Error - Your old password is incorrect!<br>";
			
			}
		}catch(exception &e){
			error = true;
			response += "Error updating password:" +string(e.what()) + "<br>";
		}
	}
	{
		if(BitQA::HTML::getLoggedInStatus(cgi)){

			BitQA::HTML::displayHeader("Change password", cgi);
			
			cout << "<h3> Change Password </h3>";
			
			cout <<  "<form data-ajax=\"false\" method=\"post\">" << endl;
			
			cout << "<div class=\"form-group\">"<<endl;
			
			cout << "<label for= \"oldPassword\"> Enter old password </label>" << endl;
			cout << "<input type=\"password\" class=\"form-control\" id=\"oldPassword\" name=\"oldPassword\">" << endl;
			
			cout << "</div>" << endl;
			
			cout << "<div class=\"form-group\">" << endl;
			
			
			cout << "<label for= \"newPassword\">Enter new password </label>" << endl;
			cout << "<input type=\"password\" class=\"form-control\" id=\"newPassword\" name=\"newPassword\">" << endl;
			
			cout << "</div>" << endl;
			
			cout << "<div class=\"form-group\">" << endl;
			
			cout << "<label for= \"confirmPassword\">Reenter new password </label>" << endl;
			cout << "<input type=\"password\" class=\"form-control\" id=\"confirmPassword\" name=\"confirmPassword\">" << endl;
			
			cout << "</div>" << endl;
			
			
			cout << "<button type=\"submit\" class=\"btn btn-default\"> Change password </button> " <<endl;
			cout << "</div>" << endl;
			cout << "</form>" << endl;
		}else{
			cout << "Dont attempt to break the server please" <<endl;
		}
	
	}
	
	if (environment.getRequestMethod() == "POST") {
		if (error) {
			cout << "<div class=\"alert alert-danger\">" << endl;
			cout << "<strong>" << response << "</strong> "<< endl;
			cout << "</div>";
		} else {
			cout << "<div class=\"alert alert-success\">" << endl;
			cout << "<strong>Success!</strong> Password updated successfully." << endl;
			cout << "</div>";
			cout << "<script>window.location.href=\""
			<< BitQA::HTML::HOST + "/profile.html?username=" + curUser.getUsername()
			<<"\"</script>" << endl;
		}
	}
	
	BitQA::HTML::displayFooter();
	return 0;
}