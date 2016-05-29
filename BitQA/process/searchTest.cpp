#include "searchTest.h"

bool testEquality(string a, string b) {
	if(a == b) {
		return true;
	}else
	{
		return false;
	}
}


void searchTest::setUp() {
	//Put the test object back into its original state
	testObj.clear();
	testObjB.clear();
}


void searchTest::tearDown() {
	//Nothing to do here
}

bool searchTest::testSet() {
	
	//Both should return true
	string a = "Ben";
	testObj->set(a);
	CPPUNIT_ASSERT(testEquality((testObj.getSearchTerm()), a));
	
	string b = "Bill";
	testObjB.set(b);
	CPPUNIT_ASSERT(testEquality((testObjB.getSearchTerm()), b));

}


