#pragma once
class Vector3d;	//need to declare that this exists in this header

class Point3d
{
private:
	double m_x, m_y, m_z;

public:
	Point3d(double x = 0.0, double y = 0.0, double z = 0.0)
		: m_x{ x }, m_y{ y }, m_z{ z }
	{
	}

	void print();
	void moveByVector(const Vector3d &v);		//forward declaration of class Vector3d needed for the forward declaration of the friend function
};