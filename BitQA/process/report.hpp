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
//private:
	//int userId
public:
	Report();
	//Report(int userid);
	//void setUserId(int userid);
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
