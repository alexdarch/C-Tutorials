// 9.3_IO_overloading.cpp : Defines the entry point for the console application.
//

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

	friend std::ostream& operator<<(std::ostream& out, const Fraction &f);
	friend std::istream& operator>>(std::istream& in, const Fraction &f);



};


std::istream& operator>>(std::istream& in, const Fraction &f)
{
	char c;
	in >> f.m_numerator;
	in >> c;		//ignore "/"
	in >> f.m_denominator;

	return in;
}


std::ostream& operator<<(std::ostream& out, const Fraction &f)
{
	out << f.m_numerator << "/" << f.m_denominator;
	return out;
}



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
	Fraction f1;
	std::cout << "Enter fraction 1: ";
	std::cin >> f1;

	Fraction f2;
	std::cout << "Enter fraction 2: ";
	std::cin >> f2;

	std::cout << f1 << " * " << f2 << " is " << f1 * f2 << '\n';

	return 0;

	return 0;
}
