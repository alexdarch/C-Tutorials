// Quiz4_FixedPoints.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cassert>
#include <iostream>
#include <cmath>
void testAddition();

class FixedPoint2
{
private:
	int16_t m_base;
	int8_t m_decimal;
	int m_sign(int x) const	{return (x > 0) ? 1 : ((x < 0) ? -1 : 0);}

public:
	FixedPoint2(int16_t base = 0, int8_t decimal = 0) : m_base{ base }, m_decimal{ decimal }
	{
		if (m_base < 0 || m_decimal < 0)	//If either, or both, of the non-fractional and fractional part of the number are negative, the number should be treated as negative.
		{
			m_base = -m_sign(m_base)*m_base;	//if one is -ve then it makes both negative. If both are -ve then it keeps both negative
			m_decimal = -m_sign(m_decimal)*m_decimal;
		}
	}
	FixedPoint2(double fraction = 0.0)
	{
		m_base = static_cast<int16_t>(fraction);	//rounds down because it just gets rid of the decimal bit
		m_decimal = static_cast<int8_t>(round((fraction - m_base) * 100));	//round() gives us the nearest integer, then static_cast drops the rest of the decimals (some doubles can have 5.00099 instead of 5, for example)
	}

	//returns a double, takes a FixedPoint2
	operator double() const	{	return m_base + static_cast<double>(m_decimal) / 100.0;	}
	
	bool operator==(const FixedPoint2 &a) { return (m_base == a.m_base && m_decimal == a.m_decimal); }
	friend FixedPoint2 operator+(const FixedPoint2 &a, const FixedPoint2 &b) {	return FixedPoint2(static_cast<double>(a) + static_cast<double>(b));	}
	FixedPoint2 operator-() const { return FixedPoint2( -m_base, -m_decimal ); }

	friend std::ostream& operator<<(std::ostream &out, FixedPoint2 &num);
	friend std::istream& operator>>(std::istream &in, FixedPoint2 &num);
};

int main()
{
	{	//4b
		FixedPoint2 a(34, 56);
		std::cout << a << '\n';

		FixedPoint2 b(-2, 8);
		std::cout << b << '\n';

		FixedPoint2 c(2, -8);
		std::cout << c << '\n';

		FixedPoint2 d(-2, -8);
		std::cout << d << '\n';

		FixedPoint2 e(0, -5);
		std::cout << e << '\n';

		std::cout << static_cast<double>(e) << '\n';
	}	//put in blocks to kill the local variables (objects)


	{	//4c
		FixedPoint2 a(0.01);
		std::cout << a << '\n';

		FixedPoint2 b(-0.01);
		std::cout << b << '\n';

		FixedPoint2 c(5.01); // stored as 5.0099999... so we'll need to round this
		std::cout << c << '\n';

		FixedPoint2 d(-5.01); // stored as -5.0099999... so we'll need to round this
		std::cout << d << '\n';
	}
	
	{
		testAddition();

		FixedPoint2 a(-0.48);
		std::cout << a << '\n';

		std::cout << -a << '\n';

		std::cout << "Enter a number: "; // enter 5.678
		std::cin >> a;

		std::cout << "You entered: " << a << '\n';
	}

	
    return 0;
}

void testAddition()
{
	// h/t to reader Sharjeel Safdar for this function
	std::cout << std::boolalpha;
	std::cout << (FixedPoint2(0.75) + FixedPoint2(1.23) == FixedPoint2(1.98)) << '\n'; // both positive, no decimal overflow
	std::cout << (FixedPoint2(0.75) + FixedPoint2(1.50) == FixedPoint2(2.25)) << '\n'; // both positive, with decimal overflow
	std::cout << (FixedPoint2(-0.75) + FixedPoint2(-1.23) == FixedPoint2(-1.98)) << '\n'; // both negative, no decimal overflow
	std::cout << (FixedPoint2(-0.75) + FixedPoint2(-1.50) == FixedPoint2(-2.25)) << '\n'; // both negative, with decimal overflow
	std::cout << (FixedPoint2(0.75) + FixedPoint2(-1.23) == FixedPoint2(-0.48)) << '\n'; // second negative, no decimal overflow
	std::cout << (FixedPoint2(0.75) + FixedPoint2(-1.50) == FixedPoint2(-0.75)) << '\n'; // second negative, possible decimal overflow
	std::cout << (FixedPoint2(-0.75) + FixedPoint2(1.23) == FixedPoint2(0.48)) << '\n'; // first negative, no decimal overflow
	std::cout << (FixedPoint2(-0.75) + FixedPoint2(1.50) == FixedPoint2(0.75)) << '\n'; // first negative, possible decimal overflow
}


std::ostream& operator<<(std::ostream &out, FixedPoint2 &num)
{
	//method 1 - no explicit casting (bad because its not really the number)
	//std::cout << num.m_base << "." << static_cast<int>(num.m_decimal) << "\n";

	//method two - effectively cast manually here
	//out << ( num.m_base + static_cast<double>(num.m_decimal)/100 );

	//method 3 - use an overloaded cast (good because reusable code)
	out << static_cast<double>(num);

	return out;
}

std::istream& operator>>(std::istream &in, FixedPoint2 &num)
{
	double d;
	in >> d;
	num = FixedPoint2(d);

	return in;
}
