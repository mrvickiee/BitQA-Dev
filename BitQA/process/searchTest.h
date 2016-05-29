
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "search.hpp"


class searchTest : public CppUnit::TestFixture
{

	private:
		MySearch testObj();
		MySearch testObjB();
	public:
		void setUp();
		void tearDown();
	protected:
		bool testGet();
		bool testSet();
};
