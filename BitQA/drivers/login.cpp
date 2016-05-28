//
//  login.cpp
//  BitQA
//
//  Created by Victor Ang on 12/05/2016.
//  Copyright © 2016 CSCI222. All rights reserved.
//

#include <stdio.h>
#include "../process/user.hpp"
#include "../includes/html.hpp"
#include "../includes/database.hpp"
#include "../includes/md5.hpp"
#include <cgicc/HTTPCookie.h>
#include <string>
using namespace cgicc;
using namespace std;
bool success = true;
string response = "";
string dbusername,dbpassword, dbdisplayName;

bool verifyUser(string username, string password){
    
    
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
    prep_stmt = con->prepareStatement("SELECT * FROM tblUser where username = ? AND deleted = 0");
    prep_stmt->setString(1, username);
    res = prep_stmt->executeQuery();
    
    if(res->rowsCount() == 1){
        res->next();
        dbusername = res->getString("username");
       
        dbpassword = res->getString("passhash");
       
        dbdisplayName = res->getString("displayname");
        
        
        
       
        if(dbpassword == md5(password)){
            return true;
            
        }else{
            response = "Incorrect password or username!<br>";
            return false;
        }
        
    }else{
        response += "User does not exists!<br>";
        return false;
    }
}


int main(){
    
    cgicc::Cgicc cgi;
    
    string username,password;
    
    auto error = false;
    
    CgiEnvironment environment = cgi.getEnvironment();
    
    if(environment.getRequestMethod() == "POST"){
        try{
            username = cgi("username");
            password = cgi("password");
            
            if(username.size() > 0 && password.size() > 0){
                bool valid = verifyUser(username, password);
                
                if(valid){
                    cout << "Set-Cookie:username=" << dbusername <<";"<< endl;
                    cout << "Set-Cookie:displayname=" << dbdisplayName<<";" << endl;

                    cout << cgicc::HTTPRedirectHeader(BitQA::HTML::HOST) << endl;
                }else{
                    error = true;
                }
            }else{
                error = true;
                response += "Empty field are not allowed!";
            }
        }catch(exception &e){
            error = true;
            response += "Error logging in: " + string(e.what()) + "<br>";
        }
        
        
    }
    
    {
		
		BitQA::HTML::displayHeader("Login", cgi);
        
        User usr;
        string date = usr.getDate();
		
		cout << "<h1>Login</h1><br>" << endl;
        
        cout << "<form data-ajax=\"false\" method=\"post\">"<<endl;
        
        cout << "<div class=\"form-group\">" << endl;
        
        cout << "<label for= \"Username\"> Username </label>" << endl;
        cout << "<input type=\"text\" class=\"form-control\" id=\"userName\" name=\"userName\" placeholder = \"Enter Username\"> " << endl;
        
        cout << "</div>" << endl;
        
        cout << "<div class=\"form-group\">" << endl;
        
        cout << "<label for= \"password\"> Password </label>" << endl;
        cout << "<input type=\"password\" class=\"form-control\" id=\"password\" name=\"password\" placeholder = \"Enter password\">" << endl;
        
        cout << "</div>" << endl;
        
        cout << "<button type=\"submit\" class=\"btn btn-default\"> Submit </button> " <<endl;
        cout << "<button type=\"reset\" class=\"btn btn-danger\">Reset </button>" <<endl;
        
        
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