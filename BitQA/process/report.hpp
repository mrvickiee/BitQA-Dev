/*
Matthew Twose, mt156, 4510550
BitQA
report functionality declaration
*/

#ifndef _REPORT
#define _REPORT

#include<iostream>
#include "../includes/database.hpp"
using namespace std;

class Report{
private:
	string userid;
public:
	Report();
	Report(string userId);
	void setUserId(string userId);

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
};

#endif
