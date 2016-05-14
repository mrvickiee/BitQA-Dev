//
//  allquestions.cpp
//  BitQA
//
//  Created by Asjad Athick on 14/05/2016.
//  Copyright © 2016 CSCI222. All rights reserved.
//

#include <stdio.h>
#include "../includes/database.hpp"
#include "../includes/html.hpp"

using namespace cgicc;
using namespace std;

int main(){
	BitQA::HTML::displayHeader();
	
	Cgicc cgicc;
	
	try {
		
		
		
	} catch (sql::SQLException &e) {
		
		string error(e.what());
		
		BitQA::HTML::error("There was an error viewing your question",
						   "Please go <a href=\"/\">home</a><p>Details: " + error + "</p>"
						   );
		
	} catch (exception &e) {
		
		string error(e.what());
		
		BitQA::HTML::error("There was an error viewing your question",
						   "Please go <a href=\"/\">home</a><p>Details: " + error + "</p>"
						   );
		
	}
	
	BitQA::HTML::displayFooter();
	return 0;
}