/**
 * \class Fraction
 *
 * \brief A simple fraction class to model fractions
 *
 * This class models fractions whose numerator and denominator are integers.
 * The code has been taken and modified from: 
 * http://en.cppreference.com/w/cpp/language/operators
 *
 * \author Carlos Villarraga
 *
 */

#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>

using namespace std;


/**
 * \class DivisionByZeroException
 *
 * \brief dummy zero exception class
 *
 */
class DivisionByZeroException {

};


class Fraction {

private:
	int n, d;
	int gcd(int a, int b);

public:
	/**
	 * \brief Constructor
	 * \param n the value of the numerator
	 * \param d the value of the denominator (default value is 1)
	 * \exception DivisionByZeroException is thrown if the value of the denominator is zero
	 *
	 * This constructor initilizes the value of the fraction. 
	 * The initialization value will be always reduced according to the greatest common divisor (gcd).
	 * The fraction with value zero is represented as: 0/1
	 */
	Fraction(int n, int d = 1) throw (DivisionByZeroException);
	/**
	 * Destructor
	 */
	virtual ~Fraction(){};
	/**
	 * \return the value of the numerator
	 */
	int num() const;
	/**
	 * \return the value of the denominator
	 */
	int den() const;
	/**
	 * Overloaded multiplication operator
	 */
	Fraction& operator *=(const Fraction& rhs);
	/**
	 * Overloaded multiplication operator
	 */
	friend Fraction operator *(const Fraction& lhs, const Fraction& rhs);
	/**
	 * Overloaded equality comparison
	 */
	bool operator==(const Fraction& rhs) const;
	/**
	 * Overloaded inequality comparison
	 */
	bool operator!=(const Fraction& rhs) const;
	/**
	 * Overloaded output stream operator
	 */
	friend ostream& operator<<(ostream& out, const Fraction& rhs);
};

#endif
