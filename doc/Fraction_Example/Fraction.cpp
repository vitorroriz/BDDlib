/**
 * \brief ‫Implements methods of the fraction class
 *
 * \author Carlos Villarraga
 *
 */

#include "Fraction.hpp" 

Fraction::Fraction(int n, int d) throw (DivisionByZeroException) :
		n(n / gcd(n, d)), d(d / gcd(n, d)) {
	if (d == 0)
		throw DivisionByZeroException();
}

/**
 * Computes the greatest common divisor.
 * Thiss method is used to reduce the fractions.
 */
int Fraction::gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

Fraction& Fraction::operator *=(const Fraction& rhs) {
	int new_n = n * rhs.n / gcd(n * rhs.n, d * rhs.d);
	d = d * rhs.d / gcd(n * rhs.n, d * rhs.d);
	n = new_n;
	return *this;
}

int Fraction::num() const {
	return n;
}

int Fraction::den() const {
	return d;
}

Fraction operator *(const Fraction& lhs, const Fraction& rhs) {
	Fraction frc(lhs.num(), lhs.den());
	return frc *= rhs;
}

bool Fraction::operator ==(const Fraction& rhs) const {
	return this->num() == rhs.num() && this->den() == rhs.den();
}

bool Fraction::operator !=(const Fraction& rhs) const {
	return !(*this == rhs);
}

ostream& operator <<(ostream& out, const Fraction& rhs) {
	return out << rhs.num() << "/" << rhs.den();
}

