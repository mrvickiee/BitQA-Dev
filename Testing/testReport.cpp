/*
Author: Matthew Twose, mt156, 4510550
Date Modified: 29/05/2016
Contains the cpp unit test class for the report class
*/
#include "testReport.h"
#include "Report.h"

CPPUNIT_TEST_REGISTRATION (testReport);

void testReport::setUp(){}
void testReport::tearDown(){}

void testReport::testLoggedIn(){
	CPPUNIT_ASSERT(!report1.loggedIn);
	report.setUserId("test");
	CPPUNIT_ASSERT(report1.loggedIn);
}
