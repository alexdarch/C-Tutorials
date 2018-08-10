#pragma once
#include "point3d.h"		//for declaring moveByVector as a friend

class Vector3d
{
private:
	double m_x, m_y, m_z;

public:
	Vector3d(double x = 0.0, double y = 0.0, double z = 0.0)
		: m_x{ x }, m_y{ y }, m_z{ z }
	{
	}

	void print();

	//  friend class Point3d;		//gives all of the members of the friend class access to the private members of the other class
	friend void Point3d::moveByVector(const Vector3d &v);	//needs to have seen the forward declaration of the friend function in Point3d
};