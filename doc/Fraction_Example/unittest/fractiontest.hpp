/**
 * \class FractionTest
 *
 * \brief Tests the fraction class
 *
 * Fixture class containing the Unit Tests used to test the Fraction class.
 * The test framework CppUnit is used.
 * This class inherits from TestFixture base class defined in the test framework.
 * 
 * Read explanatory comments in the code.
 * 
 * For more details see: http://cppunit.sourceforge.net/doc/cvs/cppunit_cookbook.html
 *
 * \author Carlos Villarraga
 *
 */
#ifndef FRACTIONTEST_HPP
#define FRACTIONTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../Fraction.hpp"

using namespace std;
using namespace CppUnit;


class FractionTest : public TestFixture
{
	//CppUnit: declare the suite, passing the class name to the macro
	CPPUNIT_TEST_SUITE(FractionTest);
	//CppUnit: declare each test case of the fixture in the suite passing the method name
	CPPUNIT_TEST(constructorTest);
	CPPUNIT_TEST(eqTest);
	CPPUNIT_TEST(neqTest);
	CPPUNIT_TEST(multTest);
	//CppUnit: end the suite declaration
	CPPUNIT_TEST_SUITE_END ();

public:
	//CppUnit: methods from the base class overridden in this class
	void setUp(void);
	void tearDown(void);
	// Methods with unit test
	void constructorTest(void);
	void eqTest(void);
	void neqTest(void);
	void multTest(void);

private:

	//CppUnit: a fixture is a known set of objects (variables) that serves as a base for a set of test cases. 
	//         Note that the same objects will be used in different test methods.
	//         If the same objects are not used in different methods then no fixture is required
	//         and the methods "setUp" and "tearDown" do not need to be overridden

	// CppUnit: add member variables for each part of the fixture
	Fraction* p_f_0_1;
	Fraction* p_f_0_6;
	Fraction* p_f_2_3;
	Fraction* p_f_3_2;
	Fraction* p_f_12_8;
	Fraction* p_f_5_2;
	Fraction* p_f_m5_m2;
	Fraction* p_f_m5_2;
	Fraction* p_f_5_m2;
	Fraction* p_f_1_1;
};

#endif
