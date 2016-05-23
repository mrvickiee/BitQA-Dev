//
//  signup.cpp
//  BitQA
//
//  Created by Victor Ang on 12/05/2016.
//  Copyright © 2016 CSCI222. All rights reserved.
//

#include "../process/user.hpp"
#include "../includes/html.hpp"
#include "../includes/database.hpp"
#include <stdio.h>
#include "../includes/md5.hpp"

using namespace std;
using namespace cgicc;


void addUser(User user){
    sql::Driver *driver;
    sql::Connection *con;
    sql::PreparedStatement *prep_stmt, *prep_stmt2, *prep_stmt3;
    
    driver = get_driver_instance();
    con = driver->connect(BitQA::Database::HOST,
                          BitQA::Database::USERNAME,
                          BitQA::Database::PASSWORD
                          );
    
    con->setSchema(BitQA::Database::SCHEMA);
    
    prep_stmt = con->prepareStatement("Insert into tblUser values(?,?,?,?,NOW(),?,?,?,0)");
    
    prep_stmt->setInt(1,user.getID());
    prep_stmt->setString(2,user.getUsername());
    prep_stmt->setString(3,user.getPassword());
    prep_stmt->setString(4,user.getDisplayName());
    prep_stmt->setInt(5, user.getAge());
    prep_stmt->setString(6, user.getLocation());
    prep_stmt->setString(7, user.getEmail());
    
    prep_stmt->executeUpdate();
    
    prep_stmt2 = con->prepareStatement("Insert into tblUserTags values(?,?,0)");
    prep_stmt2->setInt(1, user.getID());
    prep_stmt2->setString(2, user.getTag());
    prep_stmt2->executeUpdate();
    
    prep_stmt3 = con->prepareStatement("Insert into tblUserReputation values(?,0,0)");
    prep_stmt3->setInt(1, user.getID());
    prep_stmt3->executeUpdate();
    
    delete prep_stmt,prep_stmt2,prep_stmt3;
    delete con;
}

bool checkUsername(string username){
    sql::Driver *driver;
    sql::Connection *con;
    sql::PreparedStatement *prep_stmt;
    sql::ResultSet *res;
    bool unique = false;
    
    if(!isspace(username.at(0))){
        driver = get_driver_instance();
        con = driver->connect(BitQA::Database::HOST,
                              BitQA::Database::USERNAME,
                              BitQA::Database::PASSWORD
                              );
        
        con->setSchema(BitQA::Database::SCHEMA);
        prep_stmt = con->prepareStatement("SELECT * FROM tblUser where username = ?");
        prep_stmt->setString(1, username);
        
        
        res = prep_stmt->executeQuery();
       
        if(res->rowsCount() == 0){
            unique = true;
        }
    }
    
    return unique;
}





int main(){
    
    cgicc::Cgicc cgi;
	BitQA::HTML::displayHeader("Signup", cgi);
    
    string response,username,password, confirmPassword, email, tags,location, displayName, ageString;
    bool success = true;
    int age;
    auto error = false;
    
    CgiEnvironment environment = cgi.getEnvironment();
    
    if(environment.getRequestMethod() == "POST"){
        try{
            username = cgi("username");
            password = cgi("password");
            confirmPassword = cgi("confirmPassword");
            email = cgi("email");
            tags = cgi("tag");
            ageString =  cgi("age");
            location = cgi("location");
            displayName = cgi("displayName");
            //checking
            
            if(password != confirmPassword || password == ""){
                success = false;
                response += "<br>Password do not match!";
            }
            
            if(!checkUsername(username)){
                success = false;
                response += "<br>Username is not unique!";
            }else{
                bool gotSpace = false;
                
                for(int i = 0 ; i< username.size() ; i++){
                    if(isspace(username.at(i))){
                        gotSpace = true;
                        break;
                    }
                }
                
                if(gotSpace){
                    success = false;
                    response += "<br>Username must not contain space!";
                }
            }
            
            if(displayName.size() == 0 || isspace(displayName.at(0))){
                success = false;
                response += "<br>Please enter preferred display name!";
            }
            
            if(email.size() == 0  || isspace(email.at(0))){
                success = false;
                response += "<br>Please enter email address!";
            }
            
            
            for(int i =0; i< ageString.size();i++){
                if(!isdigit(ageString[i])){
                    success = false;
                    response += "<br>Age must be numerical!";
                    break;
                }
            }
            
            if(success){
                age = atoi(ageString.c_str());
                User newUser = User(username, md5(password), email, tags, age, location,displayName);
                addUser(newUser);
                cout << "<script>location.href=\"/login.html\";</script>" << endl;
            }else{
                error = true;
                
            }
       
        
        
        
        }catch(exception &e){
            error = true;
            response += "Error creating account: " + string(e.what()) + "<br>";
        }
    
        
        
    }
    
    {
        User usr;
        string date = usr.getDate();
		
    cout << "<h1>Sign up to BitQA</h2><br>" << endl;
        
    cout << "<form data-ajax=\"false\" method=\"post\">"<<endl;
        
    cout << "<div class=\"form-group\">" << endl;
    
    cout << "<label for= \"displayName\"> Display name </label>" << endl;
    cout << "<input type=\"text\" class=\"form-control\" id=\"displayName\" name=\"displayName\" placeholder = \"Enter display name\"> " << endl;
    
    cout << "</div>" << endl;
        
    cout << "<div class=\"form-group\">" << endl;

    cout << "<label for= \"username1\"> Username </label>" << endl;
    cout << "<input type=\"text\" class=\"form-control\" id=\"username1\" name=\"username\" placeholder = \"Enter username\">" << endl;
    
    cout << "</div>" << endl;
    
    cout << "<div class=\"form-group\">" << endl;
    
    cout << "<label for= \"password\"> Password </label>" << endl;
    cout << "<input type=\"password\" class=\"form-control\" id=\"password\" name=\"password\" placeholder = \"Enter password\"> " << endl;
    
    cout << "</div>" << endl;
    
    cout << "<div class=\"form-group\">" << endl;
    
    cout << "<label for= \"confirmPassword\"> Confirm Password </label>" << endl;
    cout << "<input type=\"password\" class=\"form-control\" id=\"confirmPassword\" name=\"confirmPassword\" placeholder = \"Retype password\"> " << endl;
    
    cout << "</div>" << endl;
    
    cout << "<div class=\"form-group\">" << endl;
    
    cout << "<label for= \"email\"> Email </label>" << endl;
    cout << "<input type=\"email\" class=\"form-control\" id=\"email\" name=\"email\" placeholder = \"Enter email\"> " << endl;
    
    cout << "</div>" << endl;
    
    cout << "<div class=\"form-group\">" << endl;
    
    cout << "<label for= \"tag\"> Tags of interest </label>" << endl;
    cout << "<input type=\"text\" class=\"form-control\" id=\"tag\" name=\"tag\" placeholder = \"Enter tag (seperate with ,)\"> " << endl;
    
    cout << "</div>" << endl;
        
    cout << "<div class=\"form-group\">" << endl;
    
    cout << "<label for= \"location\"> Location </label>" << endl;
    cout << "<input type=\"text\" class=\"form-control\" id=\"location\" name=\"location\" placeholder = \"Enter location\"> " << endl;
    
    cout << "</div>" << endl;
        
    cout << "<div class=\"form-group\">" << endl;
    
    cout << "<label for= \"age\"> Age </label>" << endl;
    cout << "<input type=\"number\" min=\"1\" max = \"99\" class=\"form-control\" id=\"age\" name=\"age\" placeholder = \"Enter age\"> " << endl;
    
    cout << "</div>" << endl;
        
    cout << "<button type=\"submit\" class=\"btn btn-default\"> Submit </button> " <<endl;
    
    cout << "</div>" << endl;
    cout << "</form>" << endl;
        
        
        if (environment.getRequestMethod() == "POST") {
            if (error) {
                cout << "<div class=\"alert alert-danger\">" << endl;
                cout << "<strong>Error!</strong> " << response << endl;
                cout << "</div>";
            } else {
                cout << "<div class=\"alert alert-success\">" << endl;
                cout << "<strong>Success!</strong> Added to Database." << endl;
                cout << "</div>";
            }
        }
        
        BitQA::HTML::displayFooter();
    
    
    }
}