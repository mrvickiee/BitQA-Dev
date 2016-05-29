/*
Author: Matthew Twose, mt156, 4510550
Date Modified: 29/05/2016
Contains the cpp unit test class for the answer class
*/
#include "testAnswer.h"
#include "Answer.h"

CPPUNIT_TEST_REGISTRATION (testAnswer);

void testAnswer::setUp(){}
void testAnswer::tearDown(){}

void testAnswer::testGetAnswerID(){
	CPPUNIT_ASSERT_EQUAL(1, a1.getAnswerID());
	CPPUNIT_ASSERT_EQUAL(2, a2.getAnswerID());
	CPPUNIT_ASSERT_EQUAL(3, a3.getAnswerID());
}

void testAnswer::testGetUserID(){
	string result;
	result = a1.getUserID();

	CPPUNIT_ASSERT_EQUAL(result, a1.getUserID()); 
	result = a2.getUserID();

	CPPUNIT_ASSERT_EQUAL(result, a2.getUserID()); 
	result = a3.getUserID();

	CPPUNIT_ASSERT_EQUAL(result, a3.getUserID());
}

void testAnswer::testGetContentID(){
	int result;
	result = a1.getContentID();

	CPPUNIT_ASSERT_EQUAL(result, a1.getContentID()); 
	result = a2.getUserID();

	CPPUNIT_ASSERT_EQUAL(result, a2.getContentID());
	result = a3.getUserID();

	CPPUNIT_ASSERT_EQUAL(result, a3.getContentID()); 
}

void testAnswer::testIsAcceptedAnswer(){
	CPPUNIT_ASSERT(!a1.isAcceptedAnswer());
	CPPUNIT_ASSERT(!a2.isAcceptedAnswer());
	CPPUNIT_ASSERT(!a3.isAcceptedAnswer());
}
