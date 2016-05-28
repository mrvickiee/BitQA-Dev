//
//  editprofile.cpp
//  BitQA
//
//  Created by Victor Ang on 22/05/2016.
//  Copyright © 2016 CSCI222. All rights reserved.
//

#include <stdio.h>
#include "../includes/html.hpp"
#include "../includes/database.hpp"
#include "../process/user.hpp"
using namespace std;
using namespace cgicc;

User curUser;
cgicc::Cgicc cgi;
CgiEnvironment environment = cgi.getEnvironment();
bool valid = false;
auto error = false;

void getUserInfo(){
	
	string currUsername = BitQA::HTML::getUsername(cgi);
	curUser = User().getUserObj(currUsername);
	
	
	
//    sql::Driver *driver;
//    sql::Connection *con;
//    sql::PreparedStatement *prep_stmt;
//    sql::ResultSet *res;
//    
//    driver = get_driver_instance();
//    con = driver->connect(BitQA::Database::HOST,
//                          BitQA::Database::USERNAME,
//                          BitQA::Database::PASSWORD
//                          );
//    
//    con->setSchema(BitQA::Database::SCHEMA);
//    prep_stmt = con->prepareStatement("SELECT *, (select tags from tblUserTags where id = A.id) as 'UserTag', (select reputation from tblUserReputation where username = A.username) as 'Reputation' from tblUser A where username = ?");
//    prep_stmt->setString(1, currUsername);
//    res = prep_stmt->executeQuery();
//    
//    if(res->next()){            //get user info and populate
//        curUser.setUsername(currUsername);
//        curUser.setLocation(res->getString("location"));
//        curUser.setDisplayName(res->getString("displayname"));
//        curUser.setAge(res->getInt("age"));
//        curUser.setEmail(res->getString("email"));
//        curUser.setTag(res->getString("UserTag"));
//        curUser.setReputation(res->getInt("Reputation"));
//        curUser.setID(res->getInt("id"));
//        
//        valid = true;
//    }
//    delete prep_stmt;
//    delete con;
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
    prep_stmt->setString(5, curUser.getUsername());
    
    prep_stmt->executeUpdate();
    
    prep_stmt2 = con->prepareStatement("UPDATE tblUserTags SET tags = ? WHERE id = ?");
    prep_stmt2->setString(1, user.getTag());
    prep_stmt2->setInt(2, curUser.getID());
    
    prep_stmt2->executeUpdate();
    
    delete prep_stmt,prep_stmt2;
    delete con;
}

void loggedInStatus(){
	if(BitQA::HTML::getLoggedInStatus(cgi)){
		valid = true;
	}
}



int main(){
    
    CgiEnvironment environment = cgi.getEnvironment();
    string displayName, email, tags, location, ageString;
    int age;
	getUserInfo();
	BitQA::HTML::displayHeader("Edit profile", cgi);
	
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
		<< BitQA::HTML::HOST + "/profile.html?username=" + curUser.getUsername()
		<<"\"</script>" << endl;

		
    }
    {


		if(BitQA::HTML::getLoggedInStatus(cgi)){
			cout << "<h3> Edit Profile </h3>";
			
			cout << "<form data-ajax=\"false\" method=\"post\">"<<endl;
			
			cout << "<div class=\"form-group\">" << endl;
			
			cout << "<label for= \"displayName\"> Display name </label>" << endl;
			cout << "<input type=\"text\" class=\"form-control\" id=\"displayName\" name=\"displayName\" value = \"" << curUser.getDisplayName() << "\"> " << endl;
			
			cout << "</div>" << endl;
			
			cout << "<div class=\"form-group\">" << endl;
			
			cout << "<label for= \"email\"> Email </label>" << endl;
			cout << "<input type=\"email\" class=\"form-control\" id=\"email\" name=\"email\" value=\"" << curUser.getEmail() << "\">" << endl;
			
			cout << "</div>" << endl;
			
			cout << "<div class=\"form-group\">" << endl;
			
			cout << "<label for= \"tag\"> Tags of interest </label>" << endl;
			cout << "<input type=\"text\" class=\"form-control\" id=\"tag\" name=\"tag\" value=\"" << curUser.getTag() << "\">"<< endl;
			
			cout << "</div>" << endl;
			
			cout << "<div class=\"form-group\">" << endl;
			
			cout << "<label for= \"location\"> Location </label>" << endl;
			cout << "<input type=\"text\" class=\"form-control\" id=\"location\" name=\"location\" value=\"" << curUser.getLocation() << "\">" << endl;
			
			cout << "</div>" << endl;
			
			cout << "<div class=\"form-group\">" << endl;
			
			cout << "<label for= \"age\"> Age </label>" << endl;
			cout << "<input type=\"number\" min=\"1\" max = \"99\" class=\"form-control\" id=\"age\" name=\"age\" value=\"" << curUser.getAge() << "\">" << endl;
			
			cout << "</div>" << endl;
			
			cout << "<button type=\"submit\" class=\"btn btn-default\"> Update </button> " <<endl;
			
			cout << "</div>" << endl;
			cout << "</form>" << endl;
		
		}else{
			cout << "Dont attempt to break the server please!";
		}
	}
	
		if (environment.getRequestMethod() == "POST") {
			if (error) {
				cout << "<div class=\"alert alert-danger\">" << endl;
				cout << "<strong>Error!</strong> "<< endl;
				cout << "</div>";
			} else {
				cout << "<div class=\"alert alert-success\">" << endl;
				cout << "<strong>Success!</strong> Profile updated successfully." << endl;
				cout << "</div>";
			}
			
		}

    BitQA::HTML::displayFooter();
    return 0;
    
}