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
	Report report;
    
    BitQA::HTML::displayHeader();

	cout << "<h1>Homepage Reports</h1>";
	cout << "<h3>Reccomended Questions<br></h3>";
	report.recQuestions();
	cout << "<h3>Top 10 Users<br></h3>";
	report.topUsers();
	cout << "<h3>Recent Featured Questions<br></h3>";
	report.featured();
	cout << "<h3>Top 10 Most Upvoted Questions<br></h3>";
	report.topQuestions();

	cout << "<h1><br>User Profile Reports<h1>";
	cout << "<h3>Activity Graph<br></h3>";
	report.activityGraph();
	cout << "<h3>Top 5 Tags<br></h3>";
	report.topTags();
	cout << "<h3>Top 5 Posted Answers<br></h3>";
	report.topPostedAnswers();
	cout << "<h3>Top 5 Posted Questions<br></h3>";
	report.topPostedQuestions();
	cout << "<h3>Posting History<br></h3>";
	report.postHistory();

    BitQA::HTML::displayFooter();
    
    return 0;
}
