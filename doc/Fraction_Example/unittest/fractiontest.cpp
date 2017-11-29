#include "FractionTest.hpp"

//CppUnit: register suite into the TestFactoryRegistry 
CPPUNIT_TEST_SUITE_REGISTRATION(FractionTest);

//CppUnit: override setUp() to initialize the variables
void FractionTest::setUp(void) {
	// initialize objects
	p_f_0_1 = new Fraction(0, 1);
	p_f_0_6 = new Fraction(0, 6);
	p_f_2_3 = new Fraction(2, 3);
	p_f_3_2 = new Fraction(3, 2);
	p_f_12_8 = new Fraction(12, 8);
	p_f_5_2 = new Fraction(5, 2);
	p_f_m5_m2 = new Fraction(-5, -2);
	p_f_m5_2 = new Fraction(-5, 2);
	p_f_5_m2 = new Fraction(5, -2);
	p_f_1_1 = new Fraction(1, 1);
}

//CppUnit: override tearDown() to release any permanent resources 
//         you allocated in setUp()
void FractionTest::tearDown(void) {
	// delete objects
	delete p_f_0_1;
	delete p_f_0_6;
	delete p_f_2_3;
	delete p_f_3_2;
	delete p_f_12_8;
	delete p_f_5_2;
	delete p_f_m5_m2;
	delete p_f_m5_2;
	delete p_f_5_m2;
	delete p_f_1_1;
}

/// Method for Unit Test: checks the constructor
void FractionTest::constructorTest(void) {
	Fraction frc1(-11, 12); // correct data member initialization
	CPPUNIT_ASSERT_EQUAL(frc1.num(), -11); // numerator
	CPPUNIT_ASSERT_EQUAL(frc1.den(), 12);  // denominator
	Fraction frc2(0, 8); // correct data member initialization (zero = 0/1)
	CPPUNIT_ASSERT_EQUAL(frc2.num(), 0); // numerator
	CPPUNIT_ASSERT_EQUAL(frc2.den(), 1); // denominator
	CPPUNIT_ASSERT_EQUAL(Fraction(12, 4), Fraction(3));	// correct reduction
	CPPUNIT_ASSERT_THROW(Fraction(9, 0), DivisionByZeroException); // division-by-zero exception
}

/// Method for Unit Test: checks the equality operator
void FractionTest::eqTest(void) {
	CPPUNIT_ASSERT(*p_f_0_1 == *p_f_0_6); // unique zero representation
	CPPUNIT_ASSERT(*p_f_3_2 == *p_f_12_8);  // unique representation after reduction
	CPPUNIT_ASSERT(*p_f_5_2 == *p_f_m5_m2); // sign rule
	CPPUNIT_ASSERT(*p_f_m5_2 == *p_f_5_m2); // sign rule
}

/// Method for Unit Test: checks the inequality operator
void FractionTest::neqTest(void) {
	CPPUNIT_ASSERT(*p_f_m5_m2 != *p_f_5_m2); // sign rule
	CPPUNIT_ASSERT(*p_f_m5_m2 != *p_f_m5_2); // sign rule
	CPPUNIT_ASSERT(*p_f_5_m2 != *p_f_5_2); // sign rule
	CPPUNIT_ASSERT(*p_f_0_1 != *p_f_2_3); // comparison with zero
}

/// Method for Unit Test: checks the multiplication operator
void FractionTest::multTest(void) {
	CPPUNIT_ASSERT_EQUAL(*p_f_m5_m2 * *p_f_3_2, *p_f_3_2 * *p_f_m5_m2); // commutative property
	CPPUNIT_ASSERT_EQUAL(*p_f_1_1 * *p_f_2_3, *p_f_2_3); // identity element
	CPPUNIT_ASSERT_EQUAL(*p_f_0_1 * *p_f_2_3, *p_f_0_1); // property of zero
	CPPUNIT_ASSERT_EQUAL(*p_f_2_3 * *p_f_3_2, Fraction(1, 1)); // inverse element
}
