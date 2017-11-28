/*
 * Tests are run in the main routine.
 * Common CppUnit usage which can be easily adapted to other cases
 * Read explanatory comments!
 */

#include <cppunit/CompilerOutputter.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

using namespace std;
using namespace CppUnit;

int main(void)
{
	//CppUnit: - create TestSuite by registry
	//         - TestFactoryRegistry contains all the test suites registered 
	//           using the macro CPPUNIT_TEST_SUITE_REGISTRATION()
	Test *suite = TestFactoryRegistry::getRegistry().makeTest();

	//CppUnit: - create TestRunner
	//         - The TestRunner will run all the test in the suite
	TextTestRunner testrunner;

	//CppUnit: - insert test-suite into runner	
	testrunner.addTest(suite);

	//CppUnit: - format output in compiler style
  	testrunner.setOutputter( new CompilerOutputter( &testrunner.result(), cerr ) );

	//CppUnit: - runs alls test and return 0 if test were successful
	return testrunner.run() ? 0 : 1;
}
