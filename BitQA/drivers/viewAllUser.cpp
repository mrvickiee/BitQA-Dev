//
//  viewAllUser.cpp
//  BitQA
//
//  Created by Victor Ang on 29/05/2016.
//  Copyright © 2016 CSCI222. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include "../includes/html.hpp"
#include "../includes/database.hpp"
#include "../process/user.hpp"
#include "../process/report.hpp"
using namespace std;
using namespace cgicc;
Report report;
Cgicc cgi;
User admin;


CgiEnvironment environemnt = cgi.getEnvironment();

int main(){
	BitQA::HTML::displayHeader("User management", cgi);
	admin = User().getUserObj(BitQA::HTML::getUsername(cgi));
	
	if(BitQA::HTML::getLoggedInStatus(cgi) && admin.getReputation() >= User().checkUserRight("ISADMIN")){
		report.allUsers();
		cout << "<script>"
		<< "$('#allUserTable').DataTable({paging:false,"
		<< "searching:true,"
		<< "autowidth:false,"
		<< "paging:true,"
		<< "info:false}); </script>" << endl;
	
		BitQA::HTML::displayFooter();
	}else{
		cout << "<h1>You do not have sufficient reputation points to view this page. Go back!</h1>" << endl;
	}
}