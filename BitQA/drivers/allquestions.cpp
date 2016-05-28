//
//  allquestions.cpp
//  BitQA
//
//  Created by Asjad Athick on 14/05/2016.
//  Copyright © 2016 CSCI222. All rights reserved.
//

#include <stdio.h>
#include <algorithm>
#include <regex>
#include "../includes/database.hpp"
#include "../includes/html.hpp"

using namespace cgicc;
using namespace std;

string removeMarkup(string input){
	string res = input;
	replace( res.begin(), res.end(), '<', ' ');
	replace( res.begin(), res.end(), '>', ' ');
	//string res = "<xmp>" + input + "</xmp>";
	//string res = "<b href='sss'>hello</b>";
	//res = regex_replace(res, regex(" *\\<[^>]*\\> *"), "");
	//res = regex_replace(res, regex("(<[a-zA-Z]*>)|(<\/[a-zA-Z]*>)"), "");
	
	return res;
}

int main(){
	
	Cgicc cgicc;
	
	BitQA::HTML::displayHeader("All Questions", cgicc);
	
	try {
		
		int acAnswersOnly = 1;
		int mostRep = 0;
		int mostVote = 0;
		
		CgiEnvironment environment = cgicc.getEnvironment();
		
		if (environment.getRequestMethod() == "POST") {
			//cout << "its a post" << endl;
			if (cgicc("mostvote") == "on"){
				mostVote = 1;
				//cout << "most vote on:" << endl;
			}
			
			if (cgicc("mostrep") == "on"){
				mostRep = 1;
				//cout << "most rep on:" << endl;
			}
			
			if (cgicc("withanswer") != "true"){
				acAnswersOnly = 0;
				//cout << "acans on:" << endl;
			}
		}
		
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
		
		int pageNum = 0;
		
		//get max page num
		
		
		int fromVal, toVal;
		if (cgicc("page") == ""){
			fromVal = 0;
			pageNum = 1;
		}
		else{
			fromVal = ((stoi(cgicc("page")) -1) * 100);
			pageNum = stoi(cgicc("page"));
		}
		
		
		if (fromVal < 0) {
			throw string("Page out of range");
		}
		
		toVal = fromVal + 100;
		
		prep_stmt = con->prepareStatement("CALL GetAllQuestions(?,?,?,?,?);");
		prep_stmt->setInt(1, fromVal);
		prep_stmt->setInt(2, toVal);
		prep_stmt->setInt(3, acAnswersOnly);
		prep_stmt->setInt(4, mostVote);
		prep_stmt->setInt(5, mostRep);
		res = prep_stmt->executeQuery();
		
		cout << "<h1>Showing all questions</h1>" << endl;
		cout << "<br><br>" << endl;
		
		//print filter div
		cout << "<div class=\"panel panel-default\">"
			<< "<div class=\"panel-heading\">"
			<< "<h3 class=\"panel-title\">Filter questions</h3></div><div class=\"panel-body\">"
			<< "<form method=\"POST\">"
			<< "<table style=\"padding: 10px;\">"
			<< "<col width = \"200\"><tr height=\"20px\">"
			<< "<td><b>Questions:</b></td>"
			<< "<td><b>Sort by:</b></td></tr>"
			<< "<tr height=\"50px\">"
			<< "<td><label class=\"checkbox-inline\"><input type=\"checkbox\" name=\"withanswer\" value=\"true\" checked>Answered</label></td>"
			<< "<td><label class=\"radio-inline\"><input type=\"radio\" name=\"mostvote\">Most voted</label>"
			<< "<label class=\"radio-inline\"><input type=\"radio\" name=\"mostrep\">Most reputed</label></td></tr>"
			<< "<tr height=\"20px\"><td><input class=\"btn btn-primary\" type=\"submit\" value=\"Refine\"/></td></tr></table></form></div></div><br><br>" << endl;
		
		
		//print results
		while (res->next()) {
			cout << "<div class=\"panel panel-default\"><div class=\"panel-body\">" << endl;
			cout << "<h4><a href='question.html?id=" << res->getString("id") <<  "'>" <<  res->getString("questionTitle") << endl;
			cout << "</a></h4>" << removeMarkup(res->getString("content").substr(0,100)) << (res->getString("content").length()>100? "..." : "");
			
			cout << "<div><br><span>&#128129;: <a href='profile.html?username=" << res->getString("username") << "'>" << res->getString("displayname") << "</a>&nbsp;</span><span>&#9202;: " << res->getString("utimestamp") <<"&nbsp;</span><span>&#128077;: " << res->getString("votes") <<"&nbsp;</span></div>" << endl;
			
			
			cout<< "</div></div>" << endl;
			
		}
		
		cout << "<br>" << endl;
		
		//pagination
		cout << "<nav>" <<
		"<ul class='pagination'>" <<
		"<li>" <<
		"<a href='allquestions.html?page=" << ((pageNum-1) < 1 ? 1 : pageNum-1) <<"'aria-label='Previous'>" <<
		"<span aria-hidden='true'>&laquo;</span>" <<
		"</a></li>" <<
		"<li><a href='allquestions.html?page=" << pageNum + 1 <<"' aria-label='Next'>" <<
		"<span aria-hidden='true'>&raquo;</span>" <<
		"</a>" <<
		"</li>" <<
		"</ul>" <<
		"</nav>"  << endl;
		
		
		delete prep_stmt;
		delete con;
		
		
	} catch (sql::SQLException &e) {
		
		string error(e.what());
		
		BitQA::HTML::error("There was an error with SQL",
						   "Please go <a href=\"/\">home</a><p>Details: " + error + "</p>"
						   );
		
	} catch (exception &e) {
		
		string error(e.what());
		
		BitQA::HTML::error("There was an error viewing questions",
						   "Please go <a href=\"/\">home</a><p>Details: " + error + "</p>"
						   );
		
	} catch (string e){
		BitQA::HTML::error("There was an error viewing questions",
						   "Please go <a href=\"/\">home</a><p></p>"
						   );
	}
	
	BitQA::HTML::displayFooter();
	return 0;
}
