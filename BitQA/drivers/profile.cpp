//
//  profile.cpp
//  BitQA
//
//  Created by Victor Ang on 13/05/2016.
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

void getUserInfo(){
    string currUsername = cgi("username");
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
    prep_stmt = con->prepareStatement("SELECT * FROM tblUser where username = ?");
    prep_stmt->setString(1, currUsername);
    res = prep_stmt->executeQuery();
    
    if(res->next()){            //get user info and populate
    curUser.setUsername(currUsername);
    curUser.setLocation(res->getString("location"));
    curUser.setDisplayName(res->getString("displayname"));
    curUser.setAge(res->getInt("age"));
    valid = true;
    }
}




int main(){
    
    
    BitQA::HTML::displayHeader();
    getUserInfo();
    
    if(valid){
    
    
    cout << "<div class=\"row\">" << endl;
    cout << " <div class=\"col-xs-4\">" << endl;
    cout << "<h2>" ;
    cout << curUser.getDisplayName();
    cout << "</h2>" << endl;
    cout << "<br><img src=\"/image/cute-tiger.jpg\" alt=\"profile pic\" style=\"width:304px;height:258px;\">" <<endl;
    cout << "</div>" << endl;
    cout << "<div class=\"col-xs-6\">" << endl;
    cout << "<dl class=\"dl-horizontal\" style=\"margin-top:20%;\">"<< endl;
    cout << "<dt>Username</dt>" << endl;
    cout << "<dd>" ;
    cout << curUser.getUsername();
    cout << "</dd>" <<endl;
    cout << "<dt>Email</dt>" << endl;
    cout << "<dd>";
    cout << curUser.getEmail();
    cout << "</dd>" << endl;
    cout << "<dt>Location</dt>" << endl;
    cout << "<dd>";
    cout << curUser.getLocation();
    cout << "</dd>" << endl;
    cout << "<dt>Age</dt>" << endl;
    cout << "<dd>";
    cout << curUser.getAge();
    cout << "</dd>" << endl;
    cout << "<dt>Tags of interest</dt>" << endl;
    cout << "<dd></dd>" << endl;
    cout << "<dt>Reputation point</dt>" << endl;
    cout << "<dd></dd>" << endl;
    cout << "<dt>Roles</dt>" << endl;
    cout << "<dd></dd>" << endl;
    cout << "</div>" << endl;
    cout << "</div>" << endl;
    cout << "</div>" << endl;
    }else{
        cout << "<h1> User not found </h1>" << endl;
    }
    BitQA::HTML::displayFooter();
    
    
    
    
}