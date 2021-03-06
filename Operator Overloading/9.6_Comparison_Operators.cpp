// 9.6_Comparison_Operators.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


class Car
{
private:
	std::string m_make;
	std::string m_model;

public:
	Car(const std::string &make, const std::string &model)
		:m_make{ make }, m_model{ model }
	{

	}
	friend bool operator==(const Car &c1, const Car &c2);
	friend bool operator!=(const Car &c1, const Car &c2);

	friend std::ostream& operator<<(std::ostream &out, const Car &c);
	friend bool operator<(const Car &c1, const Car &c2);

};

bool operator==(const Car &c1, const Car &c2)
{
	return ((c1.m_make == c2.m_make) && (c1.m_model == c2.m_model));
}
bool operator!=(const Car &c1, const Car &c2)
{
	return !(c1 == c2);	//Just returns the opposite of ==, and uses that definition.
}

std::ostream& operator<<(std::ostream &out, const Car &c) 
{
	out << "(" << c.m_make << ", " << c.m_model << ")";
	return out;
}

bool operator<(const Car &c1, const Car &c2)
{
	if (c1.m_make == c2.m_make)
		return (c1.m_model < c2.m_model);
	else
		return (c1.m_make < c2.m_make);
}

int main()
{
	std::vector<Car> v;
	v.push_back(Car("Toyota", "Corolla"));
	v.push_back(Car("Honda", "Accord"));
	v.push_back(Car("Toyota", "Camry"));
	v.push_back(Car("Honda", "Civic"));

	std::sort(v.begin(), v.end()); // requires an overloaded operator<

	for (auto &car : v)
		std::cout << car << '\n'; // requires an overloaded operator<<

	return 0;
}