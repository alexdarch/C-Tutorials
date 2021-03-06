// 8.5b_NonStatic_Member_Initialisation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

class Ball
{
private:
	std::string m_colour = "black";
	double m_radius = 10.0;

public:
	// Default constructor with no parameters
	Ball()
	{
	}

	// Constructor with only color parameter (radius will use default value)
	Ball(const std::string &colour) : m_colour{ colour }
	{
	}

	// Constructor with only radius parameter (color will use default value)
	Ball(double radius) : m_radius{ radius }
	{
	}

	// Constructor with both color and radius parameters
	Ball(const std::string &colour, double radius) : m_colour{ colour }, m_radius{ radius }
	{
	}

	void print()
	{
		std::cout << "color: " << m_colour << ", radius: " << m_radius << '\n';
	}
};

int main()
{
	Ball def;
	def.print();

	Ball blue("blue");
	blue.print();

	Ball twenty(20.0);
	twenty.print();

	Ball blueTwenty("blue", 20.0);
	blueTwenty.print();

	return 0;
}