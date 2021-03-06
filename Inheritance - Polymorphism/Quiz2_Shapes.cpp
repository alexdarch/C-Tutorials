// Quiz2_Shapes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

class Shape
{
public:
	friend std::ostream& operator<<(std::ostream &out, const Shape &s)
	{
		return s.print(out);
	}
	virtual std::ostream& print(std::ostream &out) const = 0;	//makes this an abstract class
	
	virtual ~Shape() {}
};

class Point
{
private:
	int m_x = 0;
	int m_y = 0;
	int m_z = 0;

public:
	Point(int x, int y, int z)
		: m_x(x), m_y(y), m_z(z)
	{

	}

	friend std::ostream& operator<<(std::ostream &out, const Point &p)
	{
		out << "Point(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ")";
		return out;
	}
};

class Triangle : public Shape
{
private:
	Point m_a;
	Point m_b;
	Point m_c;
public:
	Triangle(const Point &a, const Point &b, const Point &c) : m_a{ a }, m_b{ b }, m_c{ c }
	{
	}
	virtual std::ostream& print(std::ostream &out) const override
	{
		out << "Triangle(" << m_a << ", " << m_b << ", " << m_c << ")";
		return out;
	}
	virtual ~Triangle() {}
};

class Circle : public Shape
{
private:
	Point m_centre;
	int m_radius;
public:
	Circle(const Point &p, int radius) : m_centre{ p }, m_radius{ radius }
	{
	}
	virtual std::ostream& print(std::ostream &out) const override
	{
		out << "Circle(" << this->m_centre << ", radius " << this->m_radius << ")";
		return out;
	}
	
	int getRadius() { return m_radius; }
	virtual ~Circle() {}
};


int getLargestRadius(const std::vector<Shape*> &shapes)
{
	//we need to check if the shape is a circle, and then downcast it to a circle.
	//then for all of the circles, find the largest radius
	int largestRadius = 0;
	for (const auto &element : shapes)
	{
		// // Ensure the dynamic cast succeeds by checking for a null pointer result
		if (Circle *c = dynamic_cast<Circle*>(element))
		{
			if (c->getRadius() > largestRadius)
				largestRadius = c->getRadius();
		}
	}
	return largestRadius;
}



int main()
{
	//Hint: You’ll need to add a getRadius() function to Circle, and downcast a Shape* into a Circle* to access it.
	std::vector<Shape*> v;
	v.push_back(new Circle(Point(1, 2, 3), 7));
	v.push_back(new Triangle(Point(1, 2, 3), Point(4, 5, 6), Point(7, 8, 9)));
	v.push_back(new Circle(Point(4, 5, 6), 3));

	// print each shape in vector v on its own line here
	for (const auto &element : v)
		std::cout << *element << "\n";

	std::cout << "The largest radius is: " << getLargestRadius(v) << '\n'; // write this function

	for (const auto &element : v)
		delete element;

    return 0;
}

