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
#include "../includes/md5.hpp"
#include "../process/report.hpp"
using namespace std;
using namespace cgicc;

User curUser;
cgicc::Cgicc cgi;
CgiEnvironment environment = cgi.getEnvironment();
bool valid = false;
Report report;

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
        valid = true;
		report.setUserId(curUser.getUsername());
    }
    
    delete prep_stmt;
    delete con;
}




int main(){
    
    
    BitQA::HTML::displayHeader("Profile", cgi);
    getUserInfo();
    
    if(valid){
    
    
    cout << "<div class=\"row\" style=\"margin-left:10%\">" << endl;	//user details
    cout << " <div class=\"col-xs-4\">" << endl;
    cout << "<h2>" ;
    cout << curUser.getDisplayName();
    cout << "</h2>" << endl;
    cout << "<br><img src=\"";
		
	cout << "https://2.gravatar.com/avatar/" << md5(curUser.getEmail()) << "?s=512";
		
	cout << "\" alt=\"profile pic\" style=\"width:300px;\">" <<endl;
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
    cout << "<dd>";
    cout << curUser.getTag();
    cout <<"</dd>" << endl;
    cout << "<dt>Reputation point</dt>" << endl;
    cout << "<dd>";
    cout << curUser.getReputation();
    cout << "</dd>" << endl;
    cout << "<dt>Roles</dt>" << endl;
    cout << "<dd></dd>" << endl;
    cout << "</div>" << endl;
    cout << "</div>" << endl;
    cout << "</div>" << endl;
		
		
	
	cout << "<div class=\"row\" style=\"margin-top:5%\">"<< endl;
	
	cout << "<div class=\"col-xs-5\" style=\"margin-left:9%;\" >"<< endl;
	cout << "<h3>Top most upvoted question</h3>";
	report.topPostedQuestions();
	cout << "</div>";
	
	cout << "<div class=\"col-xs-5\" >"<< endl;
	cout << "<h3>Top most upvoted Answer</h3>";
	report.topPostedAnswers();
	cout << "</div>";
	cout << "</div>";


	cout << "<div class=\"row\" style=\"margin-top:5%\">"<< endl;

	cout << "<div class=\"col-xs-10\" style=\"margin-left:9%\" >"<< endl;
	cout << "<h3> Posting History </h3>"<< endl;
	report.postHistory();
	cout << "</div>"<< endl;
		
	cout << "</div>";
	
	cout << "<div class=\"row\" style=\"margin-top:5%\">"<< endl;		//user report
	cout << "<div class=\"col-xs-5\" style=\"margin-left:9%;\">"<< endl;
	cout << "<h3>Top tags</h3>"<< endl;
	report.topTags();
	
	cout << "</div>"<< endl;
	
	cout << "<div class=\"col-xs-5\" >"<< endl;
	
	cout << "<h3>Activity Graph</h3>";
	report.activityGraph();
	cout << "</div>";
	
	cout << "</div>"<< endl;

		
    }else{
        cout << "<h1> User not found </h1>" << endl;
    }
	
	
	cout << "<script>"
	<< "$('#topQuesTbl').DataTable({paging:false,"
	<< "searching:false,"
	<< "autowidth:false,"
	<< "info:false});"
	
	<< "$('#topAnsTbl').DataTable({paging:false,"
	<< "searching:false,"
	<< "autowidth:false,"
	<< "info:false});"
	
	<< "$('#topPostingHistoryTbl').DataTable({paging:false,"
	<< "searching:true,"
	<< "autowidth:false,"
	<< "info:false});"

	<< "$('#topTagTbl').DataTable({paging:false,"
	<< "searching:false,"
	<< "autowidth:false,"
	<< "info:false});"
	
	<< "</script>"
	<< endl;
    BitQA::HTML::displayFooter();
    
    
    
    
}