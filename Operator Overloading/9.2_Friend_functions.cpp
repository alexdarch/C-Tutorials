// 9.2_Friend_functions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cassert>

class Fraction
{
private:
	int m_numerator;
	int m_denominator;

	static int gcd(int a, int b) {
		return (b == 0) ? (a > 0 ? a : -a) : gcd(b, a % b);
	}

public:
	Fraction(int num = 0, int denom = 1)
		: m_numerator{ num }, m_denominator{ denom }
	{
		assert(m_denominator != 0 && "The denominator is zero, this is not valid!");
		reduce();
	}

	void print() const
	{
		std::cout << m_numerator << "/" << m_denominator << "\n";
	}



	void reduce()
	{
		int divisor = Fraction::gcd(m_numerator, m_denominator);
		m_numerator /= divisor;
		m_denominator /= divisor;
		
	}

	friend Fraction operator*(const Fraction &a, const Fraction &b);
	friend Fraction operator*(const Fraction &a, int b);
	friend Fraction operator*(int a, const Fraction &b);


};

Fraction operator*(const Fraction &a, const Fraction &b)
{
	Fraction init = Fraction(a.m_numerator*b.m_numerator, a.m_denominator*b.m_denominator);
	return init;
}

Fraction operator*(const Fraction &a, int b)
{
	return Fraction(a.m_numerator*b, a.m_denominator);
}

Fraction operator*(int a, const Fraction &b)
{
	return b * a;		//this calls the overloaded function above
}






int main()
{
	Fraction f1(1, 4);
	f1.print();

	Fraction f2(4, 1);
	f2.print();

	Fraction f3 = f1 * f2;
	f3.print();

	Fraction f4 = f1 * 2;
	f4.print();

	Fraction f5 = 2 * f2;
	f5.print();

	Fraction f6 = Fraction(3, 2) * Fraction(2, 3) * Fraction(3, 4);
	f6.print();

	return 0;
}
