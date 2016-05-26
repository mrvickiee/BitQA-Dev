/*
Matthew Twose, mt156, 4510550
BitQA
Page for testing homepage report functions
*/
#include "../includes/html.hpp"
#include "../includes/database.hpp"
#include "../process/report.hpp"

using namespace cgicc;
using namespace std;

int main()
{
	
	try {
		
		Cgicc cgicc;
		BitQA::HTML::displayHeader("Reports", cgicc);
		
		CgiEnvironment environment = cgicc.getEnvironment();
		const_cookie_iterator cci;
		
		string userName = "";
		string displayName = "";
		
		for (cci = environment.getCookieList().begin();
			 cci != environment.getCookieList().end();
			 cci++) {
			if (cci->getName() == "username") {
				userName = cci->getValue();
			} else if (cci->getName() == "displayname") {
				displayName = cci->getValue();
			}
		}
		
		Report report;
		
		if (userName.length() > 0) {
			report.setUserId(userName);
		}
		
		cout << "<h1>Reporting</h1>";
		
		cout << "<br><hr><br>";
		cout << "<h3>Recommended Questions</h3><br>";
		report.recQuestions();
		 
		cout << "<br><hr><br>";
		cout << "<h3>Top 10 Users</h3><br>";
		report.topUsers();
		 
		cout << "<br><hr><br>";
		cout << "<h3>Recent Featured Questions</h3><br>";
		report.featured();

		cout << "<br><hr><br>";
		cout << "<h3>Top 10 Most Upvoted Questions</h3><br>";
		report.topQuestions();
		
		cout << "<br><hr><h1>User Profile Reports<h1>";
		
		cout << "<br>";
		cout << "<h3>Activity Graph</h3><br>";
		report.activityGraph();
		
		cout << "<br><hr><br>";
		cout << "<h3>Top 5 Tags</h3><br>";
		report.topTags();
		
		cout << "<br><hr><br>";
		cout << "<h3>Posting History</h3><br>";
		report.postHistory();
		
		/*
		 cout << "<h3>Top 5 Posted Answers<br></h3>";
		 report.topPostedAnswers();
		 cout << "<h3>Top 5 Posted Questions<br></h3>";
		 report.topPostedQuestions();
		 */
		
	} catch (sql::SQLException &e) {
		
		string error(e.what());
		
		BitQA::HTML::error("There was an error generating the report",
						   "Please go <a href=\"/\">home</a><p>Details: " + error + "</p>"
						   );
		
	} catch (exception &e) {
		
		string error(e.what());
		
		BitQA::HTML::error("There was an error generating the report",
						   "Please go <a href=\"/\">home</a><p>Details: " + error + "</p>"
						   );
		
	}

    BitQA::HTML::displayFooter();
    
    return 0;
}
