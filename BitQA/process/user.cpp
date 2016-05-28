//
//  user.cpp
//  BitQA
//
//  Created by Victor Ang on 12/05/2016.
//  Copyright © 2016 CSCI222. All rights reserved.
//
#include "../includes/database.hpp"
#include "user.hpp"
#include <ctime>
#include <string>
#include <algorithm>

User::User(){
}

User::User(string username, string password, string email, string tag, int age, string location, string displayName ){
    this->username = username;
    this->password = password;
    this->email = email;
    tagInterest = tag;
    this->age = age;
    creationDate = time(0);
    id = generateID();
    this->location = location;
    this->displayName = displayName;
    reputation = 0;
}

string User::getUsername(){
    return username;
}

User User::getUserObj(string currUsername){

	User curUser;

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
		curUser.setLocation(res->getString("location"));
		curUser.setDisplayName(res->getString("displayname"));
		curUser.setAge(res->getInt("age"));
		curUser.setEmail(res->getString("email"));
		curUser.setTag(res->getString("UserTag"));
		curUser.setReputation(res->getInt("Reputation"));
		curUser.setID(res->getInt("id"));
		curUser.setPassword(res->getString("passhash"));

	}
	delete prep_stmt;
	delete con;

	return curUser;
}


int User::checkUserRight(string rights){
    
    
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
        prep_stmt = con->prepareStatement("SELECT * FROM tblAccessRights where title = ?");
        prep_stmt->setString(1, rights);
        
        
        res = prep_stmt->executeQuery();
        
        res->next();
        
        int reputation = res->getInt("points");
        
        return reputation;
}








string User::getPassword(){
    return password;
}

string User::getEmail(){
    return email;
}

string User::getTag(){
    return tagInterest;
}

string User::getLocation(){
    return location;
}

string User::getDisplayName(){
    return displayName;
}

int User::getAge(){
    return age;
}

string User::getDate(){
    struct tm *timeinfo;
    char buffer[100];
    time(&creationDate);
    timeinfo = localtime(&creationDate);
    strftime(buffer,100,"%Y-%m-%d %I:%M:%S",timeinfo);
    string str(buffer);
    
    
    return buffer;
}

int User::generateID(){
    int id = 0;
    
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    
    
    driver = get_driver_instance();
    con = driver->connect(BitQA::Database::HOST,
                          BitQA::Database::USERNAME,
                          BitQA::Database::PASSWORD
                          );
    
    con->setSchema(BitQA::Database::SCHEMA);
    
    stmt = con->createStatement();
    
    res = stmt->executeQuery("Select id FROM tblUser");
    
    while (res->next()){
        int tmpID = res->getInt("id");
        if(tmpID > id){
            id = tmpID;
        }
    }
    
    id += 1;
    
    
    return id;
}

int User::getID(){
    return id;
}

void User::setUsername(string username){
    this->username = username;
}

void User::setAge(int age){
    this->age = age;
}

void User::setLocation(string location){
    this->location = location;
}

void User::setDisplayName(string displayName){
    this->displayName = displayName;
}

void User::setEmail(string email){
    this->email = email;
}

void User::setID(int id){
    this->id = id;
}

void User::setTag(string tag){
    this->tagInterest = tag;
}


void User::setReputation(int point){
    reputation = point;
}

int User::getReputation(){
    return reputation;
}

void User::setPassword(string pass){
	this->password = pass;
}

