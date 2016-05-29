/*
Author: Matthew Twose, mt156, 4510550
Date Modified: 29/05/2016
Contains the cpp unit test class for the report class
*/
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Report.h"
#include <string>

class testReport : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE (testReport);
	CPPUNIT_TEST (testLoggedIn);
	CPPUNIT_TEST_SUITE_END ();
private:
	Report report1;
public:
	void setUp();
	void tearDown();
protected:
	void testLoggedIn();
};

#ifndef _REPORTTEST_H
#define _REPORTTEST_H
#endif /* _REPORTTEST_H */
