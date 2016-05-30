/*
Author: Matthew Twose, mt156, 4510550
Date Modified: 29/05/2016
Contains the cpp unit test class for the user class
*/
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "User.h"
#include <string>

class testUser : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE (testUser);
	CPPUNIT_TEST ();
	CPPUNIT_TEST_SUITE_END ();
private:
	User user1;
public:
	void setUp();
	void tearDown();
protected:
	void testGetUsername();
	void testGetPassword();
	void testGetEmail();
	void testGetTag();
	void testGetLocation();
	void testGetDisplayName();
	void testGetAge();
};

#ifndef _USERTEST_H
#define _USERTEST_H
#endif /* _USERTEST_H */
