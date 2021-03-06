// 8.5_Constructors.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

class Colour
{
public:				//could have the enum outside of the class but then we couldn't access it when calling colours from main.
	enum Type
	{
		BLACK,
		BLUE,
		GREEN,
		ORANGE,
		RED,
		WHITE,
		YELLOW,
		MAX_COLOURS
	};

private:
	Type m_type;
	std::string m_name;

	void convertTypeToName()
	{
		switch (m_type)
		{
		case BLACK:		m_name = "black";	break;
		case BLUE:		m_name = "blue";	break;
		case GREEN:		m_name = "green";	break;
		case ORANGE:	m_name = "orange";	break;
		case RED:		m_name = "red";		break;
		case WHITE:		m_name = "white";	break;
		case YELLOW:	m_name = "yellow";	break;
		default:		m_name = "Colour not found";
		}
	}

public:
	Colour(Type type = BLACK)	//default constructor for Colour
	{
		m_type = type;
	}

	void printColour()
	{
		convertTypeToName();
		std::cout << m_name;
	}
};


class Ball
{
private:
	std::string m_color;
	double m_radius;

public:
	// Constructor with only radius parameter (color will use default value)
	Ball(double radius)
	{
		m_color = "black";
		m_radius = radius;
	}

	// Constructor with both color and radius parameters
	// handles no parameter, color only, and color + radius cases.
	Ball(const std::string &color = "black", double radius = 10.0)
	{
		m_color = color;
		m_radius = radius;
	}

	void print()
	{
		std::cout << "color: " << m_color << ", radius: " << m_radius << '\n';
	}
};


int main()
{
	Colour lemons(Colour::YELLOW);			//see if you can improve this such that the two classes can interact? Inheritance/friend functions? 
	lemons.printColour();

	Ball def;
	def.print();

	Ball blue("blue");
	blue.print();

	Ball twenty(20.0);
	twenty.print();

	Ball blueTwenty("blue", 20.0);
	blueTwenty.print();

	return 0;

    return 0;
}

