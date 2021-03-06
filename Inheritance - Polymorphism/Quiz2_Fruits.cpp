// Quiz2_Fruits.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
//Apple class and a Banana class that are derived from a common Fruit class.Fruit should have two members : a name, and a color.
class Fruit
{
private:
	std::string m_name;
	std::string m_colour;

public:
	Fruit(const std::string &name = "Apple", const std::string &colour = "red") : m_name{ name }, m_colour { colour }	//default constructor
				//if no arguments, then it's a red apple. If one arguement then it is a red "whatever fruit". If 2 then it is defined by any colour
	{
	}
	std::string getName() const { return m_name; }		//need to be public to work in main(). Compiler starts looking in Apple and Banana for these, but doesn't find them
	std::string getColour() const { return m_colour; }	//so uses a "more base" function
};

class Apple : public Fruit
{
protected:
	Apple(const std::string &name, const std::string &colour) : Fruit(name, colour)	//protected constructor can only be accessed by derived classes
	{														//annoyingly if you put colour = "red" default argument, you get an error. This is because
	}														//the compiler looks at both Apple constructors and sees that it is ambiguous... even though it can't access the
															//protected one. So the compiler must check everything to start with, and then check access specifiers. Annoying!
public:
	Apple(const std::string &colour = "red") : Fruit("Apple", colour)		//default constructor. Fruit is always an apple, but colour can change
	{
	}
};

class GrannySmith : public Apple
{
public:
	GrannySmith() : Apple("granny smith apple", "red")	//calls the protected apple constructor because it is the only one that fits the arguments
	{
	}
};


class Banana : public Fruit
{
public:
	Banana(const std::string &colour = "yellow") : Fruit("Banana", colour)	//default constructor. Fruit is always a banana, but colour can change
	{
	}

};


int main()
{
	Apple a("red");
	Banana b;
	GrannySmith c;

	std::cout << "My " << a.getName() << " is " << a.getColour() << ".\n";
	std::cout << "My " << b.getName() << " is " << b.getColour() << ".\n";
	std::cout << "My " << c.getName() << " is " << c.getColour() << ".\n";
	//My granny smith apple is green.


    return 0;
}


