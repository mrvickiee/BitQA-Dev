//
//  user.hpp
//  BitQA
//
//  Created by Victor Ang on 12/05/2016.
//  Copyright © 2016 CSCI222. All rights reserved.
//

#ifndef user_hpp
#define user_hpp

#include <stdio.h>
#include <string>

using std::string;

class User{
private:
    int id;
    int age;
    string location;
    string username;
    string displayName;
    string password;
    string email;
    int reputation;
    string tagInterest;
    time_t creationDate;
    
public:
    User();
    User(string,string,string,string, int, string, string);
    string getUsername();
    string getPassword();
    string getEmail();
    string getTag();
    int getID();
    void setID(int);
    int generateID();
    string getLocation();
    string getDisplayName();
    int getAge();
    string getDate();
    void setUsername(string);
    void setAge(int);
    void setLocation(string);
    void setDisplayName(string);
    void setEmail(string);
    void setTag(string);
    void setReputation(int);
    int getReputation();
    
    
};


#endif /* user_hpp */
