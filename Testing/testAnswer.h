/*
Author: Matthew Twose, mt156, 4510550
Date Modified: 29/05/2016
Contains the cpp unit test class for the answer class
*/
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Answer.h"
#include <string>

class testAnswer : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE (testAnswer);
	CPPUNIT_TEST (testGetAnswerID);
	CPPUNIT_TEST (testGetUserID);
	CPPUNIT_TEST (testGetContentID);
	CPPUNIT_TEST (testIsAcceptedAnswer);
	CPPUNIT_TEST_SUITE_END ();
private:
	Answer a1(1);
	Answer a2(2);
	Answer a3(3);
public:
	void setUp();
	void tearDown();
protected:
	void testGetAnswerID();
	void testGetUserID();
	void testGetContentID();
	void testIsAcceptedAnswer();
};

#ifndef _ANSWERTEST_H
#define _ANSWERTEST_H
#endif /* _ANSWERTEST_H */
