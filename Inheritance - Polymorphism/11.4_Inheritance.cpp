// 11.4_Inheritance.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

//1) Let’s implement our Fruit example that we talked about in our introduction to inheritance.
//Create a Fruit base class that contains two private members : a name(std::string), and a color(std::string).
//Create an Apple class that inherits Fruit.Apple should have an additional private member : fiber(double).
//Create a Banana class that also inherits Fruit.Banana has no additional members.
class Fruit
{
private:
	std::string m_name;
	std::string m_colour;

public:
	Fruit(const std::string &name, const std::string &colour)
		:m_name{ name }, m_colour{ colour }
			{
			}

	std::string getName() const { return m_name; }		//if we want to use const object then these have to be const
	std::string getColour() const { return m_colour; }	//we can still use these for non-const objects. Const "get" functions should always be preferred
};

class Apple : public Fruit
{
private:
	double m_fiber;
public:
	Apple(const std::string &name, const std::string &colour, double fiber)	//might as well use constant m_name and m_colour here, there aren't any functions that edit them
		:Fruit(name, colour), m_fiber{ fiber }
	{
	}

	friend std::ostream& operator<<(std::ostream &out, const Apple &a)
	{
		out << "Apple(" << a.getName() << ", " << a.getColour() << ", " << a.m_fiber << ")\n";
		return out;
	}
};

class Banana : public Fruit
{
public:
	Banana(const std::string &name, const std::string &colour)
		:Fruit(name, colour)
	{
	}
	friend std::ostream& operator<<(std::ostream &out, const Banana &b)
	{
		out << "Apple(" << b.getName() << ", " << b.getColour() << ")\n";
		return out;
	}
};

int main()
{

	const Apple a("Red delicious", "red", 4.2);	//constant object
	std::cout << a;

	const Banana b("Cavendish", "yellow");
	std::cout << b;

    return 0;
}

