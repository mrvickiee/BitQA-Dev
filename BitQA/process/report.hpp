#ifndef _REPORT
#define _REPORT

#include <iostream>
#include <vector>
#include "../includes/database.hpp"
using namespace std;

class Report
{
private:
	string userid;
public:
	Report();
	
	// Helpers
	void setUserId(string userId);
	bool loggedIn();

	//Home page reports
	void recQuestions();
	void topUsers();
	void featured();
	void topQuestions();
	//User page reports
	void activityGraph();
	void topTags();
	void topPostedQuestions();
	void topPostedAnswers();
	void postHistory();
	void allUsers();
};

#endif
