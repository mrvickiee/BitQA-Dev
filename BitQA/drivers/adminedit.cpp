//
//  adminedit.cpp
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


User targetUser;
User admin;
Cgicc cgi;
CgiEnvironment environment = cgi.getEnvironment();

 string displayName, email, tags, location, ageString;
int age;
void getUserInfo(){

	targetUser = User().getUserObj(cgi("username"));
	admin = User().getUserObj(BitQA::HTML::getUsername(cgi));

}

void editUserProfile(User user){
	sql::Driver *driver;
	sql::Connection *con;
	sql::PreparedStatement *prep_stmt, *prep_stmt2;
	
	driver = get_driver_instance();
	con = driver->connect(BitQA::Database::HOST,
						  BitQA::Database::USERNAME,
						  BitQA::Database::PASSWORD
						  );
	
	con->setSchema(BitQA::Database::SCHEMA);
	
	prep_stmt = con->prepareStatement("UPDATE tblUser SET displayname = ?, age = ?, location = ?, email = ? WHERE username = ?");
	prep_stmt->setString(1, user.getDisplayName());
	prep_stmt->setInt(2, user.getAge());
	prep_stmt->setString(3, user.getLocation());
	prep_stmt->setString(4, user.getEmail());
	prep_stmt->setString(5, targetUser.getUsername());
	
	prep_stmt->executeUpdate();
	
	prep_stmt2 = con->prepareStatement("UPDATE tblUserTags SET tags = ? WHERE id = ?");
	prep_stmt2->setString(1, user.getTag());
	prep_stmt2->setInt(2, targetUser.getID());
	
	prep_stmt2->executeUpdate();
	
	delete prep_stmt;
	delete con;
}


int main(){
	BitQA::HTML::displayHeader("Admin Edit", cgi);
	getUserInfo();
	
	if(environment.getRequestMethod() == "POST"){
		displayName = cgi("displayName");
		location = cgi("location");
		tags = cgi("tag");
		ageString = cgi("age");
		email = cgi("email");
		age = atoi(ageString.c_str());
		
		User updateUser = User();
		updateUser.setTag(tags);
		updateUser.setDisplayName(displayName);
		updateUser.setLocation(location);
		updateUser.setAge(age);
		updateUser.setEmail(email);
		
		editUserProfile(updateUser);
		
		
		cout << "<script>window.location.href=\""
		<< BitQA::HTML::HOST + "/profile.html?username=" + targetUser.getUsername()
		<<"\"</script>" << endl;
		

		
		
	}

	{
		
		if(admin.getReputation() >= User().checkUserRight("EDITANYPROFILE")){
			cout << "<h3> Admin page : Edit other user profile </h3>";
			
			cout << "<form data-ajax=\"false\" method=\"post\">"<<endl;
			
			cout << "<div class=\"form-group\">" << endl;
			
			cout << "<label for= \"displayName\"> Display name </label>" << endl;
			cout << "<input type=\"text\" class=\"form-control\" id=\"displayName\" name=\"displayName\" value = \"" << targetUser.getDisplayName() << "\"> " << endl;
			
			cout << "</div>" << endl;
			
			cout << "<div class=\"form-group\">" << endl;
			
			cout << "<label for= \"email\"> Email </label>" << endl;
			cout << "<input type=\"email\" class=\"form-control\" id=\"email\" name=\"email\" value=\"" << targetUser.getEmail() << "\">" << endl;
			
			cout << "</div>" << endl;
			
			cout << "<div class=\"form-group\">" << endl;
			
			cout << "<label for= \"tag\"> Tags of interest </label>" << endl;
			cout << "<input type=\"text\" class=\"form-control\" id=\"tag\" name=\"tag\" value=\"" << targetUser.getTag() << "\">"<< endl;
			
			cout << "</div>" << endl;
			
			cout << "<div class=\"form-group\">" << endl;
			
			cout << "<label for= \"location\"> Location </label>" << endl;
			cout << "<input type=\"text\" class=\"form-control\" id=\"location\" name=\"location\" value=\"" << targetUser.getLocation() << "\">" << endl;
			
			cout << "</div>" << endl;
			
			cout << "<div class=\"form-group\">" << endl;
			
			cout << "<label for= \"age\"> Age </label>" << endl;
			cout << "<input type=\"number\" min=\"1\" max = \"99\" class=\"form-control\" id=\"age\" name=\"age\" value=\"" << targetUser.getAge() << "\">" << endl;
			
			cout << "</div>" << endl;
			
			cout << "<button type=\"submit\" class=\"btn btn-default\"> Update </button> " <<endl;
			
			cout << "</div>" << endl;
			cout << "</form>" << endl;

			
			
			
		}else{
			
			
			cout << "<h1>You do not have sufficient reputation points to view this page. Go back!</h1>" << endl;
			
			
		}
	

	}
	
	
	
	
}