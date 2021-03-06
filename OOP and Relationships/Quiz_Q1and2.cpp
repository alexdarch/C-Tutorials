// Quiz_Q1and2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>


class HelloWorld
{
private:
	char *m_data;

public:
	HelloWorld()
	{
		m_data = new char[14];
		const char *init = "Hello, World!";
		for (int i = 0; i < 14; ++i)
			m_data[i] = init[i];
	}

	~HelloWorld()
	{
		delete[] m_data;
		// replace this comment with your destructor implementation
	}

	void print() const
	{
		std::cout << m_data << "\n";
	}

};


class Point2d
{
private:
	double m_x;
	double m_y;
public:

	Point2d(double x = 0.0, double y = 0.0)
		:m_x{ x }, m_y{ y }
	{
	}

	double distanceTo(const Point2d &p2)
	{
		return sqrt((m_x - p2.m_x)*(m_x - p2.m_x) + (m_y - p2.m_y)*(m_y - p2.m_y));
	}

	void print()
	{
		std::cout << "Point2d(" << m_x << ", " << m_y << ")\n";
	}

	friend double distanceFrom(const Point2d &p1, const Point2d &p2);

};


double distanceFrom(const Point2d &p1, const Point2d &p2)
{
	return sqrt((p1.m_x - p2.m_x)*(p1.m_x - p2.m_x) + (p1.m_y - p2.m_y)*(p1.m_y - p2.m_y));
}


int main()
{
	HelloWorld hello;
	hello.print();


	Point2d first;
	Point2d second(3.0, 4.0);
	first.print();
	second.print();
	std::cout << "Distance between two points: " << first.distanceTo(second) << '\n'; 
	std::cout << "Distance between two points: " << distanceFrom(first, second) << '\n';

	return 0;
}

