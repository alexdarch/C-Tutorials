// 8.3_Access_specifiers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cassert>

class Point3d 
{
private:
	double m_x;
	double m_y;
	double m_z;

public:
	void setValues(double setX, double setY, double setZ)
	{
		m_x = setX;		m_y = setY;		m_z = setZ;
	}
	void print()
	{
		std::cout << "<" << m_x << ", " << m_y << ", " << m_z << ">\n";
	}
	bool isEqual(const Point3d &point2)
	{
		return (m_x == point2.m_x && m_y == point2.m_y && m_z == point2.m_z);
	}
};


class Stack
{
private:
	int m_stack[10];
	int m_stackLength;

public:
	void reset()
	{
		for (auto &element : m_stack) //needs to be a reference to element otherwise doesn't change it
			element = 0;

		m_stackLength = 0;
	}
	bool push(int element)
	{
		if (m_stackLength > 10)
			return false;

		m_stack[m_stackLength++] = element;	//set m_stack[m_stackLength] = element; and then increment m_stackLength (as opposed to ++m_stackLength)
		return true;
	}
	int pop()
	{
		assert(m_stackLength > 0 && "Can not pop empty stack");

		int value = m_stack[m_stackLength];
		m_stack[m_stackLength--] = 0;	//set m_stack[m_stackLength] = 0; and then decrement m_stackLength (as opposed to --m_stackLength)
		return value;
	}
	void print()
	{
		std::cout << "( ";
		for (int index = 0; index < m_stackLength; ++index)
		{
			std::cout << m_stack[index] << " ";
		}
		std::cout << ")\n";
	}


};


int main()
{
	Point3d point1;
	point1.setValues(1.0, 2.0, 3.0);

	Point3d point2;
	point2.setValues(1.0, 2.0, 3.0);

	if (point1.isEqual(point2))
		std::cout << "point1 and point2 are equal\n";
	else
		std::cout << "point1 and point2 are not equal\n";

	Point3d point3;
	point3.setValues(3.0, 4.0, 5.0);

	if (point1.isEqual(point3))
		std::cout << "point1 and point3 are equal\n";
	else
		std::cout << "point1 and point3 are not equal\n";

	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////

	Stack stack;
	stack.reset();

	stack.print();

	stack.push(5);
	stack.push(3);
	stack.push(8);
	stack.print();

	stack.pop();
	stack.print();

	stack.pop();
	stack.pop();

	stack.print();


    return 0;
}

