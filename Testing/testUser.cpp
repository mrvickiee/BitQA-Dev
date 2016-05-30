/*
Author: Matthew Twose, mt156, 4510550
Date Modified: 29/05/2016
Contains the cpp unit test class for the report class
*/
#include "testUser.h"
#include "User.h"

CPPUNIT_TEST_REGISTRATION (testUser);

void setUp(){}
void tearDown(){}

void testGetUsername(){
	user1.setUsername("test");
	CPPUNIT_ASSERT_EQUALS("test", user1.getUsername());
	user1.setUsername("username");
	CPPUNIT_ASSERT_EQUALS("username", user1.getUsername());
}

void testGetPassword(){
	user1.setPassword("test");
	CPPUNIT_ASSERT_EQUALS("test", user1.getPassword());
	user1.setPassword("password");
	CPPUNIT_ASSERT_EQUALS("password", user1.getPassword());
}

void testGetEmail(){
	user1.setEmail("test@email.com");
	CPPUNIT_ASSERT_EQUALS("test@email.com", user1.getEmail());
	user1.setEmail("email@email.com");
	CPPUNIT_ASSERT_EQUALS("email@email.com", user1.getEmail());
}

void testGetTag(){
	user1.setTag("c++, c");
	CPPUNIT_ASSERT_EQUALS("c++, c", user1.getTag());
	user1.setTag("php, xml, python");
	CPPUNIT_ASSERT_EQUALS("php, xml, python", user1.getTag());
}

void testGetLocation(){
	user1.setLocation("Australia");
	CPPUNIT_ASSERT_EQUALS("Australia", user1.getLocation());
	user1.setLocation("location");
	CPPUNIT_ASSERT_EQUALS("location", user1.getLocation());
}

void testGetDisplayName(){
	user1.setDisplayName("Randal Person");
	CPPUNIT_ASSERT_EQUALS("Randal Person", user1.getDisplayName());
	user1.setDisplayName("displayName");
	CPPUNIT_ASSERT_EQUALS("displayName", user1.getDisplayName());
}
void testGetAge(){
	user1.setAge(32);
	CPPUNIT_ASSERT_EQUALS(32, user1.getAge());
	user1.setAge(0);
	CPPUNIT_ASSERT_EQUALS(0, user1.getAge());
}
